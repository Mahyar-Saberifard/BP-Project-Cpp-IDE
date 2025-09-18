#include<iostream>
using namespace std;

int main()
{
    int n,m,a=0;
    cin>>n;
    int ln[n];
    for(int i=0;i<n;i++) cin>>ln[i];
    cin>>m;
    int lm[m];
    for(int i=0;i<m;i++) cin>>lm[i];
    
    for(int i=0;i<m+1;i++){
        if(i>n-1){
            for(int j=0;j<n;j++){
                if(lm[i-j-1]==ln[n-j-1]) a++;
            }
        }
        if(a==n) cout<<1<<" ";
        else cout<<0<<" ";
        a=0;
    }
    return 0;
}