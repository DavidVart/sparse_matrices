// DiagonalMatrix: Implements the constructor to convert a dense matrix to diagonal format.
// toDense: Converts the diagonal matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#include "DiagonalMatrix.h"
#include <stdexcept>

namespace sparsematrix {

DiagonalMatrix::DiagonalMatrix(const DenseMatrix& denseMatrix) {
    numRows = denseMatrix.rows;
    numCols = denseMatrix.cols;

    for (size_t i = 0; i < numRows && i < numCols; ++i) {
        if (denseMatrix(i, i) != 0) {
            values.push_back(denseMatrix(i, i));
        }
    }
}

void DiagonalMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(numRows, numCols);
    for (size_t i = 0; i < values.size(); ++i) {
        denseMatrix(i, i) = values[i];
    }
}

size_t DiagonalMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> DiagonalMatrix::getShape() const {
    return {numRows, numCols};
}

double DiagonalMatrix::getElement(size_t row, size_t col) const {
    if (row >= numRows || col >= numCols) {
        throw std::out_of_range("Index out of range");
    }
    return (row == col) ? values[row] : 0.0;
}

} // namespace sparsematrix