/* 
Author : Nguyen Xuan An 
Gmail : xuanan437@gmail.com
*/   
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
#define for0(i ,l ,r) for(int i = (l); i < (r); ++i)
#define for1(i, l, r) for(int i = (l); i >= (r); --i)
#define for2(v) for(auto it : v)
#define reset(a) memset(a,0,sizeof(a))
#define mem(a) memset(a,-1,sizeof(a))
#define membo(a) memset(a,false,sizeof(a))

#define vi vector<int>
#define vpi vector<pair<int, int>>
#define pii pair<int,int>
#define fi first
#define se second
#define prq priority_queue
#define pb push_back

#define output ios::sync_with_stdio(0);cin.tie(0);
#define fastio 	ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define PI 3.1415926535897932385
#define INF 10000000

#define BIT(n) (1<<(n))
#define AND(a,b) ((a) & (b))
#define OR(a,b) ((a) | (b))
#define XOR(a,b) ((a) ^ (b))


int n;
const int MX = 600000;
ll tree[MX], lazy[MX], a[MX];
void build_set1(int pos,int ss, int se)
{
   if(ss == se)
   {
       tree[pos] = a[ss];
       return;
   }
   int mid = (ss + se) / 2;
   build_set1(2*pos,ss,mid);
   build_set1(2*pos+1,mid+1,se);
   tree[pos] = tree[pos*2]+tree[pos*2+1];
}
void build_set()
{
    build_set1(1,0,n-1);
}
void updaterange(ll pos, ll ss, ll se, ll us, ll ue, ll diff)
{
    if(ss > se || ss > ue || se < us) return;
    if(ss == se)
    {
        tree[pos] = diff;
        return ;

    }
    int mid = (ss + se) / 2;
    updaterange(2*pos,ss,mid,us,ue,diff);
    updaterange(2*pos+1,mid+1,se,us,ue,diff);
    tree[pos] = tree[pos*2] + tree[pos*2 + 1];
}
void update(int a, int b, int d)
{
    updaterange(1,0,n-1,a,b,d);
}
ll sumrange(ll pos, ll ss, ll se, ll us, ll ue)
{
    if(ss > se || ss > ue || se < us) return 0;
    if(ss >= us and se <= ue) return tree[pos];
    int mid  = (se + ss) / 2;
    return sumrange(2*pos,ss,mid,us,ue)+sumrange(2*pos + 1,mid+1,se,us,ue);
}
ll sum(ll a, ll b)
{
    return sumrange(1,0,n-1,a,b);
}
int main()
{
    ll m;
    cin >> n >> m;
    for0(i,0,n)
    {
        cin >> a[i];
    }
    build_set();
    for0(i,0,m)
    {
        ll x, y ,z;
        cin >> x >> y >> z;
        if(x == 1) update(y-1,y-1,z);
        if(x == 2) cout << sum(y-1,z-1) << endl;
    }

}