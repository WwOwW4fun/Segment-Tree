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
const int Max = 600000;
ll a[Max];
ll n;
struct node{
    ll val,pre_len,suf_len;
};
node tree[Max];
ll cal(ll a)
{
    return a*(a+1) / 2;
}
void build_branch(ll id, ll pos, ll ss, ll se)
{
    if(ss > pos || se < pos) return ;
    if(ss == se)
    {
        tree[id].val = 1;
        tree[id].pre_len = 1;
        tree[id].suf_len = 1;
        return;
    }
    ll mid = (ss + se) / 2;
    build_branch(2*id,pos, ss,mid);
    build_branch(2*id + 1,pos,mid + 1,se);
    tree[id].val = tree[2*id].val + tree[2*id + 1].val;
    tree[id].pre_len = tree[2*id].pre_len;
    tree[id].suf_len = tree[2*id+1].suf_len;
    if(a[mid+1] >= a[mid])
    {
        tree[id].val =  tree[2*id].val + tree[2*id + 1].val - cal(tree[2*id].suf_len) - cal(tree[2*id + 1].pre_len) + cal(tree[2*id].suf_len + tree[2*id+1].pre_len);
        if(tree[id].pre_len == mid - ss + 1)
        {
            tree[id].pre_len +=  tree[2*id + 1].pre_len;
        }
        if(tree[id].suf_len == se - mid)
        {
            tree[id].suf_len += tree[2*id].suf_len;
        }
    }

}
void build(ll pos)
{
    return build_branch(1,pos,0,n-1);
}
ll get(ll id, ll us, ll ue, ll ss, ll se)
{
    if(ss >= us and se <= ue) return tree[id].val;
    ll mid = (se + ss) / 2;
    if(ue <= mid) return get(2*id,us,ue,ss,mid);
    if(us > mid) return get(2*id + 1,us,ue,mid+1,se);
    ll ans  = get(2*id,us,mid,ss,mid) + get(2*id + 1,mid+1,ue,mid+1,se);
    if(a[mid+1] >= a[mid])
    {
        ll x = min (mid - us + 1,tree[2*id].suf_len);
        ll y = min (ue - mid, tree[2*id+1].pre_len);
        ans = ans + cal(x + y) - cal(x) - cal(y);
    }
    return ans;
}
ll query2(ll l, ll r)
{
    return get(1,l,r,0,n-1);
}
void input()
{
    ll m; cin >> n >> m;
    for0(i,0,n)
    {
        cin >> a[i];
        build(i);
    }
    while(m--)
    {
        ll qu, l, r; cin >> qu >> l >> r;
        if(qu == 1)
        {
            l--;
            a[l] = r;
            build(l);
        }
        if(qu == 2)
        {
            l--;r--;
            cout << query2(l,r) << endl;
        }
    }
}
int main()
{
    input();
}