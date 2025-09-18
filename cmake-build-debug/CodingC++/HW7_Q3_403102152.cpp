#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<string> v(0);
    vector<vector<string>> text(100,v);
    vector<vector<string>> dictionary(100,v);
    string input;
    
    int a=0;
    while(1){
        getline(cin,input);
        string words="";
        if(input=="Close Dictionary") break;
        for(int i=0;i<=input.length();i++){
            bool flag=false;
            while(input[i]==' '){
                input.erase(i,1);
                flag=true;
            }
            if((flag || i==input.length()) && words!=""){
                dictionary[a].push_back(words);
                words="";
            }
            words+=input[i];
        }
        a++;
    }
    
    int b=0;
    while(1){
        getline(cin,input);
        string words="";
        if(input=="End of The Text") break;
        for(int i=0;i<=input.length();i++){
            bool flag=false;
            while(input[i]==' '){
                input.erase(i,1);
                flag=true;
            }
            if((flag || i==input.length()) && words!=""){
                text[b].push_back(words);
                words="";
            }
            words+=input[i];
        }
        b++;
    }
    
    getline(cin,input);
    
    for(int i=0;i<a;i++){
        for(int j=0;j<text[i].size();j++){
            int max=0;
            for(int k=0;k<b;k++){
                for(int g=0;g<dictionary[k].size();g++){
                    int t=0;
                    if(text[i][j].length()==dictionary[k][g].length()){
                        for(int h=0;h<text[i][j].length();h++){
                            if(text[i][j][h]==dictionary[k][g][h]) t++;
                        }
                        if(t>max && t>text[i][j].length()/2) max=t;
                    }
                }
            }
            bool yes=false;
            for(int k=0;k<b;k++){
                for(int g=0;g<dictionary[k].size();g++){
                    int t=0;
                    if(text[i][j].length()==dictionary[k][g].length()){
                        for(int h=0;h<text[i][j].length();h++){
                            if(text[i][j][h]==dictionary[k][g][h]) t++;
                        }
                        if(t==max && max!=0){
                            text[i][j]=dictionary[k][g];
                            yes=true;
                            break;
                        }
                    }
                }
                if(yes) break;
            }
            cout<<text[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}