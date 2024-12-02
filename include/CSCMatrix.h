/**
 * @file CSCMatrix.h
 * @brief Header file for the CSCMatrix class.
 */

#ifndef CSCMATRIX_H
#define CSCMATRIX_H

#include "SparseMatrix.h"
#include <stdexcept>
#include <vector>

namespace sparsematrix {

/**
 * @class CSCMatrix
 * @brief Class representing a sparse matrix in CSC (Compressed Sparse Column) format.
 */
class CSCMatrix : public SparseMatrix {
public:
    /**
     * @brief Constructs a CSCMatrix from a DenseMatrix.
     * @param dense The dense matrix to convert.
     */
    CSCMatrix(const DenseMatrix& dense);

    /**
     * @brief Converts the CSCMatrix to a DenseMatrix.
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

private:
    size_t rows, cols;
    std::vector<size_t> row_indices, col_ptrs;
    std::vector<double> values;
};

} // namespace sparsematrix

#endif // CSCMATRIX_H