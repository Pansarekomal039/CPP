#ifndef MAT_HPP
#define MAT_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;
class Matrix {
private:
    int r, c; // Number of rows and columns
    vector<vector<double>> matrix; // Matrix data
    vector<double> sol; // Solution vector

public:
    Matrix(); // Constructor
    void readFile(const string& filename); // Read matrix from file
    void readAugmentedMatrix(const string& filenameA, const string& filenameB); // Read augmented matrix
    void display() const; // Display matrix
    Matrix add(const Matrix& other) const; // Matrix addition
    Matrix subtract(const Matrix& other) const; // Matrix subtraction
    bool isIdentity() const; // Check if matrix is identity
    void eliminate(); // Gaussian elimination
    void backSubstitute(); // Back substitution
    void printSolution() const; // Print solution
    void Doolittle() const; // Doolittle LU decomposition
    void crout() const; // Crout's LU decomposition
    void cholesky() const; // Cholesky decomposition
};

#endif
