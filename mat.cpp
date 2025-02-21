#include "mat.hpp"
using namespace std;

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.resize(rows, vector<int>(cols, 0));
}

void Matrix::readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> data[i][j];
        }
    }
    file.close();
}

void Matrix::display() const {
    for (const auto& row : data) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::add(const Matrix& other) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::subtract(const Matrix& other) const {
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
            if ((i == j && data[i][j] != 1) || (i != j && data[i][j] != 0)) {
                return false;
            }
        }
    }
    return true;
}
