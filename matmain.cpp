#include "mat.hpp"
#include <iostream>

using namespace std;

int main() {
    string filenameA, filenameB;

    cout << "Enter the filename for Matrix A: ";
    cin >> filenameA;

    cout << "Enter the filename for Matrix B: ";
    cin >> filenameB;

    Matrix A, B; 

    cout << "Matrix A" << endl;
    A.readFile(filenameA);
    cout << "Matrix A:\n";
    A.display();

    cout << "\nMatrix B" << endl;
    B.readFile(filenameB);
    cout << "Matrix B:\n";
    B.display();

    cout << "\nMatrix A + Matrix B:\n";
    Matrix add = A.add(B);
    add.display();

    cout << "\nMatrix A - Matrix B:\n";
    Matrix sub = A.subtract(B);
    sub.display();

    cout << "\nIs Matrix A an identity matrix? " << (A.isIdentity() ? "Yes" : "No") << endl;
    cout << "Is Matrix B an identity matrix? " << (B.isIdentity() ? "Yes" : "No") << endl;

    cout << "\n Gaussian elimination " << endl;
    B.eliminate();
    B.backSubstitute();
    B.printSolution();

    cout << "\n LU Decomposition " << endl;
    A.Doolittle();
    A.crout();
    A.cholesky();

    return 0;
}
