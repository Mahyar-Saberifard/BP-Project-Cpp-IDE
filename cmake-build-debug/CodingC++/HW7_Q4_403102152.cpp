#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m,count=0;
    cin>>n>>m;
    vector<int> map(n*m);
    
    for(int i=0;i<n*m;i++){
        cin>>map[i];
    }
    
    for(int i=0;i<n*m;i++){
        for(int j=i+1;j<n*m;j++){
            if(map[i]==map[j]) count+=j/m-i/m+abs(j%m-i%m);
        }
    }
    cout<<count;
    return 0;
}