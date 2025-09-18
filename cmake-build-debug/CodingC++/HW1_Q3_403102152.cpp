#include<iostream>
using namespace std;

int main()
{
    int a;
    double b,c;
    cin>>a;
    b=a/10*1.3;
    c=int(a/60*7.9)+a%60/10*1.3;
    if(c<b)
        cout<<c;
    else
        cout<<b;
    return 0;
}