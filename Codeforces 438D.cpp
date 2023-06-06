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
const int Max = 6e5;
pll tree[Max];
ll a[Max];
ll n ,q;
void build_tree(int id, int ss, int se)
{
    if(ss == se)
    {
        tree[id].first = tree[id].second = a[ss];
        return;
    }
    int mid = (ss + se) / 2;
    build_tree(2*id,ss,mid);
    build_tree(2*id + 1,mid + 1, se);
    tree[id].first = tree[2*id].first + tree[2*id + 1].first;
    tree[id].second = max(tree[2*id].second , tree[2*id + 1].second);
}
void build()
{
    build_tree(1,0,n - 1);
}
void update1(int id, int ss, int se, int pos, int diff)
{
    if(ss > se || ss > pos || se < pos) return;
    if(ss == se)
    {
        tree[id].first = tree[id].second = diff;
        return;
    }
    int mid = (ss + se) / 2;
    update1(2*id,ss,mid,pos,diff);
    update1(2*id + 1,mid + 1,se,pos,diff);
    tree[id].first = tree[2*id].first + tree[2*id + 1].first;
    tree[id].second = max(tree[2*id].second , tree[2*id + 1].second);
}
void update_range1(int pos, int diff)
{
    update1(1,0,n-1, pos, diff);
}
void update2(int id, int ss, int se, int us, int ue, int mod)
{
    if(ss > se || ss > ue || se < us || tree[id].second < mod) return;
    if(ss == se)
    {
        tree[id].first %= mod;
        tree[id].second = tree[id].first;
        return;
    }
    int mid = (ss + se) / 2;
    update2(2*id,ss,mid,us,ue,mod);
    update2(2*id + 1,mid + 1, se, us, ue, mod);
    tree[id].first = tree[2*id].first + tree[2*id + 1].first;
    tree[id].second = max(tree[2*id].second , tree[2*id + 1].second);
}
void update_range2(int us, int ue, int mod)
{
    update2(1,0,n-1,us,ue,mod);
}
ll get(int id, int ss, int se, int us, int ue)
{
    if(ss > se || ss > ue || se < us) return 0;
    if(ss >= us and se <= ue) return tree[id].first;
    int mid = (ss + se) / 2;
    return get(2*id,ss,mid,us,ue) + get(2*id + 1, mid + 1,se, us, ue);
}
ll get_range(int us, int ue)
{
    return get(1,0, n - 1, us,ue);
}
void input()
{
    cin >> n >> q;
    for0(i,0,n) cin >> a[i];
    build();
    while(q --)
    {
        int qu; cin >> qu;
        if(qu == 1)
        {
            int l, r; cin >> l >> r;
            l--, r--;
            cout << get_range(l, r) << endl;
        }
        if(qu == 2)
        {
            int l, r, mod; cin >> l >> r >> mod;
            l--, r--;
            update_range2(l,r,mod);
        }
        if(qu == 3)
        {
            int pos, d; cin >> pos >> d;
            pos --;
            update_range1(pos,d);
        }
    }
}
int main()
{
    output;
    input();
}