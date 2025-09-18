#include<iostream>
#include<math.h>
using namespace std;

int main()
{
    long k,a=0,maxm=0,maxn=0;
    cin>>k;
    double list[k],javab[k];
    
    for(int i=0;i<k;i++){
        cin>>list[i];
        for(int j=1;j<=list[i];j++){
            if(long(list[i]/j)==list[i]/j) a++;
        }
        javab[i]=a;
        a=0;
    }
    for(int i=0;i<k;i++){
        cout<<javab[i]<<endl;
        if(maxm<javab[i]){
            maxm=javab[i];
        }
    }
    for(int i=0;i<k;i++){
        if(javab[i]==maxm && list[i]>maxn) maxn=list[i];
    }
    cout<<"max : ("<<maxn<<","<<maxm<<")";
    return 0;
}