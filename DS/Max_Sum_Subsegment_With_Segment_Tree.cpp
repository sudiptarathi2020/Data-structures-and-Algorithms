#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define pf push_front
#define mkp make_pair
#define endl '\n'
#define ub upper_bound
#define lb lower_bound
#define IN cin
#define out cout
#define elif else if
#define yes cout<<"yes\n";
#define YES cout<<"YES\n";
#define NO cout<<"NO\n";
#define no cout<<"no\n";
#define fst first
#define scnd second
#define all(s) (s).begin(),(s.end())
#define sz(x) (ll)(x).size();
#define FOR(i,a,b) for(ll i=a;i<(b);i++)
#define F0R(i,a) for(ll i=0;i<(a);i++)
#define FORd(i,a,b) for(ll i=a;i>=b;i--)
#define F0Rd(i,a) for(ll i=a;i>=0;i--)
using namespace std;
const ll inf=LLONG_MAX;
const ll ninf=LLONG_MIN;
const ll N=2e5;
const ll mod=1e9+7;
typedef pair<ll,ll> pl;
typedef set<ll> st;
typedef queue<ll> ql;
typedef queue<pl> qpl;
typedef stack<ll> stk;
typedef stack<pl> stkp;
typedef priority_queue<ll> pq;
typedef priority_queue<ll,vector<ll>,greater<ll>> rpq;
typedef priority_queue<pl> pql;
typedef priority_queue<pl,vector<pl>,greater<pl>> rpql;
typedef set<pl> stp;
typedef vector<ll> vl;
typedef set<ll,greater<ll>> rst;
typedef set<pl,greater<pl>> rstp;
typedef vector<pl> vpl;
typedef vector<string> vs;
struct seg{
    struct data{
        int sum,pref,suff,ans;
        data(){
            sum=pref=suff=ans=0;
        }
    };
    int n;
    vector<data>t;
    seg(){}
    seg(int _n){
        this->n=_n;
        t.resize(4*_n);
    }
    data combine(data l,data r){
        data res;
        res.sum = l.sum + r.sum;
        res.pref = max(l.pref, l.sum + r.pref);
        res.suff = max(r.suff, r.sum + l.suff);
        res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
        return res;
    }
    data make_data(int val){
        data res;
        res.sum = val;
        res.pref = res.suff = res.ans = max(0,val);
        return res;
    }
    void build(){
        build(1,0,n-1);
    }
    void build(int v, int tl, int tr) {
        if (tl == tr) {
             t[v] = make_data(-1);
             return;
         }
        int tm = (tl + tr) / 2;
        build(v*2, tl, tm);
        build( v*2+1, tm+1, tr);
        t[v] = combine(t[v*2], t[v*2+1]);
    }
    void upd(int node,int start,int end,int pos,int val){
        if(start==end){
            t[node]=make_data(val);
        }else{
            int mid=(start+end)>>1;
            if(pos<=mid){
                upd(node<<1,start,mid,pos,val);
            }else{
                upd(node+node+1,mid+1,end,pos,val);
            }
            t[node]=combine(t[node<<1],t[node+node+1]);
        }
    }
    void upd(int pos,int val){
        upd(1,0,n-1,pos,val);
    }
    data q(int node,int tl,int tr,int l,int r){
        if(l>r){
            return make_data(0);
        }
        if(l==tl and r==tr){
            return t[node];
        }
        int mid=(tl+tr)>>1;
        return combine(q(node<<1,tl,mid,l,min(r,tr)),q(2*node+1,mid+1,tr,max(l,mid+1),r));
    }
    int q(int left,int right){
        data s= q(1,0,n-1,left,right);
        return s.ans;
    }
};
void sol(ll test){
    int n;cin>>n;
    int a[n];
    seg S(n);
    S.build();
    map<int,vector<int>>mp;
    for(int i=0;i<n;i++){
        cin>>a[i];
        mp[a[i]].pb(i);
    }
    int mx=-1;
    int ans=-1;
    for(auto it=mp.begin();it!=mp.end();it++){
        int val=it->first;
        vector<int>v=it->second;
        for(int x:v){
            S.upd(x,1);
        }
        int cur=S.q(0,n-1);
        if(cur>mx){
            mx=cur;
            ans=val;
        }
        for(int x:v){
            S.upd(x,-1);
        }
    }
    for(int i=0;i<n;i++){
        if(a[i]==ans){
            a[i]=1;
        }else{
            a[i]=-1;
        }
    }
    mx=0;
    int sum=0;
    int L=0,R=0;
    int last=0;
    for(int i=0;i<n;i++){
        sum+=a[i]; 
        if(sum>mx){
            mx=sum;
            L=i;
            R=last;
        }else if(sum<=0){
            last=i+1;;
            sum=0;
        }
    }
    cout<<ans<<" "<<R+1<<" "<<L+1<<endl;
    return;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    ll t=1;cin>>t;
    for(ll i=1;i<=t;i++){
        sol(i);
    }
}


