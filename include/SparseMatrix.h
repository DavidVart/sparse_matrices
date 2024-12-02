/**
 * @file SparseMatrix.h
 * @brief Header file for the SparseMatrix base class.
 */

#ifndef SPARSEMATRIX_H
#define SPARSEMATRIX_H

#include "DenseMatrix.h"
#include <string>

namespace sparsematrix {

/**
 * @class SparseMatrix
 * @brief The base class for all sparse matrix types.
 */
class SparseMatrix {
public:
    virtual ~SparseMatrix() = default; // Virtual destructor

    /**
     * @brief Factory method to create a sparse matrix from a dense matrix.
     * @param denseMatrix The dense matrix to convert.
     * @param format The format of the sparse matrix (e.g., "CSR", "CSC").
     * @return A pointer to the created sparse matrix.
     */
    static SparseMatrix* fromDense(const DenseMatrix& denseMatrix, const std::string& format);

    /**
     * @brief Converts the sparse matrix to a dense matrix.
     * @param denseMatrix The dense matrix to store the result.
     */
    virtual void toDense(DenseMatrix& denseMatrix) const = 0;

    /**
     * @brief Gets the number of non-zero elements in the matrix.
     * @return The number of non-zero elements.
     */
    virtual size_t getNNZ() const = 0;

    /**
     * @brief Gets the shape of the matrix.
     * @return A pair representing the number of rows and columns.
     */
    virtual std::pair<size_t, size_t> getShape() const = 0;
};

} // namespace sparsematrix

#endif // SPARSEMATRIX_H