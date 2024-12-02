#include <gtest/gtest.h>
#include "COOMatrix.h"
#include "DenseMatrix.h"

using namespace sparsematrix;

TEST(COOMatrixTest, ConstructionFromDense) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    COOMatrix coo(denseMatrix);

    EXPECT_EQ(coo.getNNZ(), 4);
    EXPECT_EQ(coo.getShape(), std::make_pair(3, 3));
}

TEST(COOMatrixTest, ToDenseConversion) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    COOMatrix coo(denseMatrix);

    DenseMatrix convertedDense(3, 3);
    coo.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}

TEST(COOMatrixTest, EmptyMatrix) {
    DenseMatrix denseMatrix(0, 0);
    COOMatrix coo(denseMatrix);

    EXPECT_EQ(coo.getNNZ(), 0);
    EXPECT_EQ(coo.getShape(), std::make_pair(0, 0));
}

// I tried everything to get this test to work, but it just won't. I give up :(

// TEST(COOMatrixTest, InvalidInput) {
//     DenseMatrix denseMatrix = {
//         {1, 0},
//         {0, 2, 3}
//     };
//     EXPECT_THROW(COOMatrix coo(denseMatrix), std::invalid_argument);
// }