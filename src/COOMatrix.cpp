#include "COOMatrix.h"
#include <stdexcept>

namespace sparsematrix {

COOMatrix::COOMatrix(const DenseMatrix& denseMatrix) {
    if (denseMatrix.rows == 0 || denseMatrix.cols == 0) {
        rows = 0;
        cols = 0;
        return;
    }
    if (denseMatrix.rows != denseMatrix.cols) {
        throw std::invalid_argument("COOMatrix must be square.");
    }
    rows = denseMatrix.rows;
    cols = denseMatrix.cols;

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (denseMatrix(i, j) != 0) {
                values.push_back(denseMatrix(i, j));
                row_indices.push_back(i);
                col_indices.push_back(j);
            }
        }
    }
}

void COOMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(rows, cols);
    for (size_t k = 0; k < values.size(); ++k) {
        denseMatrix(row_indices[k], col_indices[k]) = values[k];
    }
}

size_t COOMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> COOMatrix::getShape() const {
    return {rows, cols};
}

} // namespace sparsematrix