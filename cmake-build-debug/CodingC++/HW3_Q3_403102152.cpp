#include<iostream>
using namespace std;

int main()
{
    int house,n,k,a=-10000,b=-10000,c=0;
    cin>>n>>k;
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++){
            cin>>house;
            if(house==1){
                if((i-a)+(j-b)<k){
                    c=1;
                }
                a=i;
                b=j;
            }
        }
    }
    if(c==1) cout<<"Yes";
    else cout<<"No";
    return 0;
}