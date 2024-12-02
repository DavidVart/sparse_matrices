// COOMatrix: Implements the constructor to convert a dense matrix to COO format.
// toDense: Converts the COO matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#include "COOMatrix.h"
#include <stdexcept>

namespace sparsematrix {

COOMatrix::COOMatrix(const DenseMatrix& denseMatrix) {
    numRows = denseMatrix.rows;
    numCols = denseMatrix.cols;

    for (size_t i = 0; i < numRows; ++i) {
        for (size_t j = 0; j < numCols; ++j) {
            if (denseMatrix(i, j) != 0) {
                rowIndices.push_back(i);
                colIndices.push_back(j);
                values.push_back(denseMatrix(i, j));
            }
        }
    }
}

void COOMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(numRows, numCols);
    for (size_t k = 0; k < values.size(); ++k) {
        denseMatrix(rowIndices[k], colIndices[k]) = values[k];
    }
}

size_t COOMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> COOMatrix::getShape() const {
    return {numRows, numCols};
}

} // namespace sparsematrix