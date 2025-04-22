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
    try {
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
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    cout << "\nEnter the filename for the Gaussian elimination matrix: ";
    cin >> gaussFileA;

    cout << "Enter the filename for the augmented column: ";
    cin >> gaussFileB;

    Matrix gaussMatrix;
    gaussMatrix.readAugmentedMatrix(gaussFileA, gaussFileB);
    
    cout << "\nOriginal Augmented Matrix:\n";
    gaussMatrix.display();
    
    cout << "\nPerforming Gaussian Elimination...\n";
    gaussMatrix.eliminate();
    
    cout << "\nPerforming Back Substitution...\n";
    gaussMatrix.backSubstitute();
    gaussMatrix.displaySolution();

    string luFileA;
    cout << "\nEnter the filename for LU decomposition matrix: ";
    cin >> luFileA;

    Matrix luMatrix;
    luMatrix.readFile(luFileA);
    
    cout << "\nOriginal Matrix for LU Decomposition:\n";
    luMatrix.display();
    
    cout << "\nPerforming Doolittle LU Decomposition...\n";
    luMatrix.Doolittle();
    
    cout << "\nPerforming Crout's LU Decomposition...\n";
    luMatrix.crout();

    string iterFileA;
    cout << "\nEnter the filename for iterative method matrix: ";
    cin >> iterFileA;

    Matrix iterMatrix;
    iterMatrix.readFile(iterFileA);
    
    cout << "\nOriginal Augmented Matrix for Iterative Methods:\n";
    iterMatrix.display();
    
    cout << "\nPerforming Gauss-Jacobi Method...\n";
    Matrix Jacobi = iterMatrix.gaussJacobi();
    Jacobi.displaySolution();
    
    cout << "\nPerforming Gauss-Seidel Method...\n";
    Matrix Seidel = iterMatrix.gaussSeidel();
    Seidel.displaySolution();

    return 0;
}