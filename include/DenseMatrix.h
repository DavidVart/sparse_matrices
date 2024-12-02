#ifndef DENSEMATRIX_H
#define DENSEMATRIX_H

#include <vector>
#include <initializer_list>
#include <stdexcept>

namespace sparsematrix {

struct DenseMatrix {
    size_t rows;
    size_t cols;
    std::vector<double> data;

    DenseMatrix(size_t r, size_t c) : rows(r), cols(c), data(r * c) {}

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

    double& operator()(size_t r, size_t c) {
        return data[r * cols + c];
    }

    const double& operator()(size_t r, size_t c) const {
        return data[r * cols + c];
    }

    bool operator==(const DenseMatrix& other) const {
        return rows == other.rows && cols == other.cols && data == other.data;
    }
};

} // namespace sparsematrix

#endif // DENSEMATRIX_H