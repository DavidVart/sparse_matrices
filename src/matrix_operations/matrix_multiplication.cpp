#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <omp.h>
#include <filesystem>
#include "CSRMatrix.h"
#include "DenseMatrix.h"

// Function to read a dense matrix from a file
sparsematrix::DenseMatrix read_matrix(const std::string& file_path) {
    std::ifstream file(file_path);
    std::vector<std::string> lines;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << std::endl;
        return sparsematrix::DenseMatrix(0, 0);
    }

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    size_t rows = lines.size();
    size_t cols = 0;
    if (rows > 0) {
        std::istringstream iss(lines[0]);
        double value;
        while (iss >> value) {
            ++cols;
        }
    }

    sparsematrix::DenseMatrix matrix(rows, cols);

    #pragma omp parallel for
    for (size_t i = 0; i < rows; ++i) {
        std::istringstream iss(lines[i]);
        for (size_t j = 0; j < cols; ++j) {
            iss >> matrix(i, j);
        }
    }

    std::cout << "Matrix read from " << file_path << " with dimensions " << rows << "x" << cols << std::endl;
    return matrix;
}

// Function to write a matrix to a file
void write_matrix(const sparsematrix::DenseMatrix& matrix, const std::string& file_path) {
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << file_path << " for writing." << std::endl;
        return;
    }

    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            file << matrix(i, j) << " ";
        }
        file << "\n";
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::string file1 = "src/matrix_generation/output/dense_matrix_1.txt";
    std::string file2 = "src/matrix_generation/output/dense_matrix_2.txt";
    std::string output_file = "src/matrix_operations/output/result_matrix.txt";

    sparsematrix::DenseMatrix dense_matrix1 = read_matrix(file1);
    sparsematrix::DenseMatrix dense_matrix2 = read_matrix(file2);

    if (dense_matrix1.rows == 0 || dense_matrix2.rows == 0) {
        std::cerr << "Error: One of the matrices is empty." << std::endl;
        return 1;
    }

    if (dense_matrix1.cols != dense_matrix2.rows) {
        std::cerr << "Error: Matrix dimensions do not match for multiplication." << std::endl;
        return 1;
    }

    sparsematrix::CSRMatrix sparse_matrix1(dense_matrix1);
    sparsematrix::CSRMatrix sparse_matrix2(dense_matrix2);

    sparsematrix::DenseMatrix result_matrix = sparsematrix::multiply_sparse_matrices(sparse_matrix1, sparse_matrix2);

    write_matrix(result_matrix, output_file);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total execution time: " << duration.count() << " seconds" << std::endl;

    std::cout << "Matrix multiplication completed and result written to " << output_file << std::endl;

    return 0;
}