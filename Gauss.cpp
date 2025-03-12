#include "Gauss.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
using namespace std;

void Gauss::readMatrix() {
    string filename;
    cout << "Enter the filename containing the augmented matrix: ";
    cin >> filename;

    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
    }

    file >> n >> m; 
    
    augmentedMatrix = vector<vector<double>>(n, vector<double>(m)); 

    cout << "Reading matrix from file: " << filename << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            file >> augmentedMatrix[i][j];
        }
    }
    
    file.close();
}

void Gauss::eliminate() {
    for(int i = 0; i < n - 1; i++) {
        if(fabs(augmentedMatrix[i][i]) < 0.0001) {
            cerr << "Mathematical Error: Division by zero!" << endl;
            exit(EXIT_FAILURE);
        }

        for(int j = i + 1; j < n; j++) {
            double i = augmentedMatrix[j][i] / augmentedMatrix[i][i];
            for(int k = 0; k < m; k++) {  
                augmentedMatrix[j][k] -= i * augmentedMatrix[i][k];
            }
        }
    }
}

void Gauss::backSubstitute() {
    sol = vector<double>(n);

    sol[n - 1] = augmentedMatrix[n - 1][m - 1] / augmentedMatrix[n - 1][n - 1];  

    for(int i = n - 2; i >= 0; i--) {
        sol[i] = augmentedMatrix[i][m - 1];  
        for(int j = i + 1; j < n; j++) {
            sol[i] -= augmentedMatrix[i][j] * sol[j];
        }
        sol[i] /= augmentedMatrix[i][i];
    }
}

void Gauss::printSolution() {
    cout << setprecision(3) << fixed;
    cout << "\nSolution:\n";
    for(int i = 0; i < n; i++) {
        cout << "x[" << i + 1 << "] = " << sol[i] << endl;
    }
}

