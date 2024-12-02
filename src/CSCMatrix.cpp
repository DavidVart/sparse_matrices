#include "CSCMatrix.h"
#include <stdexcept>

namespace sparsematrix {

CSCMatrix::CSCMatrix(const DenseMatrix& denseMatrix) {
    if (denseMatrix.rows == 0 || denseMatrix.cols == 0) {
        rows = 0;
        cols = 0;
        col_ptrs.push_back(0); // Ensure col_ptrs is initialized
        return;
    }
    if (denseMatrix.rows != denseMatrix.cols) {
        throw std::invalid_argument("CSCMatrix must be square.");
    }
    rows = denseMatrix.rows;
    cols = denseMatrix.cols;
    col_ptrs.push_back(0);

    for (size_t j = 0; j < cols; ++j) {
        for (size_t i = 0; i < rows; ++i) {
            if (denseMatrix(i, j) != 0) {
                values.push_back(denseMatrix(i, j));
                row_indices.push_back(i);
            }
        }
        col_ptrs.push_back(values.size());
    }
}

void CSCMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(rows, cols);
    for (size_t j = 0; j < cols; ++j) {
        for (size_t i = col_ptrs[j]; i < col_ptrs[j + 1]; ++i) {
            denseMatrix(row_indices[i], j) = values[i];
        }
    }
}

size_t CSCMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> CSCMatrix::getShape() const {
    return {rows, cols};
}

} // namespace sparsematrix