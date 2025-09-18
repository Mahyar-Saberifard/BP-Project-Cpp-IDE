#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    long n,k;
    bool yes=true;
    cin>>n>>k;
    double list[n],pow[n-k+1],t,max,min;
    
    for(int i=0;i<n;i++){
        list[i]=1;
    }
    for(int i=0;i<n-k+1;i++){
        pow[i]=0;
    }
    
    for(int i=0;i<3;i++){
        for(int j=0;j<n;j++){
            cin>>t;
            list[j]*=t;
        }
    }
    
    for(int i=0;i<n-k+1;i++){
        for(int j=0;j<k;j++) pow[i]+=list[i+j];
        if(yes){
            max=pow[0];
            min=pow[0];
            yes=false;
        }
        if(pow[i]>max) max=pow[i];
        if(pow[i]<min) min=pow[i];
        cout<<"Total Power in interval "<<i+1<<" = "<<setprecision(3)<<fixed<<pow[i]<<endl;
    }
    cout<<"Maximum Power in "<<k<<" seconds = "<<max<<endl;
    cout<<"Minimum Power in "<<k<<" seconds = "<<min<<endl;
    return 0;
}