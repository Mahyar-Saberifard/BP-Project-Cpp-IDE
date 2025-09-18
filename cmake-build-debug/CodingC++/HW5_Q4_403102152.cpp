#include<iostream>
using namespace std;

int main()
{
    int k,m,n;
l1:
    cin>>k;
    if(k%2==0||k==1) {
        cout<<"kernel matrix must be odd-sized!"<<endl;
        goto l1;
    }
    
    int kernel[k][k],pad=(k-1)/2;
    for(int i=0;i<k;i++){
        for(int j=0;j<k;j++){
            cin>>kernel[i][j];
        }
    }
    
    cin>>m>>n;
    int map[m+2*pad][n+2*pad],javab[m][n];
    
    for(int i=0;i<m+2*pad;i++){
        for(int j=0;j<n+2*pad;j++){
            map[i][j]=0;
            javab[i][j]=0;
        }
    }
    
    for(int i=pad;i<m+pad;i++){
        for(int j=pad;j<n+pad;j++){
            cin>>map[i][j];
        }
    }
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            for(int h=0;h<k;h++){
                for(int g=0;g<k;g++){
                    javab[i][j]+=kernel[h][g]*map[h+i][g+j];
                }
            }
        }
    }
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout<<javab[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}