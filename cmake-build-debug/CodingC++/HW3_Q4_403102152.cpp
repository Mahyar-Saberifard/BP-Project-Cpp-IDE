#include <iostream>
#include <math.h>
using namespace std;
long power(long b,long c){
    long sum=0,pow=1;
    for(int i=1;i<=b;i++){
        sum+=pow;
        pow*=c;
    }
    return sum;
}
int main() {
    long n,a,b=2,c;
    cin>>n;
    a=log2(n);
    l1:
    c=pow(n,1.0/(b-1));
    if(power(b,c)==n){
        cout<<c;
        return 0;
    }
    if(b<=a){
        b++;
        goto l1;
    }
    cout<<n-1;
    return 0;
}