#include<bits/stdc++.h>
using namespace std;
struct HLD{
    vector<vector<int>>adj;
    vector<int>tree;
    vector<int>head,pos,heavy,depth,parent,sz;
    vector<bool>vis;
    vector<int>euler,gene;
    int n;
    HLD(){}
    HLD(int _n){
        this->n=_n;
        adj.resize(n);
        head.resize(n+1);
        gene.resize(n+1);
        vis.resize(n+1);
        sz.resize(n+1);
        pos.resize(n+1);
        heavy.resize(n+1,-1);
        tree.assign(4*n,0);
        depth.resize(n+1);
        parent.resize(n+1);
    }
    void add(int a,int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void decom(int source,int h){
        head[source]=h;
        pos[source]=(int)euler.size();
        euler.push_back(gene[source]);
        if(heavy[source]!=-1){
            decom(heavy[source],h);
        }
        for(int c:adj[source]){
            if(c!=parent[source] and c!=heavy[source]){
                decom(c,c);
            }
        }
    }
    void build(int node,int st,int en){
        if(st==en){
            tree[node]=euler[st];
        }else{
            int mid=(st+en)>>1;
            build(node+node,st,mid);
            build(node+1+node,mid+1,en);
            tree[node]=tree[2*node]+tree[2*node+1];
        }
    }
    void upd(int node,int st,int en,int ind,int val){
        if(st==en){
            tree[node]=val;
        }else{
            int mid=(st+en)>>1;
            if(ind<=mid){
                upd(node+node,st,mid,ind,val);
            }else{
                upd(node+node+1,mid+1,en,ind,val);
            }
            tree[node]=tree[2*node]+tree[2*node+1];
        }
    }
    void upd(int v,int val){
        upd(1,0,n-1,pos[v],val);
    }
    void make_seg(){
        build(1,0,n-1);
    }
    int q(int node,int st,int en,int left,int right){
        if(st==left and right==en){
            return tree[node];
        }
        int mid=(st+en)>>1;
        if(right<=mid){
            return q(node+node,st,mid,left,right);
        }else if(left>mid){
            return q(node+node+1,mid+1,en,left,right);
        }else{
            int a=q(node+node,st,mid,left,mid);
            int b=q(node+node+1,mid+1,en,mid+1,right);
            return a+b;
        }
    }
    int q(int left,int right){
        return q(1,0,n-1,left,right);
    }
    int query(int u,int v){
        int a=pos[u],b=pos[v];
        if(a<b){
            return q(a,b);
        }else{
            return q(b,a);
        }
    }
    void dfs(int source,int par,int H){
        vis[source]=true;
        depth[source]=H;
        parent[source]=par;
        sz[source]+=1; 
        int Mx=-1,big=-1;
        for(int u:adj[source]){
            if(u!=par){
                dfs(u,source,H+1);
                sz[source]+=sz[u];
                if(sz[u]>Mx){
                    Mx=sz[u];
                    big=u;
                }
            }
        }
        heavy[source]=big;
    }
    int get_ans(int a,int b){
        int res=0;
        for(;head[a]!=head[b];b=parent[head[b]]){
            if(depth[head[a]]>depth[head[b]]){
                swap(a,b);
            }
            int cur=query(head[b],b);
            res+=cur;
        }
        if(depth[a]>depth[b]){
            swap(a,b);
        }
        int cur=query(a,b);
        return res+cur;
    }
};
int main(){

}
