#include "mat.hpp"
#include <iostream>

using namespace std;

int main() {
    Matrix A(3, 3);  
    Matrix B(3, 3); 

    cout << "Reading Matrix A from file..." << endl;
    A.readFromFile("matrixA.txt");
    cout << "Matrix A:\n";
    A.display();

    cout << "\nReading Matrix B from file..." << endl;
    B.readFromFile("matrixB.txt");
    cout << "Matrix B:\n";
    B.display();

    cout << "\nMatrix A + Matrix B:\n";
    Matrix add = A.add(B);
    add.display();

    cout << "\nMatrix A - Matrix B:\n";
    Matrix sub = A.subtract(B);
    sub.display();

    cout << "\nChecking if Matrix A is an identity matrix: " << (A.isIdentity() ? "Yes" : "No") << endl;
    cout << "Checking if Matrix B is an identity matrix: " << (B.isIdentity() ? "Yes" : "No") << endl;

    cout << "\n Gaussian elimination on Matrix A\n";
    A.eliminate();

    cout << "\nback substitution on Matrix A\n";
    A.backSubstitute();
    A.printSolution();

    return 0;
}
