#include "root.hpp"

int main() {
    Root rootSolver;
    
    double a, b;
    rootSolver.bisection(a, b);

    double x0;
    rootSolver.newtonRaphson(x0);

    double xn;
    rootSolver.FixedPoint(xn);

    return 0;
}
