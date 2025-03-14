#include "mat.hpp"

Matrix::Matrix() {
    r = 0;
    c = 0;
}

void Matrix::readFile(const string fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: Could not open file " << fileName << endl;
        exit(1);
    }

    file >> r >> c;
    
    matrix = vector<vector<int>>(r, vector<int>(c));
    a = vector<vector<double>>(r, vector<double>(c));
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int value;
            file >> value;
            matrix[i][j] = value;
            a[i][j] = value;
        }
    }
    file.close();
}

void Matrix::display() const {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::add(const Matrix other) const {
    Matrix res;
    res.r = r;
    res.c = c;
    res.matrix = vector<vector<int>>(r, vector<int>(c));
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return res;
}

Matrix Matrix::subtract(const Matrix other) const {
    Matrix res;
    res.r = r;
    res.c = c;
    res.matrix = vector<vector<int>>(r, vector<int>(c));
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    return res;
}

bool Matrix::isIdentity() const {
    if (r != c) return false;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if ((i == j && matrix[i][j] != 1) || (i != j && matrix[i][j] != 0)) {
                return false;
            }
        }
    }
    return true;
}

void Matrix::eliminate() {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            double i = a[j][i] / a[i][i];
            for(int k = 0; k < m; k++) {  
                a[j][k] -= i * a[i][k];
            }
        }
    }
}

void Matrix::backSubstitute() {
    sol = vector<double>(n);

    sol[n - 1] = a[n - 1][m - 1] / a[n - 1][n - 1];  

    for(int i = n - 2; i >= 0; i--) {
        sol[i] = a[i][m - 1];  
        for(int j = i + 1; j < n; j++) {
            sol[i] -= a[i][j] * sol[j];
        }
        sol[i] /= a[i][i];
    }
}


void Matrix::printSolution() const {
    if (sol.empty()) {
        cerr << "No solution found. Matrix is singular." << endl;
        return;
    }

    cout << setprecision(3) << fixed;
    cout << "\nSolution:\n";
    for (int i = 0; i < r; ++i) {
        cout << "x[" << i + 1 << "] = " << sol[i] << endl;
    }
}

void Matrix::luDecomposition() const {
    vector<vector<double>> L(r, vector<double>(c, 0));
    vector<vector<double>> U(r, vector<double>(c, 0));

    for (int i = 0; i < r; ++i) {
        for (int k = i; k < c; ++k) {
            double sum = 0;
            for (int j = 0; j < i; ++j) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = matrix[i][k] - sum;
        }

        for (int k = i; k < r; ++k) {
            if (i == k) {
                L[i][i] = 1; 
            } else {
                double sum = 0;
                for (int j = 0; j < i; ++j) {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (matrix[k][i] - sum) / U[i][i];
            }
        }
    }

    cout << "\nLower Triangular Matrix\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << L[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nUpper Triangular Matrix\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << U[i][j] << " ";
        }
        cout << endl;
    }
}