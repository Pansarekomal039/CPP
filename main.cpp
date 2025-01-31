#include "cmplx.hpp"
using namespace std;
int main()
{
    cmplx p, q, ans_add, ans_sub;

    p.real=10.00;
    p.img=12.00;
    q.real=20.00;
    q.img=13.00;

    cout<< "p=";
    p.display();

    cout<<"q=";
    q.display();

    ans_add = p.add(q);
    cout << "Addition result: ";
    ans_add.display();

    ans_sub = p.sub(q);
    cout << "Subtraction result: ";
    ans_sub.display();

}