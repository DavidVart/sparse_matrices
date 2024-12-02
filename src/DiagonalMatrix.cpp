#include "DiagonalMatrix.h"
#include <stdexcept>

namespace sparsematrix {

DiagonalMatrix::DiagonalMatrix(const DenseMatrix& denseMatrix) {
    if (denseMatrix.rows == 0 || denseMatrix.cols == 0) {
        rows = 0;
        cols = 0;
        return;
    }
    if (denseMatrix.rows != denseMatrix.cols) {
        throw std::invalid_argument("Diagonal matrix must be square.");
    }
    rows = denseMatrix.rows;
    cols = denseMatrix.cols;

    for (size_t i = 0; i < rows; ++i) {
        diag_values.push_back(denseMatrix(i, i));
    }
}

void DiagonalMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        denseMatrix(i, i) = diag_values[i];
    }
}

size_t DiagonalMatrix::getNNZ() const {
    return diag_values.size();
}

std::pair<size_t, size_t> DiagonalMatrix::getShape() const {
    return {rows, cols};
}

double DiagonalMatrix::getElement(size_t i, size_t j) const {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Index out of range.");
    }
    return (i == j) ? diag_values[i] : 0.0;
}

} // namespace sparsematrix