#include<bits/stdc++.h>
using namespace std;

struct person {
  string firstname = "";
  string lastname = "";
  int age = 0;
  int offences = 0 ;
};

char letters(char a){
    if(int(a)<88) a+=2;
    else a-=24;
    return a;
}

char numbers(char a, char b){
    int c=10*(int(a)-48)+(int(b)-48);
    return(char(c));
}

int ages(char a, char b){
    int c=10*(int(b)-48)+(int(a)-48);
    return(c);
}

int main()
{
    int n,max=0;
    cin>>n;
    string plate[n];
    person info[100];
    
    for(int i=0;i<n;i++){
        string first="",last="";
        cin>>plate[i];
        first+=letters(plate[i][0]);
        first+=letters(plate[i][1]);
        first+=numbers(plate[i][2],plate[i][3]);
        last+=letters(plate[i][4]);
        last+=letters(plate[i][5]);
        last+=numbers(plate[i][6],plate[i][7]);
        last+=numbers(plate[i][8],plate[i][9]);
        bool flag=true;
        for(int j=0;j<n;j++){
            if(info[j].firstname==first && info[j].lastname==last){
                info[j].offences++;
                flag=false;
            }
            else if(j==n-1&&flag){
                info[i].firstname=first;
                info[i].lastname=last;
                info[i].age=ages(plate[i][2],plate[i][3]);
                info[i].offences=1;
            }
            if(info[j].offences>max) max=info[j].offences;
        }
    }
    
    for(int j=0;j<n;j++){
        if(info[j].offences==max){
            cout<<"firstname : "<<info[j].firstname<<endl;
            cout<<"lastname : "<<info[j].lastname<<endl;
            cout<<"age : "<<info[j].age<<endl;
            cout<<"offences : "<<info[j].offences<<endl;
            break;
        }
    }
    
    return 0;
}