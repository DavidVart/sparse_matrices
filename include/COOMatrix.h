// COOMatrix: A class representing a sparse matrix in COO format.
// toDense: Converts the COO matrix to a dense matrix.
// getNNZ: Returns the number of non-zero elements.
// getShape: Returns the shape of the matrix.

#ifndef COOMATRIX_H
#define COOMATRIX_H

#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include <vector>
#include <utility>

namespace sparsematrix {

class COOMatrix : public SparseMatrix {
public:
    explicit COOMatrix(const DenseMatrix& denseMatrix);

    void toDense(DenseMatrix& denseMatrix) const override;
    size_t getNNZ() const override;
    std::pair<size_t, size_t> getShape() const override;

private:
    size_t numRows;
    size_t numCols;
    std::vector<size_t> rowIndices;
    std::vector<size_t> colIndices;
    std::vector<double> values;
};

} // namespace sparsematrix

#endif // COOMATRIX_H