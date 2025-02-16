#include "cmplx.hpp"
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







