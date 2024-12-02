#include "SparseMatrix.h"
#include "DenseMatrix.h"
#include <iostream>
#include <vector>
#include <stdexcept>

int main() {
    try {
        // Create a DenseMatrix instance
        sparsematrix::DenseMatrix denseMatrix(20, 20);

        // Fill the DenseMatrix with values
        for (int i = 0; i < 20; ++i) {
            denseMatrix(i, i) = i + 1;
            if (i < 19) denseMatrix(i, i + 1) = 0.5;
        }

        // Convert DenseMatrix to CSR format
        sparsematrix::SparseMatrix* csr = sparsematrix::SparseMatrix::fromDense(denseMatrix, "CSR");
        std::cout << "Converted to CSR format\n";
        std::cout << "CSR Matrix: NNZ = " << csr->getNNZ() << ", Shape = (" << csr->getShape().first << ", " << csr->getShape().second << ")\n";
        delete csr;

        // Convert DenseMatrix to CSC format
        sparsematrix::SparseMatrix* csc = sparsematrix::SparseMatrix::fromDense(denseMatrix, "CSC");
        std::cout << "Converted to CSC format\n";
        std::cout << "CSC Matrix: NNZ = " << csc->getNNZ() << ", Shape = (" << csc->getShape().first << ", " << csc->getShape().second << ")\n";
        delete csc;

        // Convert DenseMatrix to COO format
        sparsematrix::SparseMatrix* coo = sparsematrix::SparseMatrix::fromDense(denseMatrix, "COO");
        std::cout << "Converted to COO format\n";
        std::cout << "COO Matrix: NNZ = " << coo->getNNZ() << ", Shape = (" << coo->getShape().first << ", " << coo->getShape().second << ")\n";
        delete coo;

        // Convert DenseMatrix to Diagonal format
        sparsematrix::SparseMatrix* diag = sparsematrix::SparseMatrix::fromDense(denseMatrix, "Diagonal");
        std::cout << "Converted to Diagonal format\n";
        std::cout << "Diagonal Matrix: NNZ = " << diag->getNNZ() << ", Shape = (" << diag->getShape().first << ", " << diag->getShape().second << ")\n";
        delete diag;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }

    return 0;
}