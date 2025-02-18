/*
Prepared by Sudpta Singha
E-mail: jucse29.408@gmail.com
topic:lazy propagatable dynamic segment tree
*/
struct seg{
    int start,end,sum=0,lazy=0;
    seg *start_child=nullptr,*end_child=nullptr;
    seg(int Left,int Right){
        start=Left,end=Right;
    }
    void extend(){
        if(!start_child and start!=end){
            int mid=(start+end)>>1;
            start_child=new seg(start,mid);
            end_child=new seg(mid+1,end);
        }
    }
    void propagate(){
        sum+=(end-start+1)*lazy;
        if(start!=end){
            start_child->lazy+=lazy;
            end_child->lazy+=lazy;
        }
        lazy=0;
    }
    void upd(int Left,int Right,int val){
        extend();
        propagate();
        if(Left==start and Right==end){
            sum+=(end-start+1)*val;
            if(start!=end){
                start_child->lazy+=val;
                end_child->lazy+=val;
            }
            return;
        }
        int mid=(start+end)>>1;
        if(Right<=mid){
            start_child->upd(Left,Right,val);
        }else if(mid<Left){
            end_child->upd(Left,Right,val);
        }else{
            start_child->upd(Left,mid,val);
            end_child->upd(mid+1,Right,val);
        }
        sum=start_child->sum+end_child->sum;
    }
    int get(int Left,int Right){
        extend();
        propagate();
        if(start==Left and end==Right){
            return sum;
        }
        int mid=(start+end)>>1;
        if(Right<=mid){
            return start_child->get(Left,Right);
        }else if(mid<Left){
            return end_child->get(Left,Right);
        }else{
            return start_child->get(Left,mid)+end_child->get(mid+1,Right);
        }
    }
};
