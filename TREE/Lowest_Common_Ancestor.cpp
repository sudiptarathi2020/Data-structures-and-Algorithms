#include<bits/stdc++.h>
using namespace std;
struct LCA{
    int n,l;
    vector<vector<int>>adj;
    int timer;
    vector<int>tin,tout;
    vector<vector<int>>up;
    LCA(){}
    LCA(int _n){
        this->n=_n;
        this->timer=0;
        l=ceil(log2(n));
        adj.resize(n+1);
        tin.resize(n+1);
        tout.resize(n+1);
        up.assign(n,vector<int>(l+1));
    }
    void add(int a,int b){
        adj[a].push_back(b);
    }
    void dfs(int v,int p){
        tin[v]=++timer;
        up[v][0]=p;
        for(int i=1;i<=l;++i){
            up[v][i]=up[up[v][i-1]][i-1];
        }
        for(int u:adj[v]){
            if(u!=p){
                dfs(u,v);
            }
        }
        tout[v]=++timer;
    }
    bool is_an(int u,int v){
        return tin[u]<=tin[v] and tout[u]>=tout[v];
    }
    int lca(int u,int v){
        if(is_an(u,v)){
            return u;
        }
        if(is_an(v,u)){
            return v;
        }
        for(int i=l;i>=0;i--){
            if(!is_an(up[u][i],v)){
                u=up[u][i];
            }
        }
        return up[u][0];
    }
    void pre(int root){
        dfs(root,root);
    }
};
int main(){

}
