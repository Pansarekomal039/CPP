#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Matrix {
private:
    int rows, cols;
    vector<vector<int>> mat;
    vector<vector<double>> augmentedMatrix;  
    vector<double> sol;  

public:
    Matrix(int r, int c);  
    void readFromFile(const string& filename);  
    void display(); 
    Matrix add(const Matrix& Mat);  
    Matrix subtract(const Matrix& Mat);  
    bool isIdentity();  
    void eliminate();  
    void backSubstitute();  
    void printSolution();  
};

