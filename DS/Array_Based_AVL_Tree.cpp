#include<iostream>
#include<vector>
using namespace std;
struct node{
    int value;
    int leftChild,rightChild,H;
    node(int _value,int _l,int _r,int _H){
        value=_value;leftChild=_l,rightChild=_r;
        H=_H;
    }
};
vector<node>tree;
int height(int root){
    if(root==-1)return 0;
    return tree[root].H;
}
int getBalance(int root){
    if(root==-1)return 0;
    return height(tree[root].leftChild)-height(tree[root].rightChild);
}
void fix(int root,int ind){
    if(tree[root].value>tree[ind].value){
        if(tree[root].leftChild==-1){
            tree[root].leftChild=ind;
        }else{
            fix(tree[root].leftChild,ind);
        }
    }else if(tree[root].value<tree[ind].value){
        if(tree[root].rightChild==-1){
            tree[root].rightChild=ind;
        }else{
            fix(tree[root].rightChild,ind);
        }
    }else{
        tree.pop_back();
        return;
    }
    tree[root].H=1+max(height(tree[root].leftChild),height(tree[root].rightChild));
    int balance=getBalance(root);
}
void inorder(int root){
    if(root==-1)return;
    inorder(tree[root].leftChild);
    cout<<tree[root].value<<" ";
    inorder(tree[root].rightChild);
}
void insert(int value){
    tree.push_back(node(value,-1,-1,1));
    if(tree.size()==1)return;
    fix(0,(int)tree.size()-1);
}
int main(){
    insert(15);
    insert(13);
    insert(11);
    insert(10);
    insert(120);
    insert(20);
    insert(30);
    insert(3);
    insert(10);
    inorder(0);
}
