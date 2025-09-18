#include<bits/stdc++.h>
using namespace std;

int main()
{
    string input,temp;
    long ans[26]={0},min=10000;
    cin>>input;
    for(int i=97;i<=122;i++){
        temp=input;
        int a=0;
        for(int j=0;j<temp.length();j++){
            if(temp[j]!=temp[temp.length()-j-1]){
                if(temp[j]==char(i)){
                    temp.erase(temp.begin()+j);
                    a++;
                    j--;
                }
                else if(temp[temp.length()-j-1]==char(i)){
                    temp.erase(temp.end()-j-1);
                    a++;
                    j--;
                }
            }
            string pmet=temp;
            reverse(pmet.begin(),pmet.end());
            if(pmet==temp){
                ans[i-97]=a;
                break;
            }
        }
    }
    string putni=input;
    reverse(putni.begin(),putni.end());
    if(input==putni) cout<<0;
    else{
        for(int i=0;i<26;i++){
            if(min>ans[i] && ans[i]!=0) min=ans[i];
        }
        if(min!=10000) cout<<min;
        else cout<<-1;
    }
    return 0;
}