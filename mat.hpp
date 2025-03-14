#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath> 

using namespace std;

class Matrix {
private:
    int r,c; 
    vector<vector<int>> matrix; 
    vector<vector<double>> a; 
    vector<double> sol; 

public:
    Matrix(); 
    void readFile(const string filename); 
    void display() ; 
    Matrix add(const Matrix other) ; 
    Matrix subtract(const Matrix other); 
    bool isIdentity() ; 
    void eliminate(); 
    void backSubstitute(); 
    void printSolution() ; 
    void luDecomposition() ;
};
