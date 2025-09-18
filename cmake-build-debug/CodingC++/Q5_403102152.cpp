#include<iostream>
using namespace std;

int main()
{
    int n,diasum=0;
    cin>>n;
    int mat[n][n],rowsum[n];
    for(int i=0;i<n;i++){
        rowsum[i]=0;
        for(int j=0;j<n;j++){
            cin>>mat[i][j];
            if(i==j||i==n-j-1) diasum+=mat[i][j];
            rowsum[i]+=mat[i][j];
        }
    }
    
    cout<<"1.Sum of main and secondary diagonals: "<<diasum<<endl;
    cout<<"2.Rotated Matrix:"<<endl;
    for(int i=0;i<n;i++){
        for(int j=n-1;j>=0;j--){
            cout<<mat[j][i]<<" ";
        }
        cout<<endl;
    }
    cout<<"3.Binary Matrix:"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(mat[i][j]>0) cout<<1<<" ";
            else cout<<0<<" ";
        }
        cout<<endl;
    }
    cout<<"4.Row Sums:"<<endl;
    for(int i=0;i<n;i++) cout<<rowsum[i]<<endl;
    return 0;
}