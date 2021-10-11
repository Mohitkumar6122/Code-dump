// MOHIT KUMAR
#pragma GCC optimize("O3")
#pragma GCC target("sse4")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pin;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;
typedef vector<ll> vl;
typedef vector<pl> vp;

#define ff(i, a, b) for (ll i = a; i < (b); i++)
#define ffd(i, a, b) for (ll i = a; i <= b; i++)
#define fr(i, a, b) for (ll i = (b)-1; i >= a; i--)
#define ffr(i, a, b) for (ll i = b; i >= a; i--)
#define endl "\n"
#define sz(x) (ll)(x).size()
#define mp make_pair
#define pb push_back
#define f first
#define s second
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()

const ld pi = acos(-1);
const ll maxn = 1e6 + 5;
const int mod = 1e9 + 7;
const ll INF = 1e18;
const int MX = 2000000001; // check the limits, dummy

vl parent;
void init(ll n)
{
  ffd(i, 0, n) parent.pb(i);
}

ll find(ll n)
{
  return (parent[n] == n ? n : parent[n] = find(parent[n]));
}
void merge(ll a, ll b)
{
  a = find(a), b = find(b);
  if (a != b)
  {
    parent[a] = b;
  }
  return;
}
struct graph
{
  ll src, dest, weight;
};

vector<graph> v;

bool comp (graph & a, graph & b){
  return a.weight < b.weight;
}
int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  ll t, q, n, a, b, c, d, k, l, m, r, x = 0, y = 0, z = 0, sum = 0, ans = 0, temp = 0, res = 0;
  v.pb({0, 1, 4});
  v.pb({0, 2, 4});
  v.pb({1, 2, 2});
  v.pb({1, 0, 4});
  v.pb({2, 0, 4});
  v.pb({2, 1, 2});
  v.pb({2, 3, 3});
  v.pb({2, 5, 2});
  v.pb({2, 4, 4});
  v.pb({3, 2, 3});
  v.pb({3, 4, 3});
  v.pb({4, 2, 4});
  v.pb({4, 3, 3});
  v.pb({5, 2, 2});
  v.pb({5, 4, 3});
  n = 15;
  init(n);
  sort(v.begin(), v.end(), comp);
  ff(i, 0, n)
  {
    ll para = find(v[i].src), parb = find(v[i].dest);
    // cout << para << " " << parb << "\n";
    if (para != parb)
    {
      cout << v[i].src << " <-----> " << v[i].dest <<  " : " << v[i].weight << "\n";
      ans += v[i].weight;
      merge(v[i].src, v[i].dest);
    }
  }
  cout << ans << "\n";
}

/*  output 
  1 <-----> 2 : 2
  2 <-----> 5 : 2 
  2 <-----> 3 : 3
  3 <-----> 4 : 3
  0 <-----> 1 : 4
  14  
*/
