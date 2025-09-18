#include<iostream>
#include<math.h>
using namespace std;

int main()
{
    double x1,y1,x2,y2,x3,y3,a,b,c;
    cin>>x1>>y1>>x2>>y2>>x3>>y3;
    a=pow(x1-x2,2)+pow(y1-y2,2);
    b=pow(x2-x3,2)+pow(y2-y3,2);
    c=pow(x1-x3,2)+pow(y1-y3,2);
    if((y1-y2)/(x1-x2)==(y2-y3)/(x2-x3)||a==0||b==0||c==0) cout<<"No triangles are formed";
    else{
        if(c>a&&c>b){
            if(c==a+b) cout<<"A right triangle is formed";
            else if(c>a+b) cout<<"An obtuse triangle is formed";
            else cout<<"An acute triangle is formed";
        }
        else if(b>a){
            if(b==a+c) cout<<"A right triangle is formed";
            else if(b>a+c) cout<<"An obtuse triangle is formed";
            else cout<<"An acute triangle is formed";
        }
        else{
            if(a==c+b) cout<<"A right triangle is formed";
            else if(a>c+b) cout<<"An obtuse triangle is formed";
            else cout<<"An acute triangle is formed";
        }
    }
    return 0;
}