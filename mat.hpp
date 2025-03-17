#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath> 

using namespace std;

class Matrix {
private:
    int r, c;  // Number of rows and columns
    vector<vector<int>> matrix; 
    vector<vector<double>> a; 
    vector<double> sol; 

public:
    Matrix(); 
    void readFile(const string filename); 
    void display(); 
    Matrix add(Matrix& other); 
    Matrix subtract(Matrix& other); 
    bool isIdentity(); 
    void eliminate(); 
    void backSubstitute(); 
    void printSolution(); 
    void Doolittle();
    void cholesky();
    void crout();
};
