/**
 * @file CSRMatrix.h
 * @brief Header file for the CSRMatrix class.
 */

#ifndef CSRMATRIX_H
#define CSRMATRIX_H

#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include <stdexcept>
#include <vector>

namespace sparsematrix {

/**
 * @class CSRMatrix
 * @brief Class representing a Compressed Sparse Row (CSR) matrix.
 */
class CSRMatrix : public SparseMatrix {
public:
    /**
     * @brief Constructs a CSRMatrix from a DenseMatrix.
     * @param dense The dense matrix to convert.
     */
    CSRMatrix(const DenseMatrix& dense);

    /**
     * @brief Converts the CSRMatrix to a DenseMatrix.
     * @param dense The dense matrix to store the result.
     */
    void toDense(DenseMatrix& dense) const override;

    /**
     * @brief Gets the number of non-zero elements in the matrix.
     * @return The number of non-zero elements.
     */
    size_t getNNZ() const override;

    /**
     * @brief Gets the shape of the matrix.
     * @return A pair representing the number of rows and columns.
     */
    std::pair<size_t, size_t> getShape() const override;

    /**
     * @brief Gets the column indices of the non-zero elements.
     * @return A vector of column indices.
     */
    const std::vector<size_t>& getColIndices() const { return col_indices; }

    /**
     * @brief Gets the row pointers of the matrix.
     * @return A vector of row pointers.
     */
    const std::vector<size_t>& getRowPtrs() const { return row_ptrs; }

    /**
     * @brief Gets the values of the non-zero elements.
     * @return A vector of values.
     */
    const std::vector<double>& getValues() const { return values; }

private:
    size_t rows, cols;
    std::vector<size_t> col_indices, row_ptrs;
    std::vector<double> values;
};

/**
 * @brief Multiplies two CSR matrices and returns the result as a DenseMatrix.
 * @param mat1 The first CSR matrix.
 * @param mat2 The second CSR matrix.
 * @return The result of the multiplication as a DenseMatrix.
 */
DenseMatrix multiply_sparse_matrices(const CSRMatrix& mat1, const CSRMatrix& mat2);

} // namespace sparsematrix

#endif // CSRMATRIX_H