#include<iostream>
#include<math.h>
using namespace std;

int main()
{
    long x0,n,a,b,c,d,sum=0;
    cin>>n>>x0;
    for(int i=0;i<=n;i++){
        cin>>a;
        sum+=a*pow(x0,i);
    }
    cout<<sum;
    return 0;
}