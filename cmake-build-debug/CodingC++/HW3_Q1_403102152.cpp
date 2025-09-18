#include<iostream>
using namespace std;

int ragham(long adad){
    int r=0;
    while (adad>0){
        adad/=10;
        r++;
    }
    return r;
}

int main()
{
    long n,m,min,minr,max,maxr,rev,a=0;
    cin>>n>>m;
    
    if(n>m){
        min=m;
        max=n;
        minr=ragham(m);
        maxr=ragham(n);
    }
    else{
        min=n;
        max=m;
        minr=ragham(n);
        maxr=ragham(m);
    }
    
    rev=min;
    
    for(int i=0; i<(maxr-minr); i++){
        min=min*10+rev%10;
        rev/=10;
        if(rev==0) rev=min;
    }
    
    cout<<min+max;
    return 0;
}