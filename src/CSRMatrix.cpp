#include "CSRMatrix.h"
#include <iostream>
#include <unordered_map>

namespace sparsematrix {

// Constructor to create a CSR matrix from a dense matrix
CSRMatrix::CSRMatrix(const DenseMatrix& denseMatrix) {
    numRows = denseMatrix.rows;
    numCols = denseMatrix.cols;
    rowPtrs.push_back(0);

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (denseMatrix(i, j) != 0) {
                values.push_back(denseMatrix(i, j));
                colIndices.push_back(j);
            }
        }
        rowPtrs.push_back(values.size());
    }
}

// Converts the CSR matrix back to a dense matrix
void CSRMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(numRows, numCols);
    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = rowPtrs[i]; j < rowPtrs[i + 1]; ++j) {
            denseMatrix(i, colIndices[j]) = values[j];
        }
    }
}

// Get the number of non-zero elements
size_t CSRMatrix::getNNZ() const {
    return values.size();
}

// Get the shape of the matrix as {rows, columns}
std::pair<size_t, size_t> CSRMatrix::getShape() const {
    return {numRows, numCols};
}

// Function to multiply two sparse matrices
DenseMatrix multiply_sparse_matrices(const CSRMatrix& mat1, const CSRMatrix& mat2) {
    if (mat1.getShape().second != mat2.getShape().first) {
        throw std::invalid_argument("Matrix dimensions do not match for multiplication.");
    }

    size_t rows = mat1.getShape().first;
    size_t cols = mat2.getShape().second;
    DenseMatrix result(rows, cols);

    #pragma omp parallel for
    for (size_t i = 0; i < rows; ++i) {
        std::unordered_map<size_t, double> row_result;
        for (size_t j = mat1.getRowPtrs()[i]; j < mat1.getRowPtrs()[i + 1]; ++j) {
            size_t col = mat1.getColIndices()[j];
            double val = mat1.getValues()[j];
            for (size_t k = mat2.getRowPtrs()[col]; k < mat2.getRowPtrs()[col + 1]; ++k) {
                size_t col2 = mat2.getColIndices()[k];
                double val2 = mat2.getValues()[k];
                #pragma omp atomic
                result(i, col2) += val * val2;
            }
        }
    }

    return result;
}

} // namespace sparsematrix