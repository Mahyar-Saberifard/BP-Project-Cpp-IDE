#include<iostream>
using namespace std;

int main()
{
    int n,x,t;
    cin>>n>>x;
    t=x;
    
    for(int i=0; i<n; i++) {
        for(int j=0; j<=2*x; j++) {
            if(j==0) {
                for(int i=0; i<x; i++) {
                    cout<<" ";
                }
                cout<<"/|"<<endl;
            }
            else if(j==x-1) {
                cout<<" / /";
                for(int i=0; i<x-1; i++) {
                    cout<<"_";
                }
                cout<<endl;
            }
            else if(j==x) {
                cout<<"|";
                for(int i=0; i<x-1; i++) {
                    cout<<"_";
                }
                cout<<"  |"<<endl;
                t=x;
            }
            else if(j==2*x) cout<<" |/"<<endl;
            else {
                for(int k=0; k<t; k++) {
                    cout<<" ";
                }
                cout<<"/ /"<<endl;
            }
            t--;
        }
        t=x;
    }
    return 0;
}