#include<iostream>
using namespace std;

int i,x,y;
int mf,nf;
void vote(int n,int m) {
    if(x+1>=y && n-1>=0 && x+1<=nf) {
        x++;
        vote(n-1,m);
        x--;
    }
    
    if(x>=y+1 && m-1>=0 && y+1<=mf) {
        y++;
        vote(n,m-1);
        y--;
    }
    if(m+n==0) i++;
    return;
}

int main()
{
    i=0;
    x=0;
    y=0;
    int n,m;
    cin>>n>>m;
    nf=n;
    mf=m;
    vote(n,m);
    cout<<i;
    return 0;
}