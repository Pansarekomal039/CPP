#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <stdexcept>
#include <algorithm>

using namespace std;

class Matrix {
private:
    int r, c;
    vector<vector<double>> matrix;
    vector<double> solution;

    bool isDiagonallyDominant() const;

public:
    Matrix();
    Matrix(int r, int c);
    void readFile(const string& filename);
    void readAugmentedMatrix(const string& filenameA, const string& filenameB);
    void display() const;
    void displaySolution() const;
    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    bool isIdentity() const;
    void eliminate();
    void backSubstitute();
    void Doolittle();
    void crout();
    Matrix gaussJacobi(int maxIterations = 1000, double tolerance = 1e-6);
    Matrix gaussSeidel(int maxIterations = 1000, double tolerance = 1e-6);
};