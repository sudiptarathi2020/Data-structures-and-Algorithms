#include<bits/stdc++.h>
#define ll long long
using pll=std::pair<ll,ll>;
using namespace std;
const ll Inf=1e9+1;
struct Point{
    ll x,y;
    Point(){}
    Point(ll _x,ll _y):x(_x),y(_y){}
    bool operator<(const Point &other){
        if(x==other.x){return y<other.y;}
        return x<other.x;
    }
    bool operator>(const Point &other){
        if(x==other.x){return y>other.y;}
        return x>other.x;
    }
    bool operator==(const Point &other){
        return x==other.x and y==other.y;
    }
};
const pair<Point,Point> inf= make_pair(Point(-Inf,-Inf),Point(Inf,Inf));

ll dist(const pair<Point,Point> &a){
    ll d1=a.first.x-a.second.x;
    ll d2=a.first.y-a.second.y;
    return d1*d1+d2*d2;
}
pair<Point,Point> get_closest_points(const pair<Point,Point>&a,const pair<Point,Point>&b){
    return dist(a)<=dist(b)?a:b;
}
pair<Point,Point> brute_forcer(vector<Point>&points){
    pair<Point,Point>ans=inf;
    for(int i=0;i<(int)points.size();i++){
        for(int j=i+1;j<(int)points.size() && j-i<9;j++){
            ans=get_closest_points(ans,make_pair(points[i],points[j]));
        }
    }
    return ans;
}
pair<Point,Point> solve(vector<Point>&points,int l,int r){
    if(l==r){return inf;}
    int mid=(l+r)>>1;
    pair<Point,Point> ans_left=solve(points,l,mid);
    pair<Point,Point> ans_right=solve(points,mid+1,r);
    pair<Point,Point> ans;
    ans=get_closest_points(ans_left,ans_right);
    ll D=dist(ans);
    Point mid_point=points[mid];
    vector<Point>temp;
    for(int i=l;i<r;i++){
        if((points[i].x-mid_point.x)*(points[i].x-mid_point.x)<=D){
            temp.push_back(points[i]);
        }
    }
    sort(temp.begin(),temp.end(),[](Point a,Point b){
            return a.y<b.y || (a.y==b.y && a.x< b.y);
            });
    return get_closest_points(ans,brute_forcer(temp));
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin>>n;
    vector<Point>arr(n);
    for(auto &X:arr){
        cin>>X.x>>X.y;
    }
    sort(arr.begin(),arr.end());
    pair<Point,Point> ans=solve(arr,0,(int)arr.size());
    cout<<dist(ans)<<endl;
    return 0;
}

