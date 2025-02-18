#include <algorithm>
#include<bits/stdc++.h>
#include <cmath>
#include <utility>
using namespace std;
template<typename T>class kd{
    private:
        T Size;
        struct node{
            array<T,2>P;
            node *L,*R;
            node(){
                P[0]=-1;
                P[1]=-1;
                L=NULL;
                R=NULL;
            }
            node(int x,int y){
                P[0]=x;
                P[1]=y;
            }
        };node* root;
        node* newnode(array<T,2>point){
            node* temp=new node;
            temp->P[0]=point[0];
            temp->P[1]=point[1];
            temp->L=temp->R=nullptr;
            return temp;
        }
        node* insrt(node *root,array<T,2>point,int depth){
            if(root==NULL){
                return newnode({point[0],point[1]});
                Size++;
            }
            int cd=depth%2;
            if(point[cd]<root->P[cd]){
                root->L=insrt(root->L,point,depth+1);
            }else{
                root->R=insrt(root->R,point,depth+1);
            }
            return root;
        }
        node* closest(array<T,2>a,node* b,node* c){
            if(b==NULL and c==NULL){
                return NULL;
            }
            if(b==NULL and c!=NULL){
                return c;
            }
            if(c==NULL and b!=NULL){
                return b;
            }
            if(dist(a,b)<=dist(a,c)){
                return b;
            }else{
                return c;
            }
        }
        node* NN(node *root,array<T,2>point,int depth){
            if(root==NULL)return NULL; 
            int cd=depth%2;
            node *nextB;
            node *otherB; 
            node* temp;
            node* best;
            if(point[cd]<root->P[cd]){
                nextB=root->L;
                otherB=root->R;
            }else{
                nextB=root->R;
                otherB=root->L;
            }
            double D=(double)(1<<20);
            temp=NN(nextB,point,depth+1);
            best=closest(point,temp,root);
            D=dist(point,best);
            double R=(double)abs(point[cd]-root->P[cd]);
            if(D>=R){
                temp=NN(otherB,point,depth+1);
                best=closest(point,temp,best);
            }
            return best;
        }
        bool Search(node* root,array<T,2>A,int depth){
            if(root==nullptr)return false;
            if(root->P[0]==A[0] and  root->P[1]==A[1]){
                return true;
            }
            int cd=depth%2;
            if(A[cd]<root->P[cd]){
                return Search(root->L,A,depth+1);
            }
            return Search(root->R,A,depth+1);
        }
        double dist(array<T,2>a,node* B){
            if(B==NULL){
                return (double)(1<<20);
            }
            int c=(a[0]-B->P[0]);
            int d=(a[1]-B->P[1]);
            return sqrt(c*c+d*d);
        }



    public:
        kd(){
            Size=0;
            root=NULL;
        }
        void insert(int _x,int _y){
            root=insrt(root,{_x,_y},0);
        }
        pair<int,int> nearest(int _x,int _y){
            node* ans=NN(root,{_x,_y},0);
            return make_pair(ans->P[0],ans->P[1]);
        }
        double ndist(int _x,int _y){
            node* ans=NN(root,{_x,_y},0);
            return dist({_x,_y},ans);
        }
        bool search(T a,T b){
            return Search(root,{a,b},0);
        }
        T sz(){
            return Size;
        }
};
int main(){
    int a,b,k;
    cin>>k;
    kd<long long> tree;
    for(int i=0;i<k;i++){
        cin>>a>>b;
        tree.insert(a,b);//insert a point 
    }
    int x,y;cin>>x>>y;
    long long S=tree.sz();//size of the tree
    bool T=tree.search(x,y);//search for point if it exist in the tree {x,y},return bool;
    auto it=tree.nearest(x,y);//return the closest point from {x,y} as a pair<ll,ll>
    auto dist=tree.ndist(x,y);//return the closest distrance from {x,y}, return double
}
