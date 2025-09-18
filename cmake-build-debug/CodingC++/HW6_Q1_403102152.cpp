#include<iostream>
#include<string.h>
using namespace std;

int main()
{
    int n,r=-1;
    cin>>n;
    int list[n];
    string name;
    for(int i=0;i<n;i++){
        cin>>name;
        int a=0;
        char volt[]="volt",team[]="team",volteam[]="volteam";
        while ((r=name.find(volt,r+1))!=string::npos) a++;
        while ((r=name.find(team,r+1))!=string::npos) a++;
        while ((r=name.find(volteam,r+1))!=string::npos) a--;
        list[i]=a;
    }
    for(int i=0;i<n;i++) cout<<list[i]<<endl;
    return 0;
}