#include<iostream>
#include<map>
using namespace std;

int main()
{
    map<string, int> company;
    string input;
    while(1){
        cin>>input;
        if(input=="End") break;
        bool a=false;
        for(auto& n : company){
            if(n.first==input){
                n.second++;
                a=true;
            }
        }
        if(!a){
            company.insert({input, 1});
        }
    }
    
    int i=1,j=0;
    while(j<company.size()){
        for(auto n : company){
            if(n.first.length()==i){
                cout<<n.first<<":"<<n.second<<endl;
                j++;
            }
        }
        i++;
    }
    return 0;
}