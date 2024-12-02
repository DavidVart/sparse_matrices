#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <omp.h>
#include <filesystem>
#include <chrono>
#include "DenseMatrix.h"

// Function to generate a sparse matrix
sparsematrix::DenseMatrix generate_sparse_matrix(int rows, int cols, double sparsity) {
    std::random_device rd;
    sparsematrix::DenseMatrix matrix(rows, cols);

    #pragma omp parallel
    {
        std::mt19937 gen(rd() + omp_get_thread_num());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        #pragma omp for
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (dis(gen) >= sparsity) {
                    matrix(i, j) = dis(gen);
                }
            }
        }
    }

    return matrix;
}

// Function to write a matrix to a file
void write_matrix_to_file(const std::string& output_file, const sparsematrix::DenseMatrix& matrix) {
    std::ofstream file(output_file);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }
    for (size_t i = 0; i < matrix.rows; ++i) {
        for (size_t j = 0; j < matrix.cols; ++j) {
            file << std::fixed << std::setprecision(6) << matrix(i, j) << " ";
        }
        file << "\n";
    }
}

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    int rows = 10000;
    int cols = 10000;
    double sparsity = 0.95;
    std::string output_dir = "src/matrix_generation/output";

    if (argc > 1) rows = std::stoi(argv[1]);
    if (argc > 2) cols = std::stoi(argv[2]);
    if (argc > 3) sparsity = std::stod(argv[3]);
    if (argc > 4) output_dir = argv[4];

    std::filesystem::create_directories(output_dir);

    const std::string output_file1 = output_dir + "/dense_matrix_1.txt";
    const std::string output_file2 = output_dir + "/dense_matrix_2.txt";

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            sparsematrix::DenseMatrix matrix1 = generate_sparse_matrix(rows, cols, sparsity);
            write_matrix_to_file(output_file1, matrix1);
        }
        #pragma omp section
        {
            sparsematrix::DenseMatrix matrix2 = generate_sparse_matrix(rows, cols, sparsity);
            write_matrix_to_file(output_file2, matrix2);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Total execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}