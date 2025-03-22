#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;
class Matrix {
private:
    int r, c; 
    vector<vector<double>> matrix; 
    vector<double> x(r, 0);

public:
 Matrix();
    Matrix(int r,int c); 
    void readFile(const string& filename); 
    void readAugmentedMatrix(const string& filenameA, const string& filenameB); 
    void display() const; 
    Matrix add(const Matrix& other) const;
    Matrix subtract(const Matrix& other) const; 
    bool isIdentity() const; 
    void eliminate();
    void Doolittle(); 
    void crout(); 
};

