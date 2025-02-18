#include<bits/stdc++.h>
using namespace std;
using pt =struct node*;
struct node{
    int priority,val,sz;
    int sum;bool lazy=0;
    pt child[2];
    node(int _val){
        priority=rand();
        val=sum=_val;sz=1;
        child[0]=child[1]=NULL;
    }
    ~node(){
        for(int i:{0,1}){
            delete(child[i]);
        }
    }
};
int getsz(pt x){
    return x?x->sz:0;
}
int getsum(pt x){
    return x?x->sum:0;
}
pt propagate(pt x){
    if(!x or !x->lazy)return x;
    swap(x->child[0],x->child[1]);
    x->lazy=0;
    for(int i:{0,1}){
        if(x->child[i]){
            x->child[i]->lazy^=1;
        }
    }
    return x;
}
pt calculate(pt x){
    pt a=x->child[0],b=x->child[1];
    assert(!x->lazy);
    propagate(a),propagate(b);
    x->sz=1+getsz(a)+getsz(b);
    x->sum=x->val+getsum(a)+getsum(b);
    return x;
}
void traverse(pt x,vector<int>&tour){
    if(!x)return;
    traverse(x->child[0],tour);
    tour.push_back(x->val);
    traverse(x->child[1],tour);
}
pair<pt,pt> split(pt t,int v){
    if(!t)return {t,t};
    propagate(t);
    if(t->val>=v){
        pair<pt,pt>p=split(t->child[0],v);
        t->child[0]=p.second;
        return {p.first,calculate(t)};
    }else{
        pair<pt,pt>p=split(t->child[1],v);
        t->child[1]=p.first;
        return {calculate(t),p.second};
    }
}
pair<pt,pt> splitsz(pt t,int sz){
    if(!t)return {t,t};
    propagate(t);
    if(getsz(t->child[0])>=sz){
        pair<pt,pt>p=splitsz(t->child[0],sz);
        t->child[0]=p.second;
        return {p.first,calculate(t)};
    }else{
        pair<pt,pt>p=splitsz(t->child[1],sz-getsz(t->child[0])-1);
        t->child[1]=p.first;
        return {calculate(t),p.second};
    }
}
pt merge(pt L,pt R){
    if(!L)return R;
    if(!R)return L;
    propagate(L),propagate(R);
    pt T;
    if(L->priority>R->priority){
        L->child[1]=merge(L->child[1],R);
        T=L;
    }else{
        R->child[0]=merge(L,R->child[0]);
        T=R;
    }
    return calculate(T);
}
pt insert(pt x,int v){
    pair<pt,pt>a=split(x,v);
    pair<pt,pt>b=split(a.second,v+1);
    return merge(a.first,merge(new node(v),b.second));
}
pt remove(pt x,int v){
    pair<pt,pt>a=split(x,v);
    pair<pt,pt>b=split(a.second,v+1);
    return merge(a.first,b.second);
}
int main(){
    pt root=new node(10);
    for(int i=10;i>=1;i--){
        root=insert(root,i);
    }
    pair<pt,pt>P=splitsz(root,5);
    cout<<getsz(P.first)<<"\n";
    cout<<getsum(P.first)<<"\n";
    cout<<getsz(P.second)<<"\n";
    cout<<getsum(P.second)<<"\n";
}
