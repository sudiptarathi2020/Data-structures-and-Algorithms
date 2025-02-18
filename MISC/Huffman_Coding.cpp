#include <bits/stdc++.h>
using namespace std;
struct node {
    int S;
    char val;
    node *left, *right;
    node(int _S,char _val){
        S=_S;val=_val;
        left=right=NULL;
    }
    node(int _S,char _val,node* _left,node* _right){
        S=_S,val=_val;left=_left,right=_right;
    }
};
class compare{
    public:
        bool operator()(node* a,node* b){
            return a->S>b->S;
        }
};
void dfs(node* root,string S,unordered_map<char,string>&mp){
    if(root==NULL)return;
    if(root->val!='#'){
        mp[root->val]=S;
        cout<<root->val<<" "<<S<<endl;
    }else if(root->val=='#'){
        if(root->left!=NULL){
            dfs(root->left,S+'0',mp);
        }
        if(root->right!=NULL){
            dfs(root->right,S+'1',mp);
        }
    }
}
int main() {
    string s;
    cout<<"what is the typed message: ";
    cin >> s;
    unordered_map<char,int>freq;
    for (char x : s) {
        freq[x]++;
    }
    priority_queue<node*,vector<node*>,compare>pq;
    for(pair<char,int> x:freq){
        pq.push(new node(x.second,x.first));
    }
    while(pq.size()>1){
        node* X=pq.top();pq.pop();
        node* Y=pq.top();pq.pop();
        node* Z=new node(X->S+Y->S,'#',X,Y);
        pq.push(Z);
    }
    unordered_map<char,string>mp;
    dfs(pq.top(),"",mp);
    string sendmsg="";
    for(char x:s){
        sendmsg+=mp[x];
    }
    cout<<"The sent message is "<<sendmsg<<endl;
    node *root=pq.top();
    node* temp=root;
    string gotmsg="";
    for(char x:sendmsg){
        if(x=='0'){
            temp=temp->left;
        }else if(x=='1'){
            temp=temp->right;
        }
        if(temp->val!='#'){
            gotmsg+=temp->val;
            temp=root;
        }
    }
    cout<<"The received message is "<<gotmsg<<endl;
}
