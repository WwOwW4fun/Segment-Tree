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

ll n, m;
const int MX = 3000000;
ll tree[MX], lazy[MX], a[MX];
void build_set1(ll pos,ll ss, ll se)
{
   if(ss == se)
   {
       tree[pos] = a[ss];
       return;
   }
   int mid = (ss + se) / 2;
   build_set1(2*pos,ss,mid);
   build_set1(2*pos+1,mid+1,se);
   tree[pos] = max(tree[pos*2],tree[pos*2+1]);
}
void build_set()
{
    build_set1(1,1,m);
}
ll sumrange(ll pos, ll ss, ll se, ll us, ll ue)
{
    if(ss > se || ss > ue || se < us) return 0;
    if(ss >= us and se <= ue) return tree[pos];
    ll mid  = (se + ss) / 2;
    return max(sumrange(2*pos,ss,mid,us,ue),sumrange(2*pos + 1,mid+1,se,us,ue));
}
ll sum(ll a, ll b)
{
    return sumrange(1,1,m,a,b);
}
int main()
{
    fastio;
    cin >> n >> m;
    for0(i,1,m+1)
    {
        cin >> a[i];
    }
    build_set();
    int t; cin >> t;
    while(t --)
    {
        ll x1, y1, x2, y2, k; cin >> x1 >> y1 >> x2 >> y2 >> k;
        if(abs(x1 - x2) % k != 0 || abs(y1 - y2) % k != 0) cout << "NO" << endl;
        else
        {
            ll x = n - (n-x1) % k;
            if(y1 > y2) swap(y1,y2);
            if(sum(y1,y2) < x) cout << "YES\n";
            else if(sum(y1,y2) >= x) cout << "NO\n";
        }
    }


}