#include "mat.hpp"
using namespace std;

// Constructor initializes rows and columns to zero
Matrix::Matrix() : r(0), c(0) {}

// Read matrix from a file
void Matrix::readFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    file >> r >> c; // Read dimensions
    matrix.resize(r, vector<double>(c)); // Resize matrix

    // Read matrix data
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
        cerr << "Error: Could not open one or both files: " << filenameA << ", " << filenameB << endl;
        exit(1);
    }

    fileA >> r >> c; // Read dimensions from matrix file
    matrix.resize(r, vector<double>(c + 1)); // One extra column for augmented matrix

    // Read matrix data
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            fileA >> matrix[i][j];
        }
    }

    // Read augmented column from the second file
    for (int i = 0; i < r; i++) {
        fileB >> matrix[i][c]; // Augmented column goes into the last column
    }

    fileA.close();
    fileB.close();
}

// Display the matrix
void Matrix::display() const {
    for (const auto& row : matrix) {
        for (double val : row) {
            cout << setw(8) << setprecision(3) << fixed << val << " ";
        }
        cout << endl;
    }
}

// Add two matrices
Matrix Matrix::add(const Matrix& other) const {
    Matrix res;
    res.r = r;
    res.c = c;
    res.matrix.resize(r, vector<double>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
        }
    }
    return res;
}

// Subtract two matrices
Matrix Matrix::subtract(const Matrix& other) const {
    Matrix res;
    res.r = r;
    res.c = c;
    res.matrix.resize(r, vector<double>(c));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            res.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
        }
    }
    return res;
}

// Check if the matrix is an identity matrix
bool Matrix::isIdentity() const {
    if (r != c) return false; // Must be square

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
        // Partial pivoting
        int maxRow = i;
        for (int k = i + 1; k < r; k++) {
            if (fabs(matrix[k][i]) > fabs(matrix[maxRow][i])) {
                maxRow = k;
            }
        }

        // Swap rows
        if (maxRow != i) {
            swap(matrix[i], matrix[maxRow]);
        }

        // Check for zero pivot (matrix is singular)
        if (fabs(matrix[i][i]) < 1e-10) {
            cerr << "Error: Matrix is singular or nearly singular (zero pivot encountered)." << endl;
            return;
        }

        // Eliminate below the pivot
        for (int j = i + 1; j < r; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k <= c; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }

        // Debug: Print matrix after each step
        cout << "\nMatrix after step " << i + 1 << ":\n";
        display();
    }

    cout << "\nAugmented Matrix after Gaussian Elimination:\n";
    display();
}

void Matrix::backSubstitute() {
    sol.resize(r);
    for (int i = r - 1; i >= 0; i--) {
        if (fabs(matrix[i][i]) < 1e-10) {
            cerr << "Error: Matrix is singular or nearly singular (zero pivot encountered)." << endl;
            sol.clear();
            return;
        }

        sol[i] = matrix[i][c];
        for (int j = i + 1; j < r; j++) {
            sol[i] -= matrix[i][j] * sol[j];
        }
        sol[i] /= matrix[i][i];
    }
}
// Print the solution
void Matrix::printSolution() const {
    if (sol.empty()) {
        cerr << "No solution found. Matrix is singular." << endl;
        return;
    }

    cout << "\nSolution:\n";
    for (int i = 0; i < r; i++) {
        cout << "x[" << i + 1 << "] = " << sol[i] << endl;
    }
}

// Doolittle's LU decomposition
void Matrix::Doolittle() const {
    vector<vector<double>> L(r, vector<double>(r, 0));
    vector<vector<double>> U(r, vector<double>(r, 0));

    for (int i = 0; i < r; i++) {
        for (int j = i; j < r; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = matrix[i][j] - sum;
        }

        for (int j = i; j < r; j++) {
            if (i == j) {
                L[i][i] = 1; // Diagonal elements of L are 1
            } else {
                double sum = 0;
                for (int k = 0; k < i; k++) {
                    sum += L[j][k] * U[k][i];
                }
                L[j][i] = (matrix[j][i] - sum) / U[i][i];
            }
        }
    }

    cout << "\nLower Triangular Matrix (L):\n";
    for (const auto& row : L) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }

    cout << "\nUpper Triangular Matrix (U):\n";
    for (const auto& row : U) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }
}

// Crout's LU decomposition
void Matrix::crout() const {
    vector<vector<double>> L(r, vector<double>(r, 0));
    vector<vector<double>> U(r, vector<double>(r, 0));

    for (int i = 0; i < r; i++) {
        U[i][i] = 1; // Diagonal elements of U are 1
        for (int j = 0; j < r; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L[j][k] * U[k][i];
            }
            L[j][i] = matrix[j][i] - sum;
        }

        for (int j = i + 1; j < r; j++) {
            double sum = 0;
            for (int k = 0; k < i; k++) {
                sum += L[i][k] * U[k][j];
            }
            U[i][j] = (matrix[i][j] - sum) / L[i][i];
        }
    }

    cout << "\nCrout's LU Decomposition\n";
    cout << "Lower Triangular Matrix (L):\n";
    for (const auto& row : L) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }

    cout << "Upper Triangular Matrix (U):\n";
    for (const auto& row : U) {
        for (double val : row) cout << val << " ";
        cout << endl;
    }
}

// Cholesky decomposition
void Matrix::cholesky() const {
    vector<vector<double>> L(r, vector<double>(r, 0));

    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            if (j == i) {
                for (int k = 0; k < j; k++) {
                    sum += L[j][k] * L[j][k];
                }
                L[j][j] = sqrt(matrix[j][j] - sum);
            } else {
                for (int k = 0; k < j; k++) {
                    sum += L[i][k] * L[j][k];
                }
                L[i][j] = (matrix[i][j] - sum) / L[j][j];
            }
        }
    }

    cout << "\nCholesky Decomposition\n";
    cout << "Lower Triangular Matrix (L):\n";
    for (const auto& row : L) {
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