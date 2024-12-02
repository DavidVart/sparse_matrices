// CSCMatrix: A class representing a sparse matrix in CSC format.
// toDense: Converts the CSC matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#ifndef CSCMATRIX_H
#define CSCMATRIX_H

#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include <vector>
#include <utility>

namespace sparsematrix {

class CSCMatrix : public SparseMatrix {
public:
    explicit CSCMatrix(const DenseMatrix& denseMatrix);

    void toDense(DenseMatrix& denseMatrix) const override;
    size_t getNNZ() const override;
    std::pair<size_t, size_t> getShape() const override;

private:
    size_t numRows;
    size_t numCols;
    std::vector<size_t> colPtrs;
    std::vector<size_t> rowIndices;
    std::vector<double> values;
};

} // namespace sparsematrix

#endif // CSCMATRIX_H