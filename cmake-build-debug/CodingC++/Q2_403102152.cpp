#include<iostream>
using namespace std;

int gateA(int input1, int input2, int input3){
    if(input1+input2+input3==2) return 1;
    else return 0;
}

int gateB(int input1, int input2){
    if(input1+input2==1) return 1;
    else return 0;
}

int main()
{
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    if(gateB(gateA(a,b,c),gateA(b,c,d))==1) cout<<"On";
    else{
        cout<<"Off"<<endl;
        if(gateB(gateA(not(bool(a)),b,c),gateA(b,c,d))==1) cout<<"a";
        else if(gateB(gateA(a,not(bool(b)),c),gateA(not(bool(b)),c,d))==1) cout<<"b";
        else if(gateB(gateA(a,b,not(bool(c))),gateA(b,not(bool(c)),d))==1) cout<<"c";
        else if(gateB(gateA(a,b,c),gateA(b,c,not(bool(d))))==1) cout<<"d";
        else cout<<"None";
    }
    return 0;
}