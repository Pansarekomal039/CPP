#include "cmplx.hpp"
using namespace std;
int main()
{
    cmplx p,q,ans;

    p.real=10.00;
    p.img=12.00;
    q.real=20.00;
    q.img=13.00;

    cout<< "p=";
    p.display();

    cout<<"q=";
    q.display();

    ans = p.add(q);
    ans = p.sub(q);
    ans = p.mul(q);

    cout<< "ans=";
    ans.display();

}