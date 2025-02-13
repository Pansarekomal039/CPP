#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f(double x) {
    return 4 * x * x * x - 3 * x;  
}

double f_derivative(double x) {
    return 12 * x * x - 3;  
}

double g(double x) {  
    return (x * x + 5) / 5;  
}


void bisection(double a, double b) {
   double x,fx,fa,fb;
   cout << fixed << setprecision(5);
   cout<< "Enter the value of a =";
   cin>> a;

   cout<< "Enter the value of b =";
   cin>> b;

   
   cout << "\nIteration\t  a\t\t b\t\t f(a)\t\t f(b)\t\t x\t\t f(x)" << endl;
   int iteration=1;
        fa=f(a);
        fb=f(b);
   do{
    x = (a+b)/2;
    fx=f(x);
      cout << iteration << "\t\t" << a << "\t" << b << "\t" << fa << "\t" << fb << "\t\t" << x << "\t" << fx << endl;

        if (fx < 0) {
            a = x;
            fa = fx;  
        } else {
            b = x;
            fb = fx;  
        }
      iteration++;

   }
    while(fabs(b-a) > 0.00001);
    
        cout<<"The root is" <<x <<endl;
      
}

void newtonRaphson(double x0) {
    double x, fx, fdx, x_next;
    const double tolerance = 0.00001;
    int iteration = 1;
    
    cout << "Enter the initial guess: ";
    cin >> x0;
    x = x0;

    cout << fixed << setprecision(5);
    cout << "\nIteration\t  x\t\t  f(x)\t\t  f'(x)" << endl;

    do {
        fx = f(x);
        fdx = f_derivative(x);

        if (fdx == 0) {
            cout << "Error: Derivative is zero" << endl;
            return;
        }

        x_next = x - (fx / fdx);  

        cout << iteration << "\t\t" << x << "\t" << fx << "\t" << fdx << endl;

        if (fabs(x_next - x) < tolerance)  
            break;

        x = x_next;
        iteration++;

    } while (true);

    cout << "\nApproximate Root from Newton-Raphson: " << x << endl;
}

void FixedPoint(double x0) {
const double tolerance = 0.00001;
    int maxIterations = 100;
    int iteration = 1;
    double x = x0, x_next;

    cout << "Enter the initial guess: ";
    cin >> x0;
    x = x0;

    cout << fixed << setprecision(5);
    cout << "\nIteration\t\t  x\t\t  g(x)\n";

    do {
        x_next = g(x);  

        cout << iteration << "\t\t" << x << "\t" << x_next << endl;

        if (fabs(x_next - x) < tolerance) 
            break;

        x = x_next;
        iteration++;

    } while (iteration <= maxIterations);

    cout << "\nApproximate Root from Fixed-Point Iteration: " << x << endl;
}


int main() {
    double a, b;
    bisection(a, b);

    double x0;
    newtonRaphson(x0);

    double xn;
    FixedPoint(xn);
    
    return 0;
}
