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
#define pll pair<long long, long long >
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
const int Max = 1e6;
ll n, q;
ll a[Max];
pll tree[2*Max];
ll factor[4*Max];
void build(int id, int ss, int se)
{
    if(ss == se)
    {
        tree[id].first = tree[id].second = a[ss];
        return;
    }
    int mid = (ss + se) / 2;
    build(2*id,ss,mid);
    build(2*id + 1,mid+1, se);
    tree[id].first = tree[2*id].first + tree[2*id + 1].first;
    tree[id].second = max(tree[2*id + 1].second,tree[2*id].second);
}
void build_tree()
{
    build(1,0,n-1);
}
void updaterange(int id, int ss, int se, int us, int ue)
{
    if(ss > ue || se < us) return;
    if(tree[id].second <= 2) return;
    if(ss >= us and se <= ue and ss == se)
    {
        tree[id].first = tree[id].second = factor[tree[id].second];
        return;
    }
    int mid = (ss + se) / 2;
    updaterange(2*id,ss,mid,us,ue);
    updaterange(2*id + 1,mid + 1,se,us,ue);
    tree[id].first = tree[2*id].first + tree[2*id + 1].first;
    tree[id].second = max(tree[2*id + 1].second,tree[2*id].second);
}
void update(int us, int ue)
{
    updaterange(1,0,n-1,us,ue);
}
ll getrange(int id, int ss, int se, int us, int ue)
{
    if(ss > ue || se < us) return 0;
    if(ss >= us and se <= ue) return tree[id].first;
    int mid = (ss + se)/ 2;
    return getrange(2*id,ss,mid,us,ue) + getrange(2*id + 1,mid + 1,se,us,ue);
}
ll get(int us, int ue)
{
   return getrange(1,0,n - 1, us,ue);
}
void solve()
{
    for0(i,1,2*Max + 1)
    {
        for(int j = i; j <= 2*Max; j += i)
        {
            factor[j] ++;
        }
    }
}
void input()
{
    cin >> n >> q;
    for0(i,0,n) cin >> a[i];
    solve();
    build_tree();
    while(q --)
    {
        int qu, l, r; cin >> qu >> l >> r;
        l--, r --;
        if(qu == 1)
        {
            update(l,r);
        }
        if(qu == 2)
        {
            cout << get(l,r) << endl;
        }
    }
}
int main()
{
    fastio;
    input();
}