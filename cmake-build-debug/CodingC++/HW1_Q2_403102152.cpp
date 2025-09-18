#include<iostream>
using namespace std;

int main()
{
    long sh1,sh2,sh3,nes,arz1,arz2,arz3,m1,m2,m3,a,b,c;
    
    cin>>sh1>>nes>>arz1>>arz2>>arz3>>m1>>m2>>m3;
    sh2=sh1+1;
    sh3=sh2+1;
    a=arz1*arz1*nes*sh1*sh1*sh1;
    b=arz2*arz2*nes*sh2*sh2*sh2;
    c=arz3*arz3*nes*sh3*sh3*sh3;
    cout<<a+b+c<<endl;
    if(a>=m1)
      cout<<a-m1<<endl;
    else cout<<"Not enough food!"<<endl;  
    
    if(b>=m2)
      cout<<b-m2<<endl;
    else cout<<"Not enough food!"<<endl;
    
    if(c>=m3)
      cout<<c-m3<<endl;
    else cout<<"Not enough food!"<<endl;
    
    return 0;
}