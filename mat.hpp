#ifndef MATRIX_HPP
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
    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const;
    bool isIdentity() const;
};

#endif 
