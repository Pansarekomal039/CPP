#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
double f(double x);
double f(double x){
    double a= 4*x*3-4*x;
    return a;
}
int main()
{
    cout.precision(5);
    cout.setf(ios::fixed);
    double a,b,c,e,fa,fb,fc;
    a:cout<<"Enter the initial guesses:\na=";
    cin>>a;
    cout<<"\nb=";
    cin>>b;
    cout<<"\nEnter the degree of accuracy desired"<<endl;
    cin>>e;
    int iter=0;
    if(f(a)*f(b)>0)
    {
        cout<<"Please enter a different initial guess"<<endl;
        goto a;
    }
    else
    {
     cout<<"Iter"<<setw(14)<<"a"<<setw(18)<<"b" <<setw(18)<<"c"<<setw(18)<<"f(c)"<<setw(18)<<"|a-b|<<endl";
     cout<<"------------------------------------------------------------------------";
     while(fabs(a-b)>=e)
     {
        c=(a+b)/2.0;
        fa=f(a);
        fb=f(b);
        fc=f(c);
        iter++;
       cout<<iter<<setw(18)<<a<<setw(18)<<b<<setw(18)<<c<<setw(18)<<f(c)<<setw(18)<<fabs(a-b)<<endl;
       if(fc==0)
       {
        cout<<"The root of equation is "<<c<<endl;;
        return 0;

       }
       if(fa*fc>0)
       {
        a=c;
       }
       else if(fa*fc<0)
       {
        b=c;
       }
     }
    }
    cout<<"The root of the equation is "<<c<<endl;;
    return 0;
}