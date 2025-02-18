#include<bits/stdc++.h>
using namespace std;
template<typename T,typename Comp>struct heap{//maxheap greater<T>,minheap less<T>
    Comp comp;
    vector<T>hp;
    heap(){hp.push_back(T());}
    void push(T value){
        hp.push_back(value);
        up((int)hp.size()-1);
    }
    void up(int idx){
        while(idx>1 && comp(hp[idx],hp[idx>>1])){
            swap(hp[idx],hp[idx>>1]);
            idx>>=1;
        }
    }
    void pop(){
        swap(hp[1],hp.back());
        hp.pop_back();
        down();
    }
    void down(){
        int idx=1;
        while((idx<<1)<(int)hp.size()){
            int child=idx<<1;
            if(child+1<(int)hp.size() and comp(hp[child+1],hp[child])){
                child+=1;
            }
            if(comp(hp[child],hp[idx])){
                swap(hp[child],hp[idx]);
                idx=child;
            }else{
                return;
            }
        }
    }
    T peek(){return hp[1];}
    int sz(){
        return (int)hp.size()-1;
    }
    bool empty(){
        return sz()==0;
    }
};
int main(){
    heap<int,greater<int>>H;
    for(int i=1;i<15;i+=2){
        H.push(i);
    }
    while(H.sz()){
        cout<<H.peek()<<endl;
        H.pop();
    }
}

