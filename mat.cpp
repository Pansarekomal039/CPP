#include "mat.hpp"

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
            if (isnan(val))
                cout << setw(12) << "NaN" << " ";
            else
                cout << setw(12) << setprecision(6) << fixed << val << " ";
        }
        cout << endl;
    }
}

void Matrix::displaySolution() const {
    if (solution.empty()) {
        cout << "Solution not yet computed." << endl;
        return;
    }
    cout << "Solution:" << endl;
    for (size_t i = 0; i < solution.size(); i++) {
        cout << "x[" << i << "] = " << setprecision(10) << solution[i] << endl;
    }
}

Matrix Matrix::add(const Matrix& other) const {
    if (r != other.r || c != other.c) {
        throw runtime_error("Error: Matrix dimensions don't match for addition");
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
        throw runtime_error("Error: Matrix dimensions don't match for subtraction");
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
            if ((i == j && fabs(matrix[i][j] - 1.0) > 1e-9) || 
                (i != j && fabs(matrix[i][j]) > 1e-9)) {
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
        double maxVal = fabs(matrix[i][i]);
        for (int k = i + 1; k < r; k++) {
            if (fabs(matrix[k][i]) > maxVal) {
                maxVal = fabs(matrix[k][i]);
                maxRow = k;
            }
        }
        
        if (maxRow != i) {
            swap(matrix[i], matrix[maxRow]);
        }

        // Skip if pivot is zero (or very small)
        if (fabs(matrix[i][i]) < 1e-12) {
            continue;
        }

        // Elimination
        for (int j = i + 1; j < r; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < c; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
    cout << "\nUpper Triangular Matrix after Gaussian Elimination:\n";
    display();
}

void Matrix::backSubstitute() {
    solution.resize(r);
    for (int i = r - 1; i >= 0; i--) {
        if (fabs(matrix[i][i]) < 1e-12) {
            if (fabs(matrix[i][c-1]) < 1e-12) {
                cerr << "System has infinitely many solutions." << endl;
            } else {
                cerr << "System has no solution." << endl;
            }
            solution.clear();
            return;
        }
        
        solution[i] = matrix[i][c-1];
        for (int j = i + 1; j < r; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
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
    cout << "\nDoolittle LU Decomposition\n";
    cout << "Lower Triangular Matrix (L):\n";
    L.display();
    cout << "Upper Triangular Matrix (U):\n";
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

bool Matrix::isDiagonallyDominant() const {
    for (int i = 0; i < r; i++) {
        double sum = 0.0;
        for (int j = 0; j < r; j++) {
            if (j != i) sum += fabs(matrix[i][j]);
        }
        if (fabs(matrix[i][i]) <= sum) return false;
    }
    return true;
}

Matrix Matrix::gaussJacobi(int maxIterations, double tolerance) {
    if (r != c) {  
        cerr << "Error: Matrix must be square\n";
        return;
    }

    if (!isDiagonallyDominant()) {
        cout << "Matrix is not diagonally dominant\n";
    }

    // vector<double> x(r, 0.0);     
    // vector<double> newX(r, 0.0);  
    Matrix x(r,1);
    Matrix newX(r,1);
    
    int iterations = 0;          
    double error = tolerance + 1; 

    cout << "Iterations:\n";
    while (iterations < maxIterations && error > tolerance) {
        error = 0.0;
        cout << "Iteration " << iterations + 1 << ": ";

        for (int i = 0; i < r; i++) {
            double sum = 0.0;
            for (int j = 0; j < r; j++) {
                if (j != i) {
                    sum += matrix[i][j] * x.matrix[j][0];
                }
            }
            newX[i] = (matrix[i][r] - sum) / matrix[i][i];
            error += fabs(newX.matrix[i][0] - x.matrix[i][0]);

            // cout << "x[" << i << "]=" << setprecision(6) << newX[i] << " ";
        }

        x = newX;
        cout << endl;
        iterations++;
    }

    return x;
    
    cout << "\nGauss-Jacobi Method\n";
    cout << "Total iterations: " << iterations << endl;
    cout << "Final error: " << error << endl;
}


Matrix Matrix::gaussSeidel(int maxIterations, double tolerance) {
    if (r != c) {
        cerr << "Error: Matrix must be square\n";
        return;
    }

    if (!isDiagonallyDominant()) {
        cout << "Warning: Matrix is not diagonally dominant. Convergence not guaranteed.\n";
    }

    for (int i = 0; i < r; i++) {
        sol[i] = 0.0;
    }

    int iterations = 0;
    double error = tolerance + 1;

    cout << "Iterations:\n";
    while (iterations < maxIterations && error > tolerance) {
        error = 0.0;

        cout << "Iteration " << iterations + 1 << ": ";

        for (int i = 0; i < r; i++) {
            double sum = 0.0;

            for (int j = 0; j < r; j++) {
                if (j != i) {
                    sum += matrix[i][j] * sol[j];
                }
            }

            double newX = (matrix[i][r] - sum) / matrix[i][i];
            error += fabs(newX - sol[i]);  

            solution[i] = newX; 

            cout << "x[" << i << "]=" << setprecision(6) << sol[i] << " ";
        }

        cout << endl;
        iterations++;
    }

    cout << "\nGauss-Seidel Method\n";
    cout << "Total iterations: " << iterations << endl;
    cout << "Final error: " << error << endl;
}
