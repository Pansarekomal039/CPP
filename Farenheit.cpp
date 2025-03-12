#include<iostream>
using namespace std;
int main()
{
float c,f;
cout << "Enter the temperature in Celcius" << endl;
cin >> c;
f=c*(9/5.0)+32;
cout << "Fahrenheit = " << f << endl;
return 0;
}


#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <fstream>

class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<int>> data;

public:
    Matrix(int r, int c);  
    void readFromFile(const std::string& filename);
    void display() const;
    Matrix add(const Matrix& mat) const;
    Matrix subtract(const Matrix& mat) const;
    bool isIdentity() const;
};

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

Matrix Matrix::add(const Matrix& mat) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + mat.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::subtract(const Matrix& mat) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - mat.data[i][j];
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
    Matrix add = A.add(B);
    add.display();

    cout << "\nMatrix A - Matrix B:\n";
    Matrix sub = A.subtract(B);
    sub.display();

    cout << "\nChecking if Matrix A is an identity matrix: " << (A.isIdentity() ? "Yes" : "No") << endl;
    cout << "Checking if Matrix B is an identity matrix: " << (B.isIdentity() ? "Yes" : "No") << endl;

    return 0;
}
