#include "mat.hpp"

using namespace std;

Matrix::Matrix() : r(0), c(0), matrix(0, vector<double>(0, 0)) {}

Matrix::Matrix(int r, int c) : r(r), c(c), matrix(r, vector<double>(c, 0)) {}

void Matrix::readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    file >> r >> c;
    matrix = vector<vector<double>>(r, vector<double>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
}
void Matrix::readAugmentedMatrix(const string& filenameA, const string& filenameB) {
    ifstream fileA(filenameA), fileB(filenameB);

    if (!fileA || !fileB) {
        cerr << "Error: File not found: " << filenameA << ", " << filenameB << endl;
        exit(1);
    }

    fileA >> r >> c;
    c += 1; 
    matrix = vector<vector<double>>(r, vector<double>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c - 1; j++) {
            fileA >> matrix[i][j];
        }
        fileB >> matrix[i][c - 1];
    }

    fileA.close();
    fileB.close();
}



void Matrix::display() const {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << setw(8) << setprecision(3) << fixed << val << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::add(const Matrix& other) const {
    if (r != other.r || c != other.c) {
        cerr << "Error: rows is not equal to column\n";
    }
    Matrix res(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return res;
}

Matrix Matrix::subtract(const Matrix& other) const {
    if (r != other.r || c != other.c) {
        cerr << "Error: rows is not equal to column\n";
    }
    Matrix res(r, c);
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
            if ((i == j && matrix[i][j] != 1.0) || (i != j && matrix[i][j] != 0.0)) {
                return false;
            }
        }
    }
    return true;
}

void Matrix::eliminate() {
    for (int i = 0; i < r; i++) {
        int maxRow = i;
        for (int k = i + 1; k < r; k++) {
            if (fabs(matrix[k][i]) > fabs(matrix[maxRow][i])) {
                maxRow = k;
            }
        }
        swap(matrix[i], matrix[maxRow]);

        for (int j = i + 1; j < r; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < c; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
    cout << "\nAugmented Matrix\n";
    display();
        
        for (int i = r - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1; j < c - 1; j++) {
                sum += matrix[i][j] * x[j];
            }
            x[i] = (matrix[i][c - 1] - sum) / matrix[i][i];
        }
    }
    


  

void Matrix::Doolittle() {
    if (r != c) {
        cerr << "Error: LU decomposition requires a square matrix\n";
        return;
    }
    Matrix L(r, c), U(r, c);

    for (int i = 0; i < r; i++) {
        for (int j = i; j < c; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L.matrix[i][k] * U.matrix[k][j];
            }
            U.matrix[i][j] = matrix[i][j] - sum;
        }
        for (int j = i; j < r; j++) {
            if (i == j) {
                L.matrix[i][i] = 1;
            } else {
                double sum = 0;  
                for (int k = 0; k < i; k++) {
                    sum += L.matrix[j][k] * U.matrix[k][i];
                }
                L.matrix[j][i] = (matrix[j][i] - sum) / U.matrix[i][i];
            }
        }
    }
    cout << "\nLower Triangular Matrix\n";
    L.display();
    cout << "\nUpper Triangular Matrix\n";
    U.display();
}

void Matrix::crout() {
    if (r != c) {
        cerr << "Error: LU decomposition requires a square matrix\n";
        return;
    }
    Matrix L(r, c), U(r, c);

    for (int i = 0; i < r; i++) {
        U.matrix[i][i] = 1;
        for (int j = i; j < c; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L.matrix[j][k] * U.matrix[k][i];
            }
            L.matrix[j][i] = matrix[j][i] - sum;
        }
        for (int j = i + 1; j < c; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L.matrix[i][k] * U.matrix[k][j];
            }
            U.matrix[i][j] = (matrix[i][j] - sum) / L.matrix[i][i];
        }
    }
    cout << "\nCrout's LU Decomposition\n";
    cout << "Lower Triangular Matrix (L):\n";
    L.display();
    cout << "Upper Triangular Matrix (U):\n";
    U.display();
}
