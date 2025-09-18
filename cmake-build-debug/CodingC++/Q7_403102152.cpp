#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string m;
    vector<string> list;

    while(1){
        cout<<"Enter operation:"<<endl;
        cout<<"1: Add product"<<endl;
        cout<<"2: Display all products"<<endl;
        cout<<"3: Exit"<<endl;
        cin>>n;
        if(n==3){
            cout<<"Program exited."<<endl;
            break;
        }
        else if(n==2){
            bool f=true;
            int i=1;
            if(list.size()>0) f=false;
            if(f) cout<<"No products in the list."<<endl;
            else{
                cout<<"All products:"<<endl;
                sort(list.begin(),list.end());
                for(int j=0;j<list.size();j++){
                    cout<<i++<<". "<<list[j]<<endl;
                }
            }
        }
        else{
            cout<<"Enter product name:"<<endl;
            cin.ignore();
            getline(cin,m);
            list.push_back(m);
            cout<<"Product added successfully!"<<endl;
        }
    }

    return 0;
}
    