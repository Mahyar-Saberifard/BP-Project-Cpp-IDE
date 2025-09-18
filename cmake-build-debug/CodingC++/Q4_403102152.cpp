#include<iostream>
using namespace std;

int main()
{
    int m1,m2,l;
    cin>>m1>>m2>>l;
    
    for(int i=0;i<=(l-1)/2;i++){
        for(int j=0;j<=2*(m1*(l-1)/4)+2*(m2*(l-1)/4);j++){
            if(i<(l-1)/4){
                if(j==(m1*(l-1)/4)+(m2*(l-1)/4)+m1*i || j==(m1*(l-1)/4)+(m2*(l-1)/4)-m1*i) cout<<"*";
                else cout<<"-";
            }
            else{
                if(j==(m1*(l-1)/4)+(m2*(l-1)/4)+m1*(l-1)/4+m2*(i-(l-1)/4) || j==(m1*(l-1)/4)+(m2*(l-1)/4)-m1*(l-1)/4-m2*(i-(l-1)/4)) cout<<"*";
                else cout<<"-";
            }
        }
        cout<<endl;
    }
    
    for(int i=(l-1)/2-1;i>=0;i--){
        for(int j=0;j<=2*(m1*(l-1)/4)+2*(m2*(l-1)/4);j++){
            if(i<(l-1)/4){
                if(j==(m1*(l-1)/4)+(m2*(l-1)/4)+m1*i || j==(m1*(l-1)/4)+(m2*(l-1)/4)-m1*i) cout<<"*";
                else cout<<"-";
            }
            else{
                if(j==(m1*(l-1)/4)+(m2*(l-1)/4)+m1*(l-1)/4+m2*(i-(l-1)/4) || j==(m1*(l-1)/4)+(m2*(l-1)/4)-m1*(l-1)/4-m2*(i-(l-1)/4)) cout<<"*";
                else cout<<"-";
            }
        }
        cout<<endl;
    }
    
    return 0;
}