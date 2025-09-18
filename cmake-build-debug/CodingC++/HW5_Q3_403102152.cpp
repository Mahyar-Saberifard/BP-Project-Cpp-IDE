#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

int main(){
    double x,y,l,r,u,d,a,b,map[51][51],mapp[51][51];
    cin>>x>>y>>l>>r>>u>>d>>a>>b;
    double mx=a/x*50,my=50-b/y*50,t=pow(y/x,2);
    long javabx=mx,javaby=my,pp,p;

    for(int i=0;i<51;i++){
        for(int j=0;j<51;j++){
            if(i==0) map[i][j]=u;
            else if(i==50) map[i][j]=d;
            else if(j==0) map[i][j]=l;
            else if(j==50) map[i][j]=r;
            else map[i][j]=0;
            map[0][0]=(l+u)/2;
            map[0][50]=(r+u)/2;
            map[50][0]=(l+d)/2;
            map[50][50]=(r+d)/2;
            mapp[i][j]=map[i][j];
        }
    }
l1:
    int c=0;
    for(int k=1,h=1;k<50||h<50;k++,h++){
        for(int i=1;i<50;i++){
            for(int j=1;j<50;j++){
                mapp[i][j]=(map[i-1][j]+map[i+1][j]+t*(map[i][j-1]+map[i][j+1]))/(2+2*t);
            }
        }
        for(int i=0;i<51;i++){
            for(int j=0;j<51;j++){
                if(mapp[i][j]-long(mapp[i][j])>0.5) pp=long(mapp[i][j])+1;
                else pp=long(mapp[i][j]);
                if(map[i][j]-long(map[i][j])>0.5) p=long(map[i][j])+1;
                else p=long(map[i][j]);
                if(pp-p==1) c++;
                map[i][j]=mapp[i][j];
            }
        }
    }
    if(c>0) goto l1;

    cout<<setprecision(0)<<fixed<<map[javaby][javabx];
    return 0;
}