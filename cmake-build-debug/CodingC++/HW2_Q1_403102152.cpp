#include<iostream>
using namespace std;

int main()
{
    long m,a,b,c,d;
    cin>>m>>a>>b>>c;
    d=(m-c)/(b-c);
    if(b-c<a&&m>=b){
        if(m-d*(b-c)>=a) cout<<d+1;
        else cout<<d;
    }
    else cout<<m/a;
    return 0;
}