#include<bits/stdc++.h>
using namespace std;
#define ll long long
template <typename T>struct point{
    T x;
    T y;
    point(){}
    point(T _x,T _y){
        this->x=_x;
        this->y=_y;
    }
    bool operator==(const point<ll>& A){
        return make_pair(this->x,this->y)==make_pair(A.x,A.y);
    }
    bool operator<(const point<ll>& A){
        return make_pair(this->y,this->x)<make_pair(A.y,A.x);
    }
    bool operator>(const point<ll>& A){
        return make_pair(this->x,this->x)>make_pair(A.y,A.x);
    }
};
typedef point<ll> Point;
/*  Utilities
template<typename T>Point operator+(const point<T>& A,const point<T>& B){return (Point){A.x+B.x,A.y+B.y};}
template<typename T>bool operator==(const point<T>& A,const point<T>& B){return make_pair(A.x,A.y)==make_pair(B.x,B.y);}
template<typename T>bool operator<(const point<T>& A,const point<T>& B){return make_pair(A.x,A.y)<make_pair(B.x,B.y);}
template<typename T>bool operator>(const point<T>&A,const point<T>& B){return make_pair(A.x,A.y)>make_pair(B.x,B.y);}
*/
int orientation(Point A,Point B,Point C){
    int o=A.x*(B.y-C.y)+B.x*(C.y-A.y)+C.x*(A.y-B.y);
    if(o<0)return -1;
    if(o>0)return 1;
    return 1&2;
}
bool cw(Point a,Point b,Point c,bool nonlinear=false){
    int o=orientation(a,b,c);
    return o<0 or (nonlinear and o==0);
}
bool colinear(Point a,Point b,Point c){
    return orientation(a,b,c)==0;
}
vector<Point> convex_hull(vector<Point>&a,bool nonlinear=false){
    Point P=*min_element(a.begin(),a.end());
    auto B=[&P](Point A,Point B){
        int o=orientation(P,A,B);
        if(o==0){
            return (P.x-A.x)*(P.x-A.x)+(P.y-A.y)*(P.y-A.y)<(P.x-B.x)*(P.x-B.x)+(P.y-B.y)*(P.y-B.y);
        };
        return o<0;
    };
    sort(a.begin(),a.end(),B);
    vector<Point>St;
    for(int i=0;i<(int)a.size();i++){
        while(St.size()>1 && !cw(St[St.size()-2],St.back(),a[i])){
            St.pop_back();
        }
        St.push_back(a[i]);
    }
    vector<Point>K;
    K=St;
    return K;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int N;cin>>N;
    vector<Point>A(N);
    for(int i=0;i<N;i++){
        cin>>A[i].x>>A[i].y;
    }
    auto K=convex_hull(A);
    cout<<"The Point's of the convex hull are: \n";
    for(auto I:K){
        cout<<I.x<<","<<I.y<<endl;
    }
}
