#include<iostream>
#include<iomanip>
using namespace std;

struct menu{
    string name;
    float rate=0.0;
    float price;
    int quantity;
    int quantitytemp;
    int ratecount=1;
    float ratetotal=0.0;
};

struct ids{
    string name;
    float balance;
    float balancetemp;
    int order[300]={0};
    bool start=true;
    int number=0;
    int sequence[300]={0};
};

bool CharCompare(char a, char b)
{
    return tolower(a)==tolower(b);
}

int main()
{
    string adname,adpass;
    cin>>adname>>adpass;
    int n,m,k,order=1;
    cin>>n>>m>>k;
    menu foods[n];
    ids id[m];
    for(int i=0;i<n;i++){
        cin>>foods[i].name>>foods[i].price>>foods[i].quantity;
        foods[i].quantitytemp=foods[i].quantity;
    }
    for(int i=0;i<m;i++){
        cin>>id[i].name>>id[i].balance;
        id[i].balancetemp=id[i].balance;
    }
    
    string input[k][3],others;
    int count[k];
    float rate[k];
    for(int i=0;i<k;i++){
        cin>>input[i][0]>>input[i][1];
        if((input[i][0]!="view" && input[i][1]!="menu") || input[i][0]!="search:"){
            if(input[i][1]=="adds"){
                for(int j=0;j<2;j++) cin>>others;
                cin>>input[i][2]>>count[i];
            }
            else if(input[i][1]=="starts") for(int j=0;j<2;j++) cin>>others;
            else if(input[i][1]=="wants") for(int j=0;j<4;j++) cin>>others;
            else if(input[i][1]=="finalizes") for(int j=0;j<2;j++) cin>>others;
            else if(input[i][1]=="rates") cin>>input[i][2]>>rate[i];
        }
    }
    
    for(int i=0;i<k;i++){
        if(input[i][0]=="view" && input[i][1]=="menu"){
            bool e=true;
            for(int j=0;j<n;j++){
                if(foods[j].quantity>0){
                    cout<<foods[j].name<<", $"<<setprecision(1)<<fixed<<foods[j].price<<", "<<setprecision(1)<<fixed<<foods[j].rate<<"/5"<<endl;
                    e=false;
                }
                else if(j==n-1&&e) cout<<"No items are available"<<endl;
            }
        }
        else if(input[i][0]=="search:"){
            bool d=true;
            for(int j=0;j<n;j++){
                bool founded=false;
                for(int h=0;h<foods[j].name.length();h++){
                    int hhh=0;
                    for(int hh=0;hh<input[i][1].length();hh++){
                        bool found=false;
                        if(CharCompare(foods[j].name[h+hh],input[i][1][hh]) && h+hh<=foods[j].name.length()) found=true;
                        if(found) hhh++;
                    }
                    if(hhh==input[i][1].length()){
                        founded=true;
                        break;
                    }
                }
                if(founded && foods[j].quantity>0){
                    cout<<foods[j].name<<", $"<<setprecision(1)<<fixed<<foods[j].price<<", "<<setprecision(1)<<fixed<<foods[j].rate<<"/5"<<endl;
                    d=false;
                }
                else if(j==n-1&&d){
                    cout<<"No items found with '"<<input[i][1]<<"'"<<endl;
                }
            }
        }
        else{
            
            if(input[i][1]=="starts"){
                bool c=true;
                for(int j=0;j<m;j++){
                    if(id[j].name==input[i][0]){
                        if(id[j].number==0){
                            id[j].number=order;
                            cout<<"Order "<<order++<<" started"<<endl;
                        }
                        else cout<<"You already have an active order. Please complete it before starting a new one."<<endl;
                        c=false;
                    }
                    else if(j==m-1&&c) cout<<"Username does not exist."<<endl;
                }
            }
            
            else if(input[i][1]=="adds"){
                bool z=true;
                for(int j=0;j<m;j++){
                    if(id[j].name==input[i][0]){
                        bool b=true;
                        for(int h=0;h<n;h++){
                            if(foods[h].name==input[i][2]){
                                if(count[i]<1) cout<<"Quantity must be at least 1."<<endl;
                                else if(id[j].number==0) cout<<"You don't have an active order. Please start a new one."<<endl;
                                else{
                                    cout<<"Added "<<count[i]<<" of "<<input[i][2]<<" to your order."<<endl;
                                    id[j].order[h]+=count[i];
                                    id[j].start=false;
                                    if(id[j].sequence[h]==0) id[j].sequence[h]=i+1;
                                }
                                b=false;
                            }
                            else if(h==n-1&&b) cout<<input[i][2]<<" is not available in the menu."<<endl;
                        }
                        z=false;
                    }
                    else if(j==m-1&&z) cout<<"Username does not exist."<<endl;
                }
            }
            
            else if(input[i][1]=="wants"){
                bool x=true;
                for(int j=0;j<m;j++){
                    if(id[j].name==input[i][0]){
                        if(id[j].number==0) cout<<"You don't have an active order."<<endl;
                        else{
                            bool l=true,ll=true;
                            int u=0,v=0;
                            for(int h=0;h<n;h++){
                                if(id[j].order[h]>0) u++;
                            }
                            while(u>0){
                                for(int h=0;h<n;h++){
                                    if(id[j].order[h]>0 && id[j].sequence[h]==v){
                                        if(ll){
                                            cout<<"Order Number: "<<id[j].number<<endl;
                                            ll=false;
                                        }
                                        cout<<"- "<<foods[h].name<<", "<<id[j].order[h]<<endl;
                                        l=false;
                                        u--;
                                    }
                                }
                                v++;
                            }
                            if(l) cout<<"Your order is empty."<<endl;
                        }
                        x=false;
                    }
                    else if(j==m-1&&x) cout<<"Username does not exist."<<endl;
                }
            }
            
            else if(input[i][1]=="finalizes"){
                bool y=true;
                for(int j=0;j<m;j++){
                    if(id[j].name==input[i][0]){
                        if(id[j].number==0) cout<<"You don't have an active order to finalize."<<endl;
                        else{
                            if(id[j].start) cout<<"Your order is empty. Add items to the order before finalizing."<<endl;
                            else{
                                bool p=true;
                                for(int h=0;h<n;h++){
                                    if(id[j].order[h]>0){
                                        if(id[j].order[h]>foods[h].quantity){
                                            cout<<"Not enough stock available."<<endl;
                                            p=true;
                                            break;
                                        }
                                        else{
                                            if(id[j].balance<foods[h].price){
                                                cout<<"You don't have enough balance."<<endl;
                                                p=true;
                                                break;
                                            }
                                            else{
                                                foods[h].quantity-=id[j].order[h];
                                                id[j].balance-=foods[h].price * id[j].order[h];
                                                p=false;
                                            }
                                        }
                                    }
                                }
                                if(!p){
                                    cout<<"Ordered successfully! Your remaining balance is $"<<setprecision(1)<<fixed<<id[j].balance<<"."<<endl;
                                    for(int h=0;h<n;h++){
                                        if(id[j].order[h]>0) foods[h].quantitytemp=foods[h].quantity;
                                        id[j].order[h]=0;
                                        id[j].sequence[h]=0;
                                    }
                                    id[j].number=0;
                                    id[j].start=true;
                                    id[j].balancetemp=id[j].balance;
                                    
                                }
                                else{
                                    for(int h=0;h<n;h++){
                                        if(id[j].order[h]>0) foods[h].quantity=foods[h].quantitytemp;
                                        id[j].order[h]=0;
                                        id[j].sequence[h]=0;
                                    }
                                    id[j].number=0;
                                    id[j].start=true;
                                    id[j].balance=id[j].balancetemp;
                                }
                            }
                        }
                        y=false;
                    }
                    else if(j==m-1&&y) cout<<"Username does not exist."<<endl;
                }
            }
            
            else if(input[i][1]=="rates"){
                bool w=true;
                for(int j=0;j<m;j++){
                    if(id[j].name==input[i][0]){
                        bool pp=true;
                        for(int h=0;h<n;h++){
                            if(foods[h].name==input[i][2]){
                                if(rate[i]==0||rate[i]==1||rate[i]==2||rate[i]==3||rate[i]==4||rate[i]==5){
                                    foods[h].ratetotal+=rate[i];
                                    foods[h].rate=(foods[h].ratetotal)/(foods[h].ratecount++);
                                    cout<<"Your rating has been recorded."<<endl;
                                }
                                else cout<<"Ratings must be an integer between 0 and 5."<<endl;
                                pp=false;
                            }
                            else if(h==n-1&&pp) cout<<input[i][2]<<" is not available in the menu."<<endl;
                        }
                        w=false;
                    }
                    else if(j==m-1&&w) cout<<"Username does not exist."<<endl;
                }
            }
        }
    }
    
    return 0;
}