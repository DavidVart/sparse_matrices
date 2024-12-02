// DiagonalMatrix: A class representing a sparse matrix in diagonal format.
// toDense: Converts the diagonal matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#ifndef DIAGONALMATRIX_H
#define DIAGONALMATRIX_H

#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include <vector>
#include <utility>

namespace sparsematrix {

class DiagonalMatrix : public SparseMatrix {
public:
    explicit DiagonalMatrix(const DenseMatrix& denseMatrix);

    void toDense(DenseMatrix& denseMatrix) const override;
    size_t getNNZ() const override;
    std::pair<size_t, size_t> getShape() const override;
    double getElement(size_t row, size_t col) const;

private:
    size_t numRows;
    size_t numCols;
    std::vector<double> values;
};

} // namespace sparsematrix

#endif // DIAGONALMATRIX_H