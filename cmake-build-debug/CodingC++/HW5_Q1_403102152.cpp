#include<iostream>
using namespace std;

int main()
{
    int n,m,javab=0;
    cin>>n>>m;
    int mat1[n][m],mat2[m][n],res[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i][j]=0;
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>mat1[i][j];
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>mat2[i][j];
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<m;k++){
                res[i][j]+=mat1[i][k]*mat2[k][j];
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) javab+=res[i][j];
            if(j==n-i-1) javab-=res[i][j];
        }
    }
    cout<<javab;
    return 0;
}