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
typedef vector < ll > vl ;
typedef vector < pl > vp ;

#define ff(i, a, b) for (ll i = a; i < (b); i++)
#define ffd(i, a, b) for (ll i = a; i <= b; i++)
#define fr(i, a, b) for (ll i = (b)-1; i >= a; i--)
#define ffr(i, a, b) for (ll i = b ; i >= a; i--)
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
const ll maxn = 1e6 + 5 ;
const int mod = 1e9 + 7 ;
const ll INF = 1e18 ;
const int MX = 2000000001 ; // check the limits, dummy

bool vis[maxn] = {0} ;

// USING MIN HEAP aka PRIORITY QUEUE  
void djikstra( vector < pl > v[], ll s, ll n) {
  vl dist(n, INF), par(n, -1) ;
  priority_queue < pl , vp, greater < pl >> pq ; // min heap 
  
  //Always push distance as first cause it will sort according to distance else you have to make a custim comparator operator .
  
  pq.push({0, s}) ; // push source node with 0 distance
  while (sz(pq)) {
    pl topp = pq.top() ; // min dist node
    pq.pop() ;
    if (vis[topp.s]) continue ; // if already present in SPG
    vis[topp.s] = 1 ; // marked as visited
    dist[topp.s] = topp.f ; // distance is topp.f 
    for (auto x : v[topp.s]) {
      if (!vis[x.s]) {
        ll temp = dist[topp.s] + x.f ;
        if (temp < dist[x.s]) {
          dist[x.s] = temp ;
          par[x.s] = topp.s ;   // update distance if lower than parent node
        }
        pq.push({dist[x.s], x.s}) ; // push updated distane in priority queue
      }
    }

  }
  for (auto x : dist) cout << x << " " ; // prints Shortests Distance Graph path from source node 
  cout << "\n" ;
  for (auto x : par)  cout << x << " "  ;
  // FOR TRACKING PATH 
  //  for (int i = dest -1; i != source and i != -1; i = par[i])
  //    cout << i << " <--- ";

}

// USING SET 
void djikstra( vector < pl > v[], ll s, ll n) {
  vl dist(n, INF) ;

  set < pl > st ;
  st.insert({0, s}) ;

  while (sz(st)) {
    pl topp = *(st.begin()) ;
    st.erase(st.begin()) ;
    if (vis[topp.s]) continue ;
    vis[topp.s] = 1 ;
    dist[topp.s]  = topp.f ;
    for (auto x : v[topp.s]) {
      if (!vis[x.s]) {
        if (dist[x.s] > dist[topp.s] + x.f) {
          dist[x.s] = dist[topp.s] + x.f ;
        }
        st.insert({dist[x.s], x.s}) ;
      }
    }
  }
  for (auto x : dist) cout << x << " " ; // prints Shortests Distance Graph path from source node
  cout << "\n" ;
  // for (auto x : par)  cout << x << " "  ;

}

int main() {
  ios_base::sync_with_stdio(0) , cin.tie(0);
  ll t, q, n, a, b, c, d, k, l, m, r,  x = 0, y = 0, z = 0 , sum = 0, ans = 0, temp = 0, res = 0 ;
  vp v[9] ;
  ff(i, 0, 14) {
    cin >> a >> b >> c ;
    v[a].pb({c, b}) ;
    v[b].pb({c, a}) ;
  }
  djikstra(v, 0, 9) ;
}
/* INPUT 
THIS INPUT && OUTPUT IS FOR UNDIRECTED GRAPH
0 1 4
0 7 8 
1 2 8
1 7 11
2 3 7
2 8 2
2 5 4
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7
*/

/* OUTPUT
0 4 12 19 21 11 9 8 14 
-1 0 1 2 5 6 7 0 2
*/
