#include<iostream>
using namespace std;

int main()
{
    int l1,r1,l2,r2,l3,r3,l4,r4,a=0;
    bool l12=false,l13=false,l14=false,l23=false,l24=false,l34=false;
    cin>>l1>>r1>>l2>>r2>>l3>>r3>>l4>>r4;
    
    if(l1>=l2&&r1<=r2){
        a++;
        if(l1==l2&&r1==r2) l12=true;
    }
    else if(l1>=l3&&r1<=r3){
        a++;
        if(l1==l3&&r1==r3) l13=true;
    }
    else if(l1>=l4&&r1<=r4){
        a++;
        if(l1==l4&&r1==r4) l14=true;
    }
    
    if(l2>=l1&&r2<=r1&&l12==false) a++;
    else if(l2>=l3&&r2<=r3){
        a++;
        if(l2==l3&&r2==r3) l23=true;
    }
    else if(l2>=l4&&r2<=r4){
        a++;
        if(l2==l4&&r2==r4) l24=true;
    }
    
    if(l3>=l1&&r3<=r1&&l13==false) a++;
    else if(l3>=l2&&r3<=r2&&l23==false) a++;
    else if(l3>=l4&&r3<=r4){
        a++;
        if(l3==l4&&r3==r4) l34=true;
    }
    
    if(l4>=l1&&r4<=r1&&l14==false) a++;
    else if(l4>=l2&&r4<=r2&&l24==false) a++;
    else if(l4>=l3&&r4<=r3&&l34==false) a++;
    
    cout<<a;
    return 0;
}