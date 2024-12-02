/**
 * @file DenseMatrix.h
 * @brief Header file for the DenseMatrix struct.
 */

#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include <vector>
#include <initializer_list>
#include <stdexcept>

namespace sparsematrix {

/**
 * @struct DenseMatrix
 * @brief Struct representing a dense matrix.
 */
struct DenseMatrix {
    size_t rows; ///< Number of rows
    size_t cols; ///< Number of columns
    std::vector<double> data; ///< Matrix data stored in row-major order

    /**
     * @brief Constructs a DenseMatrix with the specified dimensions.
     * @param r Number of rows.
     * @param c Number of columns.
     */
    DenseMatrix(size_t r, size_t c) : rows(r), cols(c), data(r * c) {}

    /**
     * @brief Constructs a DenseMatrix from an initializer list.
     * @param init Initializer list of initializer lists representing the matrix.
     */
    DenseMatrix(std::initializer_list<std::initializer_list<double>> init) {
        rows = init.size();
        cols = init.begin()->size();
        data.reserve(rows * cols);
        for (const auto& row : init) {
            if (row.size() != cols) {
                throw std::invalid_argument("All rows must have the same number of columns");
            }
            data.insert(data.end(), row.begin(), row.end());
        }
    }

    /**
     * @brief Accesses the element at the specified position.
     * @param r Row index.
     * @param c Column index.
     * @return Reference to the element at the specified position.
     */
    double& operator()(size_t r, size_t c) {
        return data[r * cols + c];
    }

    /**
     * @brief Accesses the element at the specified position (const version).
     * @param r Row index.
     * @param c Column index.
     * @return Const reference to the element at the specified position.
     */
    const double& operator()(size_t r, size_t c) const {
        return data[r * cols + c];
    }

    /**
     * @brief Compares two DenseMatrix objects for equality.
     * @param other The other DenseMatrix to compare with.
     * @return True if the matrices are equal, false otherwise.
     */
    bool operator==(const DenseMatrix& other) const {
        return rows == other.rows && cols == other.cols && data == other.data;
    }
};

} // namespace sparsematrix

#endif // DENSEMATRIX_H