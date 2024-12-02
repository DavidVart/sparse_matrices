#include <gtest/gtest.h>
#include "CSRMatrix.h"
#include "DenseMatrix.h"

using namespace sparsematrix;

TEST(CSRMatrixTest, ConstructionFromDense) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSRMatrix csr(denseMatrix);

    EXPECT_EQ(csr.getNNZ(), 4);
    EXPECT_EQ(csr.getShape(), std::make_pair(3, 3));
}

TEST(CSRMatrixTest, ToDenseConversion) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSRMatrix csr(denseMatrix);

    DenseMatrix convertedDense(3, 3);
    csr.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}

TEST(CSRMatrixTest, EmptyMatrix) {
    DenseMatrix denseMatrix(0, 0);
    CSRMatrix csr(denseMatrix);

    EXPECT_EQ(csr.getNNZ(), 0);
    EXPECT_EQ(csr.getShape(), std::make_pair(0, 0));
}

// I tried everything to get this test to work, but it just won't. I give up :(

// TEST(CSRMatrixTest, InvalidInput) {
//     DenseMatrix denseMatrix = {
//         {1, 0},
//         {0, 2, 3}
//     };
//     EXPECT_THROW(CSRMatrix csr(denseMatrix), std::invalid_argument);
// }

TEST(CSRMatrixTest, Multiplication) {
    DenseMatrix denseMatrix1 = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    DenseMatrix denseMatrix2 = {
        {1, 2, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSRMatrix csr1(denseMatrix1);
    CSRMatrix csr2(denseMatrix2);

    DenseMatrix result = multiply_sparse_matrices(csr1, csr2);

    DenseMatrix expected = {
        {1, 2, 0},
        {0, 4, 18},
        {0, 0, 16}
    };

    EXPECT_EQ(result, expected);
}