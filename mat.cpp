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

void Matrix::display() {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::add(Matrix& other) {
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

Matrix Matrix::subtract(Matrix& other) {
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

bool Matrix::isIdentity() {
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
    for (int i = 0; i < r - 1; i++) {  
        if (a[i][i] == 0) {
            cout << "Pivot is zero, swapping rows...\n";
            for (int j = i + 1; j < r; j++) {
                if (a[j][i] != 0) {
                    swap(a[i], a[j]);  
                    break;
                }
            }
        }
        for (int j = i + 1; j < r; j++) {   
            for (int k = i; k < c; k++) {  
                a[j][k] -= (a[j][i] / a[i][i]) * a[i][k];
            }
        }
        cout << "Step " << i + 1 << ":\n";
        for (int x = 0; x < r; x++) {
            for (int y = 0; y < c; y++) {
                cout << setw(8) << setprecision(3) << fixed << a[x][y] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

void Matrix::backSubstitute() {
    sol = vector<double>(r);

    sol[r - 1] = a[r - 1][c - 1] / a[r - 1][r - 1];  

    for (int i = r - 2; i >= 0; i--) {
        sol[i] = a[i][c - 1];  
        for (int j = i + 1; j < r; j++) {
            sol[i] -= a[i][j] * sol[j];
        }
        sol[i] /= a[i][i];
    }
}

void Matrix::printSolution() {
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

void Matrix::Doolittle() {
    vector<vector<double>> L(r, vector<double>(r, 0));
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

    cout << "\nLower Triangular Matrix (L)\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < r; ++j) {
            cout << setw(8) << setprecision(3) << fixed << L[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nUpper Triangular Matrix (U)\n";
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << setw(8) << setprecision(3) << fixed << U[i][j] << " ";
        }
        cout << endl;
    }
}

void Matrix::crout() {
    vector<vector<double>> L(r, vector<double>(r, 0));
    vector<vector<double>> U(r, vector<double>(c, 0));

    for (int i = 0; i < r; ++i)
        U[i][i] = 1;

    for (int j = 0; j < r; ++j) {
        for (int i = j; i < r; ++i) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L[i][k] * U[k][j];
            L[i][j] = matrix[i][j] - sum;
        }

        for (int i = j; i < r; ++i) {
            double sum = 0;
            for (int k = 0; k < j; ++k)
                sum += L[j][k] * U[k][i];
            U[j][i] = (matrix[j][i] - sum) / L[j][j];
        }
    }

    cout << "\nCrout's LU Decomposition\n";
    cout << "Lower Triangular Matrix (L):\n";
    for (const auto &row : L) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }

    cout << "Upper Triangular Matrix (U):\n";
    for (const auto &row : U) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }
}


void Matrix::cholesky() {
    vector<vector<double>> L(r, vector<double>(r, 0));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;

            if (j == i) {
                for (int k = 0; k < j; k++)
                    sum += L[j][k] * L[j][k];
                L[j][j] = sqrt(matrix[j][j] - sum);
            } else {
                for (int k = 0; k < j; k++)
                    sum += L[i][k] * L[j][k];
                L[i][j] = (matrix[i][j] - sum) / L[j][j];
            }
        }
    }

    cout << "\nCholesky Decomposition\n";
    cout << "Lower Triangular Matrix (L):\n";
    for (const auto &row : L) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }

    cout << "Upper Triangular Matrix (U = L^T):\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            cout << L[j][i] << " "; 
        }
        cout << endl;
    }
}
