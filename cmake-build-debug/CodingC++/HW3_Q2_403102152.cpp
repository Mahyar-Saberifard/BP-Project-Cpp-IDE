#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
    int a=0,b=0;
    float ans,x,res;
    char line;
    cin>>line;
    while(a==0){
        if(line=='='){
            b++;
            line=getchar();
        }
        if(b==0){
            if(line=='x'){
                x++;
                line=getchar();
            }
            else if(line=='-'){
                line=getchar();
                if(line!='x' && line!='='){
                    res+=float(line)-48;
                    line=getchar();
                }
                else if(line='x'){
                    x--;
                    line=getchar();
                }
            }
            else if(line=='+'){
                line=getchar();
                if(line!='x' && line!='='){
                    res-=float(line)-48;
                    line=getchar();
                }
            }
            else{
                res-=float(line)-48;
                line=getchar();
            }
        }
        else{
            if(line=='x'){
                x--;
                line=getchar();
            }
            else if(line=='-'){
                line=getchar();
                if(line!='x' && line!='='){
                    res-=float(line)-48;
                    line=getchar();
                }
                else if(line='x'){
                    x++;
                    line=getchar();
                }
            }
            else if(line=='+'){
                line=getchar();
                if(line!='x' && line!='='){
                    res+=float(line)-48;
                    line=getchar();
                }
            }
            else{
                res+=float(line)-48;
                line=getchar();
            }
        }
        if(line=='!') a++;
    }
    
    ans=res/x;
    
    if(x==0){
        if(res==0) cout<<"Infinite solutions";
        else cout<<"No solution";
    }
    else cout<<fixed<<showpoint<<setprecision(3)<<ans;
    return 0;
}