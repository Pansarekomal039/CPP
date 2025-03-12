#include "mat.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
    
Matrix::Matrix(int r, int c) : rows(r), cols(c), 
mat(r, vector<int>(c)),      
augmentedMatrix(r, vector<double>(c + 1)) {}

    
void Matrix::readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Could not open file " << filename << endl;
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> mat[i][j];
        }
    }
    file.close();
}

void Matrix::display() {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::add(const Matrix& Mat) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.mat[i][j] = mat[i][j] + Mat.mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::subtract(const Matrix& Mat) {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.mat[i][j] = mat[i][j] - Mat.mat[i][j];
        }
    }
    return result;
}

bool Matrix::isIdentity() {
    if (rows != cols) return false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i == j && mat[i][j] != 1) || (i != j && mat[i][j] != 0)) {
                return false;
            }
        }
    }
    return true;
}

void Matrix::eliminate() {
    for (int i = 0; i < rows - 1; i++) {
        if (fabs(augmentedMatrix[i][i]) < 0.0001) {
            cerr << "Error" << endl;
        }

        for (int j = i + 1; j < rows; j++) {
            double factor = augmentedMatrix[j][i] / augmentedMatrix[i][i];
            for (int k = 0; k < cols; k++) {
                augmentedMatrix[j][k] -= factor * augmentedMatrix[i][k];
            }
        }
    }
}

void Matrix::backSubstitute() {
    sol = vector<double>(rows);

    sol[rows - 1] = augmentedMatrix[rows - 1][cols] / augmentedMatrix[rows - 1][rows - 1];

    for (int i = rows - 1; i >= 0; i--) {
        sol[i] = augmentedMatrix[i][cols-1];
        for (int j = i + 1; j < rows; j++) {
            sol[i] -= augmentedMatrix[i][j] * sol[j];
        }
        sol[i] /= augmentedMatrix[i][i];
    }
}

void Matrix::printSolution() {
    cout << setprecision(3) << fixed;
    cout << "\nSolution:\n";
    for (int i = 0; i < rows; i++) {
        cout << "x[" << i + 1 << "] = " << sol[i] << endl;
    }
}
