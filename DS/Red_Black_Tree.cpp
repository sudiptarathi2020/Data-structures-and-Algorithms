#include<bits/stdc++.h>
using namespace std;
template<typename T,typename compare>class RBTREE{
    private:
        compare comp;
        struct rbnode{
            bool color;
            T data;
            rbnode *parent;
            rbnode *left;
            rbnode *right;
        } ;
        rbnode *root,*TNULL;
        void inorder(rbnode *r){
            if(r!=TNULL){
                inorder(r->left);
                cout<<r->data<<" ";
                inorder(r->right);
            }
        }
        void rightRotate(rbnode *x){
            rbnode *y=x->left;
            x->left=y->right;
            if(y->right!=TNULL){
                y->right->parent=x;
            }
            y->parent=x->parent;
            if(x->parent==nullptr){
                this->root=y;
            }else if(x==x->parent->right){
                x->parent->right=y;
            }else{
                x->parent->left=y;
            }
            y->right=x;
            x->parent=y;
        }
        void leftRotate(rbnode *x){
            rbnode *y=x->right;
            x->right=y->left;
            if(y->left!=TNULL){
                y->left->parent=x;
            }
            y->parent=x->parent;
            if(x->parent==nullptr){
                this->root=y;
            }else if(x==x->parent->left){
                x->parent->left=y;
            }else{
                x->parent->right=y;
            }
            y->left=x;
            x->parent=y;
        }
        void insertFix(rbnode *current){
            rbnode *uncle;
            while(current->parent->color==1 && current->parent!=nullptr){
                if(current->parent==current->parent->parent->right){
                    uncle=current->parent->parent->left;
                    if(uncle->color==1){
                        uncle->color=0;
                        current->parent->color=0;
                        current->parent->parent->color=1;
                        current=current->parent->parent;
                    }else{
                        if(current==current->parent->left){
                            current=current->parent;
                            rightRotate(current);
                        }
                        current->parent->color=0;
                        current->parent->parent->color=1;
                        leftRotate(current->parent->parent);
                    }
                }else{
                    uncle=current->parent->parent->right;
                    if(uncle->color==1){
                        uncle->color=0;
                        current->parent->color=0;
                        current->parent->parent->color=1;
                        current=current->parent->parent;
                    }else{
                        if(current==current->parent->right){
                            current=current->parent;
                            leftRotate(current);
                        }
                        current->parent->color=0;
                        current->parent->parent->color=1;
                        rightRotate(current->parent->parent);
                    }
                }
                if(current==root){
                    break;
                }
            }
            root->color=0;
        }
    public:
        RBTREE(){
            TNULL= new rbnode;
            TNULL->color=0;
            TNULL->left=nullptr;
            TNULL->right=nullptr;
            TNULL->parent=nullptr;
            root=TNULL;
        }
        void deleteNode(rbnode* node) {
            if (node == TNULL) {
                return;
            }
            deleteNode(node->left);
            deleteNode(node->right);
            delete node;
        }

        ~RBTREE() {
            deleteNode(root);
            delete TNULL;
        }
        void insert(T key){
            rbnode *node=new rbnode;
            node->parent=nullptr;
            node->data=key;
            node->left=TNULL;
            node->right=TNULL;
            node->color=1;
            rbnode *y=nullptr;
            rbnode *x=this->root;
            while(x!=TNULL){
                y=x;
                if(comp(node->data,x->data)){
                    x=x->left;
                }else{
                    x=x->right;
                }
            }
            node->parent=y;
            if(y==nullptr){
                root=node;
            }else if(comp(node->data,y->data)){
                y->left=node;
            }else{
                y->right=node;
            }
            if(node->parent==nullptr){
                node->color=0;
                return;
            }
            if(node->parent->parent==nullptr){
                return;
            }
            insertFix(node);
        }
        void show(){
            inorder(this->root);
        }
};
int main(){
    //the input is 10,9,8,7,6,5,4,3,2,1,0
    RBTREE<int,greater<int>>st;//greater<int> for decreasing order,less<int> for increasing order
    for(int i=10;i>=0;i--){
        st.insert(i);
    }
    //the output should in increasing order
    //0 1 2 3 4 5 6 7 8 9 10
    st.show();
}
