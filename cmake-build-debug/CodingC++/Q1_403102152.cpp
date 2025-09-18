#include<iostream>
using namespace std;

int main()
{
    int n,a1,a2,a3,a4,a5;
    float b;
    cin >> n;
    a1 = n/10000;
    a2 = n/1000 - 10*a1;
    a3 = n/100 - 100*a1 - 10*a2;
    a4 = n/10 - 1000*a1 - 100*a2 - 10*a3;
    a5 = n%10;
    b = float(a4-a2)/a5;
    cout << a1 <<"   "<< a2 <<"   "<< a3 <<"   "<< a4 <<"   "<< a5 <<endl<< a1+a2+a3+a4+a5 <<endl<< b;
    return 0;
}