// MOHIT KUMAR
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> cd;

typedef pair<int, int> pin;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

#define ff(i, a, b) for ( ll i=a; i<(b); i++)
#define ffd(i, a, b) for ( ll i=a; i<= b; i++)
#define fr(i, a, b) for ( ll i = (b)-1; i >= a; i--)
#define ffr(i, a, b) for ( ll i = b ; i >= a; i--)
#define vl vector < ll >
#define vp vector < pl >
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

const ld pi = acos(-1) ;
const ll maxn = 3e5 + 5 ;
const int mod = 998244353 ;
const ll INF = 1e18 ;
const int MX = 2000000001 ; // check the limits, dummy

bool comp ( pair< ld, pl > &a, pair< ld, pl > &b) {
  return (a.f < b.f) ;
}
int main() {
  ios_base::sync_with_stdio(0) , cin.tie(0);
  ll n, ans = 0 ;
  cin >> n ;

  // FRATIONAL KNAPSACK PROBLEM

  vector < pair < ld , pl > > v(n) ;
  /*
       v[i].f = profit to weight ratio
       v[i].s.f = profit
       v[i].s.s = weight
  */

  ff(i, 0, n) {
    cin >> a >> b;
    v[i].s.f = a, v[i].s.s = b ;
    v[i].f = a / b ;
  }
  sort(all(v)) ;
  reverse(all(v)) ;
  ll w ;
  cin >> w ;
  ff(i, 0, n) {
    if (v[i].s.s + ans < w) {
      cout << "Pair with full profit " << v[i].s.f << " " << v[i].s.s << "\n" ;
      res += v[i].s.f ;
      ans += v[i].s.s ;
    }
    else  {
      cout << "Pair with fractional profit " << v[i].s.f << " " << v[i].s.s << "\n" ;
      res += ((w - ans)  * v[i].s.f) / v[i].s.s ;
      ans = w ;
      break ;
    }
  }
  cout << "Total profit " << res << endl ;
}
