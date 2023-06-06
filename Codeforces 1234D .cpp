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
const int MX = 1000000;
ll tree[MX];
string a;
void build_set1(int pos,int ss, int se)
{
   if(ss == se)
   {
       tree[pos] = (1 << (a[ss - 1] - 'a'));
       return;
   }
   int mid = (ss + se) / 2;
   build_set1(2*pos,ss,mid);
   build_set1(2*pos+1,mid+1,se);
   tree[pos] = (tree[pos*2]|tree[pos*2+1]);
}
void build_set()
{
    build_set1(1,1,n);
}
void updaterange(int pos, int ss, int se, int id, char diff)
{
    if(ss > id || id > se) return;
    if(ss == se)
    {
        tree[pos] = (1 << (diff - 'a'));
        return;
    }
    int mid = (ss + se) / 2;
    updaterange(2*pos,ss,mid,id,diff);
    updaterange(2*pos+1,mid+1,se,id,diff);
    tree[pos] = tree[pos*2]|tree[pos*2 + 1];
}
void update(int a, char d)
{
    updaterange(1,1,n,a,d);
}
ll sumrange(int pos, int ss, int se, int us, int ue)
{
    if(ss > ue || se < us) return 0;
    if(ss >= us and se <= ue) return tree[pos];
    int mid  = (se + ss) / 2;
    return (sumrange(2*pos,ss,mid,us,ue)|sumrange(2*pos + 1,mid+1,se,us,ue));
}
ll sum(int a, int b)
{
    return sumrange(1,1,n,a,b);
}
int main()
{
    output;
    cin >> a;
    n = a.length();
    int q; cin >> q;
    build_set();
    while(q --)
    {
        int qu; cin >> qu;
        if(qu == 1)
        {
           char c; int x; cin >> x >> c;
            update(x,c);
        }
        if(qu == 2)
        {
            int x, y; cin >> x >> y;
            int ans = sum(x, y);
            cout << __builtin_popcount(ans) << endl;

        }
    }
}
