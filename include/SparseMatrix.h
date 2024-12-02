// SparseMatrix: The base class for all sparse matrix types.
// fromDense: A factory method to create a sparse matrix from a dense matrix.
// toDense: A pure virtual method to convert a sparse matrix to a dense matrix.
// getNNZ: A pure virtual method to get the number of non-zero elements.
// getShape: A pure virtual method to get the shape of the matrix.

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "DenseMatrix.h"
#include <string>

namespace sparsematrix {

class SparseMatrix {
public:
    virtual ~SparseMatrix() = default; // Virtual destructor

    static SparseMatrix* fromDense(const DenseMatrix& denseMatrix, const std::string& format);

    virtual void toDense(DenseMatrix& denseMatrix) const = 0;
    virtual size_t getNNZ() const = 0;
    virtual std::pair<size_t, size_t> getShape() const = 0;
};

} // namespace sparsematrix

#endif // SPARSEMATRIX_H