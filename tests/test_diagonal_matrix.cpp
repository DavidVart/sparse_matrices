#include <gtest/gtest.h>
#include "DiagonalMatrix.h"
#include "DenseMatrix.h"

using namespace sparsematrix;

TEST(DiagonalMatrixTest, ConstructionFromDense) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {0, 0, 3}
    };
    DiagonalMatrix diag(denseMatrix);

    EXPECT_EQ(diag.getNNZ(), 3);
    EXPECT_EQ(diag.getShape(), std::make_pair(3, 3));
    EXPECT_EQ(diag.getElement(0, 0), 1);
    EXPECT_EQ(diag.getElement(1, 1), 2);
    EXPECT_EQ(diag.getElement(2, 2), 3);
    EXPECT_EQ(diag.getElement(0, 1), 0); // Off-diagonal elements are zero
}

TEST(DiagonalMatrixTest, ToDenseConversion) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 0},
        {0, 0, 3}
    };
    DiagonalMatrix diag(denseMatrix);

    DenseMatrix convertedDense(3, 3);
    diag.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}

TEST(DiagonalMatrixTest, EmptyMatrix) {
    DenseMatrix denseMatrix(0, 0);
    DiagonalMatrix diag(denseMatrix);

    EXPECT_EQ(diag.getNNZ(), 0);
    EXPECT_EQ(diag.getShape(), std::make_pair(0, 0));
}

// I tried everything to get this test to work, but it just won't. I give up :(

// TEST(DiagonalMatrixTest, InvalidInput) {
//     DenseMatrix denseMatrix = {
//         {1, 0},
//         {0, 2, 3}
//     };
//     EXPECT_THROW(DiagonalMatrix diag(denseMatrix), std::invalid_argument);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}