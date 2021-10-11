// BELLMAN FORD ALGORITHM FOR SHORTEST PATH IN WEIGHTED DIRECTED GRAPH
 
void bellman( vp v[], ll s, ll n) {
  vl dist(n, INF), par(n, -1) ;
  dist[s] = 0 ;
  int xl = -1 ;
  ff(j, 0, n - 1) {
    ff(i, 0, n) {
      for (auto x : v[i]) {
        ll cur_dist = x.f ;
        ll v = x.s ;
        if (dist[v] > cur_dist + dist[i]) {
          dist[v] = cur_dist + dist[i] ; // updating distance.
          par[v] = i ; // updating parent for retrieval of path.
          xl = v ;
        }
      }
    }
 
    // printing shortest distance after every iteration.
    cout << j << "\n" ;
    for (auto x : dist)cout << x << "  " ;
    cout << "\n" ;
  }
  cout << xl << " cy \n" ;
  xl = par[xl] ;
 
  bool  ch = 0 ;
  ff(i, 0, n) {
    for (auto x : v[i]) {
      ll cur_dist = x.f ;
      ll v = x.s ;
      if (dist[v] > cur_dist + dist[i]) {
        dist[v] = -INF ; // negative cycle exist to this node
        ch = 1 ;
      }
      //   for (auto x : dist) {
      //     if (x == -INF) cout << "-x " ;
      //     else cout << x << " " ;
      //   } cout << "\n" ;
    }
  }
// int chh = 0 ;
  if (ch) cout << "Negative cycle exists\n" ;
// if (par[n - 1] == -1) { cout << "No PAth Exist\n" ;}
// else {
//   for ( int i = 5; i != 0; i = par[i]) {
//     // if (ch and i == xl and chh) break ;
//     // chh = 1 ;
//     cout << i << "\n" ; // path printed in reverse order
//   }
// }
  for (auto x : dist) cout << x << " " ;
}
 
void bellmanford( vector < vl > & v, ll s, ll n ) {
  vl dist(n, INF), par(n, -1) ;
  dist[s] = 0, par[s] = -1 ;
 
  ff(k , 0, n - 1) {
    ff(i, 0, n) {
      ff(j, 0, n) {
        if (dist[i] != INF and v[i][j] and dist[j] > dist[i] + v[i][j]) {
          dist[j] = dist[i] + v[i][j] ;
          par[j] = i ;
        }
      }
    }
  }
  bool ch = false ;
  ff(k , 0, n - 1) {
    ff(i, 0, n) {
      ff(j, 0, n) {
        if ( v[i][j] and dist[j] - v[i][j] > dist[i]) {
          dist[j] = -INF ;
          ch = 1 ;
        }
      }
    }
  }
 
  if (ch) cout << "-VE CYCLE EXISTS !\n" ;
 
  cout << "DISTANCE ARRAY \n" ;
  for (int i = 0; i < n; i++)
    if (i != s)
      cout << s << " - " << i << "\t" << dist[i] << endl;
 
  cout << "\nPARENT ARRAY \n" ;
  for (auto x : par) cout << x << " " ;
  cout << "\n" ;
 
  //printing source
  if (par[n - 1] == -1) cout << "NO PATH EXISTS\n" ;
  else {
    for (ll i = n - 1; i != -1; i = par[i]) {
      cout << i  ;
      if (i != s)cout <<  " <--- " ;
    }
  }
 
}
 
void floyd_warshall( vector < vl > v, ll n) {
  std::vector<vl> dp = v, par(n, vl(n, -1));
 
  ff(i, 0, n) {
    ff(j, 0, n) par[i][j] = j ;
  }
  ff(k, 0, n) {
    ff(i, 0, n) {
      ff(j, 0, n) {
        if ( dp[i][k] < INF and dp[k][j] < INF) {
          if (dp[i][j] > dp[i][k] + dp[k][j]) {
            dp[i][j] =  dp[i][k] + dp[k][j] ;
            par[i][j] = par[i][k] ;
          }
 
        }
      }
    }
  }
  bool ch = false ;
  ff(i, 0, n) {
    if (dp[i][i] < 0) {
      ch = 1 ;
      break ;
    }
  }
  if (ch) cout << "Negative CYCLE EXISTS\n" ;
 
  cout << "Shortest path matrix\n" ;
  ff(i, 0, n) {
    ff(j, 0, n) {
      cout << dp[i][j] << " " ;
    } cout << "\n" ;
  }
  cout << "\nPARENT ARRAY\n" ;
  ff(i, 0, n) {
    ff(j, 0, n) {
      cout << par[i][j] + 1 << " " ;
    } cout << "\n" ;
  }
  cout << "\nretrieval OF PATH\n" ;
  ll s = 4 , e = 1 ;
  --s , --e ;
  if (par[s][e] == e) return ;
  while ( s != e) {
    cout << s + 1 << " <--- " ;
    s = par[s][e] ;
  } cout << ++e ;
 
}
 
