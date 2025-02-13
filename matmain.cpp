#include "mat.hpp"

using namespace std;

int main() {
    int r, c;
    
    cout << "Enter the number of rows and columns for the matrices: ";
    cin >> r >> c;

    Matrix A(r, c);
    Matrix B(r, c);

    cout << "Enter values for Matrix A:\n";
    A.inputMatrix();
    
    cout << "Enter values for Matrix B:\n";
    B.inputMatrix();

    Matrix sum = A.add(B);
    cout << "Matrix A + Matrix B:\n";
    sum.displayMatrix();

    Matrix diff = A.subtract(B);
    cout << "Matrix A - Matrix B:\n";
    diff.displayMatrix();

    cout << "Checking if Matrix A is an identity matrix: " << (A.isIdentity() ? "Yes" : "No") << endl;
    cout << "Checking if Matrix B is an identity matrix: " << (B.isIdentity() ? "Yes" : "No") << endl;

    return 0;
}
