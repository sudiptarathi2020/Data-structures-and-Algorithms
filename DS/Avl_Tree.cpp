#include<bits/stdc++.h>
using namespace std;
using node=struct Node*;
struct Node{
    int key,height,sz;
    node left,right;
    Node(int _key){
        key=_key;
        sz=1;
        height=0;
        left=right=NULL;
    }
    Node(){
        left=right=NULL;
    }
};
class AVLTREE{
    private:
        node root=NULL;
        void updateHeight(node R){
            R->height=1+max(height(R->left),height(R->right));
        }
        void updateSz(node R){
            R->sz=1+sz(R->left)+sz(R->right);
        }
        int sz(node R){
            return R==NULL?0:R->sz;
        }
        int height(node R){
            return R==NULL?-1:R->height;
        }
        int getBalance(node R){
            return (R==NULL)?0:height(R->right)-height(R->left);
        }
        node rotateRight(node R){
            node x=R->left;
            node y=x->right;
            x->right=R;
            R->left=y;
            updateHeight(R);
            updateSz(R);
            updateHeight(x);
            updateSz(x);
            return x;
        }
        node rotateLeft(node R){
            node x=R->right;
            node y=x->left;
            x->left=R;
            R->right=y;
            updateHeight(R);
            updateSz(R);
            updateHeight(x);
            updateSz(x);
            return x;
        }
        node reBalance(node z){
            updateHeight(z);
            updateSz(z);
            int balance=getBalance(z);
            if(balance>1){
                if(height(z->right->right)>height(z->right->left)){
                    z=rotateLeft(z);
                }else{
                    z->right=rotateRight(z->right);
                    z=rotateLeft(z);
                }
            }else if(balance<-1){
                if(height(z->left->left)>height(z->left->right)){
                    z=rotateRight(z);
                }else{
                    z->left=rotateLeft(z->left);
                    z=rotateRight(z);
                }
            }
            return z;
        }
        node insert(node root,int key){
            if(root==NULL){
                return new Node(key);
            }else if(root->key>key){
                root->left=insert(root->left,key);
            }else if(root->key<key){
                root->right=insert(root->right,key);
            }
            return reBalance(root);
        }
        void inorder(node root){
            if(root->left!=NULL){
                cout<<root->key<<" "<<root->left->key<<endl;
                inorder(root->left);
            }
            if(root->right!=NULL){
                cout<<root->key<<" "<<root->right->key<<endl;
                inorder(root->right);
            }
        }
        node Mostleftchild(node root){
            while(root->left!=NULL){
                root=root->left;
            }
            return root;
        }
        int idx(node root, int Idx) {
            if (root == NULL || sz(root) <= Idx) return INT_MAX;
            else if (sz(root->left) == Idx) {
                return root->key;
            } else if (sz(root->left) > Idx) {
                return idx(root->left, Idx);
            } else {
                return idx(root->right, Idx - sz(root->left) - 1);
            }
        }

        node remove(node root,int key){
            if(root==NULL){
                return root;
            }else if(key<root->key){
                root->left=remove(root->left,key);
            }else if(key>root->key){
                root->right=remove(root->right,key);
            }else{
                if(root->left==NULL || root->right==NULL){
                    root=(root->left==NULL)?root->right:root->left;
                }else{
                    node LMC=Mostleftchild(root->right);
                    root->key=LMC->key;
                    root->right=remove(root->right,root->key);
                }
            }
            if(root!=NULL){
                root=reBalance(root);
            }
            return root;
        }
    public:
        void insert(int key){
            root=insert(root,key);
        }
        void inorder(){
            inorder(root);
        }
        void remove(int key){
            root=remove(root,key);
        }
        int Sz(){
            return sz(root);
        }
        int idx(int Idx){
            return idx(root,Idx);
        }
};
int main(){
    AVLTREE tree;
    for(int i=10;i>=0;i--){
        tree.insert(i);
    }
    for(int i=0;i<11;i++){
        cout<<tree.idx(i)<<endl;
    }
}
