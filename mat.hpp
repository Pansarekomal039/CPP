#ifndef MAT_HPP
#define MAT_HPP

#include <iostream>
#include <vector>

class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<int>> data;

public:
    Matrix(int r, int c);

    void inputMatrix();

    void displayMatrix() const;

    Matrix add(const Matrix& other) const;

    Matrix subtract(const Matrix& other) const;

    bool isIdentity() const;
};

#endif 
