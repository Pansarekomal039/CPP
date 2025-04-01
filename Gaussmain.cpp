#include "Gauss.hpp"

int main() {
    Gauss solver;
    solver.readMatrix();
    solver.eliminate();
    solver.backSubstitute();
    solver.printSolution();
    
    return 0; 
}