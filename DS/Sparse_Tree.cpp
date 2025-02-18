/*
 * Code by:Sudipta Singha
 * 
 * Problem: minimum range query using sparse table
 * 
 * 
 *    
 * */


#include<bits/stdc++.h>
using namespace std;
const int mx=1e6+100;
const int k=19;
int arr[mx];
int brr[mx][k];
int get_back(int a,int b)
{
	a--;
	b--;
	int len=b-a+1;
	if(a==b)
	{
		return arr[a];
	}
	int kk=0;
	while(1<<(kk+1)<=len)
	{
		kk++;
	}
	return min(brr[a][kk],brr[b-(1<<kk)+1][kk]);
}
void solve(int count)
{
	int n,q;
	cin>>n>>q;
	for(int i=0;i<n;i++)
	{
		cin>>arr[i];
		brr[i][0]=arr[i];
	}
	for(int i=1;i<k;i++)
	{
		for(int j=0;j+(1<<i)-1<n;j++)
		{
			brr[j][i]=min(brr[j][i-1],brr[j+(1<<(i-1))][i-1]);
		}
	}
	vector<int>v;
	while(q--)
	{
		int a,b;
		cin>>a>>b;
		v.push_back(get_back(a,b));
	}
	cout<<"Case "<<count<<": ";
	for(int i=0;i<(int)v.size();i++)
	{
		cout<<v[i]<<" ";
	}
	
	cout<<"\n";
	return ;
	cout<<"HALUM HALUM\n";
	return ;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int test;
	cin>>test;
	for(int i=1;i<=test;i++)
	{
		solve(i);
	}
	return 0;
}
