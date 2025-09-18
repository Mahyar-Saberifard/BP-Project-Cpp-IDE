#include <iostream>
using namespace std;
int main(){
    int k;
    cin>>k;
    if(k==1){
        cout<<"true"<<endl;
    } else if(k==0){
        cout<<"false"<<endl;
    } else {
        cout<<"out of range"<<endl;
        cin>>k;
    }
    return 0;
}
