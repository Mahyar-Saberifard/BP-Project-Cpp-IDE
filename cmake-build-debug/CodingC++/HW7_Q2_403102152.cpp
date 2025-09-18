#include<bits/stdc++.h>
using namespace std;

int main() {
    long n,m,k,u1,u2,v;
    cin>>n>>m>>k;
    vector<long> inputs(k);
    vector<vector<long>> graph(n);

    for(long i=0;i<m;i++){
        cin>>u1>>u2;
        graph[u1-1].push_back(u2);
        graph[u2-1].push_back(u1);
    }

    for(long i=0;i<k;i++){
        cin>>v;
        inputs[i]=v;
    }

    for(long i=0;i<k;i++){
        vector<long>& mojavers=graph[inputs[i]-1];
        sort(mojavers.begin(),mojavers.end());
        cout<<mojavers.size()<<" ";
        for(long mojaver : mojavers){
            cout<<mojaver<<" ";
        }
        cout<<endl;
    }

    return 0;
}
