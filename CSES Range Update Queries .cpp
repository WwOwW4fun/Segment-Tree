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
   tree[pos] =tree[pos*2]+tree[pos*2+1];
}
void build_set()
{
    build_set1(1,0,n-1);
}
void updaterange(int pos, int ss, int se, int us, int ue, int diff)
{
    if(ss > se || ss > ue || se < us) return;
    if(lazy[pos] != 0)
    {
        tree[pos] += (se-ss+1) * lazy[pos];
        if(ss != se)
        {
            lazy[2*pos] += lazy[pos];
            lazy[2*pos + 1] += lazy[pos];
        }
        lazy[pos] = 0;
    }

    if(ss >= us and se <= ue)
    {
        tree[pos] += (se - ss + 1)*diff;
        if(ss != se)
        {
            lazy[2*pos] += diff;
            lazy[2*pos + 1] += diff;
        }
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
ll sumrange(int pos, int ss, int se, int us, int ue)
{
    if(ss > se || ss > ue || se < us) return 0;
    if(lazy[pos] != 0)
    {
        tree[pos] += (se-ss+1) * lazy[pos];
        if(ss != se)
        {
            lazy[2*pos] += lazy[pos];
            lazy[2*pos + 1] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if(ss >= us and se <= ue) return tree[pos];
    int mid  = (se + ss) / 2;
    return sumrange(2*pos,ss,mid,us,ue)+sumrange(2*pos + 1,mid+1,se,us,ue);
}
ll sum(int a, int b)
{
    return sumrange(1,0,n-1,a,b);
}
int main()
{
    int m;
    cin >> n >> m;
    memset(lazy,0,sizeof(lazy));
    for0(i,0,n)
    {
        cin >> a[i];
    }
    build_set();
    for0(i,0,m)
    {
        int x; cin >> x;
        if(x == 1)
        {
            int y , z, d; cin >> y >> z >> d;
            update(y-1,z-1,d);
        }
        if(x == 2)
        {
            int a ; cin >> a;
            cout << sum(a-1,a-1) << endl;
        }
    }

}