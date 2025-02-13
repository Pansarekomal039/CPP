#include "mat.hpp"

using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(rows, vector<int>(cols, 0));  
}

void Matrix::inputMatrix() {
    cout << "Enter elements for a " << rows << "x" << cols << " matrix:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> data[i][j];
        }
    }
}

void Matrix::displayMatrix() const {
    cout << "Matrix:\n";
    for (const auto& row : data) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::add(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        cerr << "Error: Matrices must have the same dimensions for addition.\n";
        exit(1);
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::subtract(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        cerr << "Error: Matrices must have the same dimensions for subtraction.\n";
        exit(1);
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

bool Matrix::isIdentity() const {
    if (rows != cols) return false;  

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if ((i == j && data[i][j] != 1) || (i != j && data[i][j] != 0))
                return false;
        }
    }
    return true;
}
