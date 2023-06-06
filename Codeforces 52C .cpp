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
ll n;
const int Max = 10000000;
ll tree[Max], lazy[Max], a[Max];
void build_set1(ll pos,ll ss, ll se)
{
   if(ss == se)
   {
       tree[pos] = a[ss];
       return;
   }
   ll mid = (ss + se) / 2;
   build_set1(2*pos,ss,mid);
   build_set1(2*pos+1,mid+1,se);
   tree[pos] = min(tree[pos*2],tree[pos*2+1]);
}
void build_set()
{
    build_set1(1,0,n-1);
}
void updaterange(ll pos, ll ss, ll se, ll us, ll ue, ll diff)
{
    
    if(lazy[pos] != 0)
    {
        tree[pos] +=  lazy[pos];
        if(ss != se)
        {
            lazy[2*pos] += lazy[pos];
            lazy[2*pos + 1] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if(ss > ue || se < us) return;
    if(ss >= us and se <= ue)
    {
        tree[pos] += diff;
        if(ss != se)
        {
            lazy[2*pos] += diff;
            lazy[2*pos + 1] += diff;
        }
        return ;

    }
    ll mid = (ss + se) / 2;
    updaterange(2*pos,ss,mid,us,ue,diff);
    updaterange(2*pos+1,mid+1,se,us,ue,diff);
    tree[pos] = min(tree[pos*2],tree[pos*2 + 1]);
}
void update(ll a, ll b, ll d)
{
    updaterange(1,0,n-1,a,b,d);
}
ll sumrange(ll pos, ll ss, ll se, ll us, ll ue)
{
     if(ss > ue || se < us) return 1e18;
    if(lazy[pos] != 0)
    {
        tree[pos] += lazy[pos];
        if(ss != se)
        {
            lazy[2*pos] += lazy[pos];
            lazy[2*pos + 1] += lazy[pos];
        }
        lazy[pos] = 0;
    }
   
    if(ss >= us and se <= ue) return tree[pos];
    int mid  = (se + ss) / 2;
    return min(sumrange(2*pos,ss,mid,us,ue),sumrange(2*pos + 1,mid+1,se,us,ue));
}
ll sum(ll a, ll b)
{
    return sumrange(1,0,n-1,a,b);
}
int main()
{
    fastio;
    cin >> n;
    for0(i,0,n)
    {
        cin >> a[i];
    }
    build_set();
    int m; cin >> m;
    cin.ignore();
    
    while(m --)
    {
        string str; getline(cin ,str);
        stringstream ss (str);
        ll c;
        vector <ll> v;
        while(ss >> c)
        {
            v.push_back(c);
        }
        if(v.size() == 2)
        {
            if(v[0] > v[1])
            {
                ll x = sum(v[0], n - 1);
                ll y = sum(0,v[1]);
                cout << min(x, y) << endl;
            }
            else cout << sum (v[0],v[1]) << endl;
        }
        else
        {
            if(v[0] > v[1])
            {
                update(v[0],n-1,v[2]);
                update(0,v[1],v[2]);
            }
            else update(v[0],v[1],v[2]);
        }
    }

}