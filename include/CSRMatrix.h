#ifndef CSR_MATRIX_H
#define CSR_MATRIX_H

#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include <vector>
#include <utility>

namespace sparsematrix {

class CSRMatrix : public SparseMatrix {
public:
    explicit CSRMatrix(const DenseMatrix& denseMatrix);

    void toDense(DenseMatrix& denseMatrix) const override;
    size_t getNNZ() const override;
    std::pair<size_t, size_t> getShape() const override;

    // Public getter methods for private members
    const std::vector<size_t>& getRowPtrs() const { return rowPtrs; }
    const std::vector<size_t>& getColIndices() const { return colIndices; }
    const std::vector<double>& getValues() const { return values; }

private:
    size_t numRows;
    size_t numCols;
    std::vector<size_t> rowPtrs;
    std::vector<size_t> colIndices;
    std::vector<double> values;
};

// Function to multiply two sparse matrices
DenseMatrix multiply_sparse_matrices(const CSRMatrix& mat1, const CSRMatrix& mat2);

} // namespace sparsematrix

#endif // CSR_MATRIX_H