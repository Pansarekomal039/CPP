#include <iostream>
#include <string>
#include "mat.hpp"
using namespace std;

int main() {
    string filenameA, filenameB, gaussFileA, gaussFileB;

    // Input for regular matrices
    cout << "Enter the filename for Matrix A: ";
    cin >> filenameA;

    cout << "Enter the filename for Matrix B: ";
    cin >> filenameB;

    Matrix A, B;
    A.readFile(filenameA);
    B.readFile(filenameB);

    cout << "\nMatrix A:\n";
    A.display();

    cout << "\nMatrix B:\n";
    B.display();

    cout << "\nMatrix A + Matrix B:\n";
    Matrix add = A.add(B);
    add.display();

    cout << "\nMatrix A - Matrix B:\n";
    Matrix sub = A.subtract(B);
    sub.display();

    cout << "\nIs Matrix A an identity matrix? " << (A.isIdentity() ? "Yes" : "No") << endl;
    cout << "Is Matrix B an identity matrix? " << (B.isIdentity() ? "Yes" : "No") << endl;

    // Input for Gaussian elimination matrices
    cout << "\nEnter the filename for the Gaussian elimination matrix: ";
    cin >> gaussFileA;

    cout << "Enter the filename for the augmented column: ";
    cin >> gaussFileB;

    cout << "\nGaussian elimination:\n";
    Matrix gaussMatrix;
    gaussMatrix.readAugmentedMatrix(gaussFileA, gaussFileB);
    gaussMatrix.eliminate();
    gaussMatrix.backSubstitute();
    gaussMatrix.printSolution();

    cout << "\nLU Decomposition:\n";
    A.Doolittle();
    A.crout();
    A.cholesky();

    return 0;
}
