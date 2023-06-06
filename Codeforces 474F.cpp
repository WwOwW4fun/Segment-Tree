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
   tree[pos] = __gcd(tree[pos*2],tree[pos*2+1]);
}
void build_set()
{
    build_set1(1,0,n-1);
}

ll sumrange(int pos, int ss, int se, int us, int ue)
{
    if(ss > se || ss > ue || se < us) return 0;
    
    if(ss >= us and se <= ue) return tree[pos];
    int mid  = (se + ss) / 2;
    return __gcd(sumrange(2*pos,ss,mid,us,ue),sumrange(2*pos + 1,mid+1,se,us,ue));
}
ll sum(int a, int b)
{
    return sumrange(1,0,n-1,a,b);
}
vector<pair<int,int>> v;
int main()
{
    cin >> n;
    for0(i,0,n)
    {
        cin >> a[i];
        v.push_back({a[i],i});
    }
    sort(v.begin(),v.end());
    build_set();
    int q; cin >> q;
    while(q--)
    {
        int a, b; cin >> a >> b;
        a--, b--;
        int c = sum(a,b);
        cout << (b - a + 1) - (upper_bound(v.begin(),v.end(),make_pair(c,b)) - lower_bound(v.begin(),v.end(),make_pair(c,a))) << endl;
    }
}