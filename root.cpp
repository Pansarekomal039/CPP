#include <iostream>
#include <cmath>
#include <iomanip>
#include "root.hpp"

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







#include "root.hpp"
using namespace std;

cmplx::cmplx()
{
    real=0;
    img=0;
}

void cmplx::display()
{
    if(img>=0)
    {
cout << real << "+" << img <<"i"<<std::endl;
    }
    else
    {
cout << real << "-" << -img <<"i"<<std::endl;
    }
}


cmplx cmplx::add (cmplx y)
{
    cmplx c;
    c.real = this->real + y.real;
    c.img = this->img + y.img;
    return c;
}

cmplx cmplx::sub (cmplx y)
{
    cmplx c;
    c.real = this->real - y.real;
    c.img = this->img - y.img;
    return c;
}

cmplx cmplx::mul (cmplx y)
{
    cmplx c;
    c.real = (this->real * y.real)-(this->img * y.img);
    c.img = (this->real * y.img)+(this->img * y.real);
    return c;
}







