/**
 * @file DiagonalMatrix.h
 * @brief Header file for the DiagonalMatrix class.
 */

#ifndef DIAGONALMATRIX_H
#define DIAGONALMATRIX_H

#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include <stdexcept>
#include <vector>

namespace sparsematrix {

/**
 * @class DiagonalMatrix
 * @brief Class representing a diagonal matrix.
 */
class DiagonalMatrix : public SparseMatrix {
public:
    /**
     * @brief Constructs a DiagonalMatrix from a DenseMatrix.
     * @param dense The dense matrix to convert.
     */
    DiagonalMatrix(const DenseMatrix& dense);

    /**
     * @brief Converts the DiagonalMatrix to a DenseMatrix.
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
     * @brief Gets the element at the specified position.
     * @param i The row index.
     * @param j The column index.
     * @return The element at the specified position.
     */
    double getElement(size_t i, size_t j) const;

private:
    size_t rows, cols;
    std::vector<double> diag_values;
};

} // namespace sparsematrix

#endif // DIAGONALMATRIX_H