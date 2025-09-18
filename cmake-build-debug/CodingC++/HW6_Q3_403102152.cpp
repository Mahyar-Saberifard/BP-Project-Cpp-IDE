#include<iostream>
#include<iomanip>
using namespace std;

struct movies{
    string title;
    int year;
    float rate;
    float price;
};

struct ids{
    string name;
    string pass;
    float balance;
};

int main()
{
    int n,m,k;
    cin>>n>>m>>k;
    movies movie[n];
    ids id[m];
    for(int i=0;i<n;i++) cin>>movie[i].title>>movie[i].year>>movie[i].rate>>movie[i].price;
    for(int i=0;i<m;i++) cin>>id[i].name>>id[i].pass>>id[i].balance;
    
    string input[k][3],others;
    for(int i=0;i<k;i++){
        cin>>input[i][0]>>input[i][1];
        if(input[i][0]!="show" && input[i][1]!="movies"){
            for(int j=0;j<6;j++) cin>>others;
            cin>>input[i][2];
        }
    }
    
    for(int i=0;i<k;i++){
        if(input[i][0]=="show" && input[i][1]=="movies"){
            cout<<"All available movies:"<<endl;
            for(int j=0;j<n;j++) cout<<movie[j].title<<" - "<<movie[j].year<<" - "<<setprecision(1)<<fixed<<movie[j].rate<<"/10 - $"<<setprecision(1)<<fixed<<movie[j].price<<endl;
        }
        else{
            bool c=true;
            for(int j=0;j<m;j++){
                if(id[j].name==input[i][0]){
                    if(id[j].pass==input[i][1]){
                        bool b=true;
                        for(int h=0;h<n;h++){
                            if(movie[h].title==input[i][2]){
                                if(id[j].balance>=movie[h].price){
                                    id[j].balance-=movie[h].price;
                                    cout<<"Purchase successful! Your remaining balance is $"<<setprecision(1)<<fixed<<id[j].balance<<endl;
                                }
                                else cout<<"Insufficient balance"<<endl;
                                b=false;
                            }
                            else if(h==n-1&&b) cout<<"The movie "<<input[i][2]<<" does not exist"<<endl;
                        }
                    }
                    else cout<<"Invalid password"<<endl;
                    c=false;
                }
                else if(j==m-1&&c) cout<<"Invalid username"<<endl;
            }
        }
    }
    
    return 0;
}