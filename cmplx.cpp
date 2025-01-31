#include "cmplx.hpp"
using namespace std;

cmplx::cmplx()
{
    real=0;
    img=0;
//   cout<< "Default Constructor";
}

void cmplx::display()
{
cout << real << "+" << img <<"i"<<std::endl;
cout << real << "-" << img <<"i"<<std::endl;
cout << real << "*" << img <<"i"<<std::endl;
cout << real << "/" << img <<"i"<<std::endl;
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
    c.real = this->real * y.real;
    c.img = this->img * y.img;
    return c;
}

cmplx cmplx::div (cmplx y)
{
    cmplx c;
    c.real = this->real / y.real;
    c.img = this->img / y.img;
    return c;
}