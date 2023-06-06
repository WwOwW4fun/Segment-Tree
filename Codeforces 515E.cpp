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
const int maxn = 2e5+7;
const ll inf = 1e9+7;

ll n, m, dist[maxn], height[maxn], pre[maxn];

struct node
{
    ll L, R, mx;
}tree[4*maxn];

node Update(node a, node b)
{
    node temp;
    temp.L = max(a.L, b.L);
    temp.R = max(a.R, b.R);
    temp.mx = max(max(a.mx, b.mx), a.R + b.L);
    return temp;
}
void Build(ll id, ll l, ll r)
{
    if (l == r)
    {
        tree[id].L = 2*height[l] + pre[l];
        tree[id].R = 2*height[l] - pre[l];
        tree[id].mx = -inf;
        return;
    }
    ll mid = (l+r)/2;
    Build(2*id, l, mid);
    Build(2*id+1, mid+1, r);
    tree[id] = Update(tree[2*id], tree[2*id+1]);
}
node Get(ll id, ll l, ll r, ll u, ll v)
{
    if (l == u && r == v)
    {
        return tree[id];
    }
    ll mid = (l+r)/2;
    if (v <= mid)
    {
        return Get(2*id, l, mid, u, v);
    }
    else if (u > mid)
    {
        return Get(2*id+1, mid+1, r, u, v);
    }
    else
    {
        node t1 = Get(2*id, l, mid, u, mid);
        node t2 = Get(2*id+1, mid+1, r, mid+1, v);
        node temp = Update(t1, t2);
        return temp;
    }
}

int main()
{
    cin >> n >> m;
    for (ll i=1; i<=n; i++)
    {
        cin >> dist[i];
        pre[i+1] = dist[i] + pre[i];
    }
    for (ll i=n+1; i<=2*n; i++)
    {
        pre[i+1] = pre[i] + dist[i-n];
    }
    for (ll i=1; i<=n; i++)
    {
        cin >> height[i];
        height[i+n] = height[i];
    }
    Build(1, 1, 2*n);
    for (ll i=1; i<=m; i++)
    {
        ll x, y;
        cin >> x >> y;
        if (x > y)
        {
            node ans = Get(1, 1, 2*n, y+1, x-1);
            cout << ans.mx << endl;
        }
        else
        {
            node ans = Get(1, 1, 2*n, y+1, n+x-1);
            cout << ans.mx << endl;
        }
    }
}