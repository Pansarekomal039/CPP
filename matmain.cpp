#include "mat.hpp"

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
    Matrix sum = A.add(B);
    sum.display();

    cout << "\nMatrix A - Matrix B:\n";
    Matrix diff = A.subtract(B);
    diff.display();

    cout << "\nChecking if Matrix A is an identity matrix: " << (A.isIdentity() ? "Yes" : "No") << endl;
    cout << "Checking if Matrix B is an identity matrix: " << (B.isIdentity() ? "Yes" : "No") << endl;

    return 0;
}
