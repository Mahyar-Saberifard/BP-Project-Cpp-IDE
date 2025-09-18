#include<iostream>
using namespace std;

int main()
{
    int n,m,t,x,y,k,k1=0,k2=0;
    cin>>n>>m>>t;
    int map[m][n];

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            map[i][j]=0;
        }
    }
    for(int i=0; i<t; i++) {
        cin>>x>>y>>k;
        for(int j=x-2; j<x+1; j++) {
            if(j>=0&&j<n) {
                for(int h=y-2; h<y+1; h++) {
                    if(h>=0&&h<m) {
                        if(k==1) map[h][j]++;
                        else map[h][j]--;
                    }
                }
            }
        }
    }
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(map[i][j]>0) k1++;
            else if(map[i][j]<0) k2++;
        }
    }

    cout<<k1<<" "<<k2;
    return 0;
}