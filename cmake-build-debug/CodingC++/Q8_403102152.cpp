#include<iostream>
#include<iomanip>
using namespace std;

long double trib(int n){
    if(n==0||n==1){
        return 1;
    }
    if(n==2){
        return 2;
    }
    return trib(n-1)+trib(n-2)+trib(n-3);
}

int main()
{
    long double n,fact=1;
    cin>>n;
    for(int i=0;i<n;i++){
        fact*=trib(i);
    }
    cout<<fixed<<setprecision(0)<<fact;
    return 0;
}