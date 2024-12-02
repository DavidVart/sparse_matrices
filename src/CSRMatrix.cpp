#include "CSRMatrix.h"
#include <stdexcept>
#include <unordered_map>

namespace sparsematrix {

CSRMatrix::CSRMatrix(const DenseMatrix& denseMatrix) {
    if (denseMatrix.rows == 0 || denseMatrix.cols == 0) {
        rows = 0;
        cols = 0;
        row_ptrs.push_back(0); // Ensure row_ptrs is initialized
        return;
    }
    if (denseMatrix.rows != denseMatrix.cols) {
        throw std::invalid_argument("CSRMatrix must be square.");
    }
    rows = denseMatrix.rows;
    cols = denseMatrix.cols;
    row_ptrs.push_back(0);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (denseMatrix(i, j) != 0) {
                values.push_back(denseMatrix(i, j));
                col_indices.push_back(j);
            }
        }
        row_ptrs.push_back(values.size());
    }
}

void CSRMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = row_ptrs[i]; j < row_ptrs[i + 1]; ++j) {
            denseMatrix(i, col_indices[j]) = values[j];
        }
    }
}

size_t CSRMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> CSRMatrix::getShape() const {
    return {rows, cols};
}

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