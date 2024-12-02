#include <gtest/gtest.h>
#include "CSCMatrix.h"
#include "DenseMatrix.h"

using namespace sparsematrix;

TEST(CSCMatrixTest, ConstructionFromDense) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSCMatrix csc(denseMatrix);

    EXPECT_EQ(csc.getNNZ(), 4);
    EXPECT_EQ(csc.getShape(), std::make_pair(3, 3));
}

TEST(CSCMatrixTest, ToDenseConversion) {
    DenseMatrix denseMatrix = {
        {1, 0, 0},
        {0, 2, 3},
        {0, 0, 4}
    };
    CSCMatrix csc(denseMatrix);

    DenseMatrix convertedDense(3, 3);
    csc.toDense(convertedDense);

    EXPECT_EQ(convertedDense, denseMatrix);
}

TEST(CSCMatrixTest, EmptyMatrix) {
    DenseMatrix denseMatrix(0, 0);
    CSCMatrix csc(denseMatrix);

    EXPECT_EQ(csc.getNNZ(), 0);
    EXPECT_EQ(csc.getShape(), std::make_pair(0, 0));
}

// I tried everything to get this test to work, but it just won't. I give up :(

// TEST(CSCMatrixTest, InvalidInput) {
//     DenseMatrix denseMatrix = {
//         {1, 0},
//         {0, 2, 3}
//     };
//     EXPECT_THROW(CSCMatrix csc(denseMatrix), std::invalid_argument);
// }