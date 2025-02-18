#include <algorithm>
#include<bits/stdc++.h>
#include <cstddef>
#include <cstdio>
#define ll long long
using namespace std;
template<typename T>struct SET{
    T Size=0;
    struct node{
        T data;
        T prior;
        node *left,*right;
        node(T N){
            this->data=N;
            this->prior=rand();
            this->left=this->right=NULL;
        }
    };node* Root=NULL;
    typedef node * Node;
    void rotateleft(Node &root){
        Node A=root->right;
        Node B=root->right->left;
        A->left=root;
        root->right=B;
        root=A;
    }
    void rotateright(Node &root){
        Node A=root->left;
        Node B=root->left->right;
        A->right=root;
        root->left=B;
        root=A;
    }
    void insert(Node &root,T data){
        if(root==NULL){
            root=new node(data);
            Size++;
            return;
        }
        if(data<root->data){
            insert(root->left,data);
            if(root->left!=NULL and root->left->prior>root->prior){
                rotateright(root);
            }
        }else if(data==root->data){
            return;
        }else{
            insert(root->right,data);
            if(root->right!=NULL and root->right->prior>root->prior){
                rotateleft(root);
            }
        }
    }
    bool search(Node &root,T data){
        if(root==NULL)return false;
        if(root->data==data)return true;
        if(data<root->data){
            return search(root->left,data);
        }else{
            return search(root->right,data);
        }
    }
    void Delete(Node &root,T data){
        if(root==NULL)return;
        if(data<root->data){
            Delete(root->left,data);
        }else if(data>root->data){
            Delete(root->right,data);
        }else{
            if(root->left==NULL and root->right==NULL){
                delete(root);
                Size--;
                root=nullptr;
            }else if(root->left !=NULL and root->right!=NULL){
                if(root->left->prior<root->right->prior){
                    rotateleft(root);
                    Delete(root->left,data);
                }else{
                    rotateright(root);
                    Delete(root->right,data);
                }
            }else{
                Node A=(root->left!=NULL)?root->left:root->right;
                Node B=root;
                root=A;
                delete(B);
                Size--;
            }
        }
    }
    void Delete(T data){
        Delete(Root,data);
    }
    void inorder(Node root){
        if(root==NULL)return;
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
    void sorted(){
        inorder(Root);
        cout<<"\n";
    }
    void rsorted(){
        outorder(Root);
        cout<<"\n";
    }
    void outorder(Node root){
        if(root==nullptr)return;
        outorder(root->right);
        cout<<root->data<<" ";
        outorder(root->left);
    }
    void insert(T data){
        insert(Root,data);
    }
    T size(){
        return Size;
    }
};
int main(){
    SET<int>S;
    S.insert(10);
    S.insert(20);
    S.insert(1);
    S.insert(20);
    S.insert(100);
    S.insert(200);
    S.insert(-1);
    S.sorted();
    S.rsorted();
    S.Delete(20);
    S.sorted();
    S.rsorted();
}
