#ifndef ROOT_HPP
#define ROOT_HPP

#include <iostream>
#include <cmath>
#include <iomanip>

class Root {
public:
    // Constructor
    Root();

    // Function definitions
    static double f(double x);
    static double f_derivative(double x);
    static double g(double x);

    // Root-finding methods
    void bisection(double a, double b);
    void newtonRaphson(double x0);
    void FixedPoint(double x0);
};

#endif // ROOT_HPP
