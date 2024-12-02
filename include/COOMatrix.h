/**
 * @file COOMatrix.h
 * @brief Header file for the COOMatrix class.
 */

#ifndef COOMATRIX_H
#define COOMATRIX_H

#include "SparseMatrix.h"
#include <stdexcept>
#include <vector>

namespace sparsematrix {

/**
 * @class COOMatrix
 * @brief Class representing a sparse matrix in COO (Coordinate) format.
 */
class COOMatrix : public SparseMatrix {
public:
    /**
     * @brief Constructs a COOMatrix from a DenseMatrix.
     * @param dense The dense matrix to convert.
     */
    COOMatrix(const DenseMatrix& dense);

    /**
     * @brief Converts the COOMatrix to a DenseMatrix.
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
    std::vector<size_t> row_indices, col_indices;
    std::vector<double> values;
};

} // namespace sparsematrix

#endif // COOMATRIX_H