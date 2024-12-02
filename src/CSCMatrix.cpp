// CSCMatrix: Implements the constructor to convert a dense matrix to CSC format.
// toDense: Converts the CSC matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#include "CSCMatrix.h"
#include <stdexcept>

namespace sparsematrix {

CSCMatrix::CSCMatrix(const DenseMatrix& denseMatrix) {
    numRows = denseMatrix.rows;
    numCols = denseMatrix.cols;

    colPtrs.resize(numCols + 1, 0);
    for (size_t j = 0; j < numCols; ++j) {
        for (size_t i = 0; i < numRows; ++i) {
            if (denseMatrix(i, j) != 0) {
                rowIndices.push_back(i);
                values.push_back(denseMatrix(i, j));
                colPtrs[j + 1]++;
            }
        }
    }
    for (size_t j = 1; j <= numCols; ++j) {
        colPtrs[j] += colPtrs[j - 1];
    }
}

void CSCMatrix::toDense(DenseMatrix& denseMatrix) const {
    denseMatrix = DenseMatrix(numRows, numCols);
    for (size_t j = 0; j < numCols; ++j) {
        for (size_t k = colPtrs[j]; k < colPtrs[j + 1]; ++k) {
            denseMatrix(rowIndices[k], j) = values[k];
        }
    }
}

size_t CSCMatrix::getNNZ() const {
    return values.size();
}

std::pair<size_t, size_t> CSCMatrix::getShape() const {
    return {numRows, numCols};
}

} // namespace sparsematrix