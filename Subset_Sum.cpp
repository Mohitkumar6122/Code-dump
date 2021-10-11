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

void calc(vl v, vl &X, ll l, ll n)
{
  for (int i = 0; i < (1 << n); ++i)
  {
    ll sum = 0;
    ff(j, 0, n)
    {
      if (i & (1 << j))
        sum += v[l + j];
    }
    X.pb(sum);
  }
}
void solve(vl & v, ll n, ll a, ll b){
  vl half1, half2;
  calc(v, half1, 0, n / 2);
  calc(v, half2, n / 2, (n - (n / 2)));
  
  sort(all(half2));
  ll ans = 0;
  for (int i = 0; i < sz(half1); ++i){
    // cout << half2[i] << " ";
    auto x = lb(all(half2), a - half1[i]);
    auto y = ub(all(half2), b - half1[i]);
    ans += (y - x);
  }
  cout << ans << "\n";
}
int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  ll t, q, n, a, b, c, d, k, l, m, r, x = 0, y = 0, z = 0, sum = 0, ans = 0, temp = 0, res = 0;
  cin >> n >> a >> b;
  vl v(n);
  for (int i = 0; i < n; ++i){
    cin >> v[i];
  }
  solve(v, n, a, b);
}
