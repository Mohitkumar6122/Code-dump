// GRAPH SOLTUIONS

// MOHIT KUMAR
#pragma GCC optimize("O3")
#pragma GCC target("sse4")

#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
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

struct Graph
{
  int a, b, w;
};

vector<vector<int>> v, rev;
vector<vector<pair<int, int>>> graph;
vector<Graph> mstGraph;
vector<bool> vis;
vector<int> par, siz, dis;

//DISJOINT SET UNION
void init(int n){
  par.resize(n);
  siz.resize(n, 1);
  ff(i, 0, n) par[i] = i;
}
int find(int n){
  return par[n] == n ? n : par[n] = find(par[n]);
}
bool merge(int a, int b){
  a = find(a);
  b = find(b);
  if(a != b){
    if (siz[a] < siz[b])
      swap(a, b);
    par[b] = a;
    siz[a] += siz[b];
    return true;
  }
  return false;
}
bool comp(const Graph & a, const Graph & b){
  return a.w < b.w;
}

bool checkCycleUndirected(int n, int par)
{
  vis[n] = true;
  for (auto child : v[n])
  {
    if (!vis[child])
    {
      if (checkCycleUndirected(child, n))
        return true;
    }
    else if (child != par)
    {
      return true;
    }
  }
  return false;
}

void containsCycleUndirected(){
  int n, m;
  cin >> n >> m;
  v.resize(n);
  for (auto x : v)
    x.resize(m);
  vis.resize(n);
  int edgeFrom, edgeTo;
  for (int i = 0; i < m; ++i)
  {
    cin >> edgeFrom >> edgeTo;
    v[edgeFrom].pb(edgeTo);
    v[edgeTo].pb(edgeFrom);
  }

  for (int i = 0; i < n; ++i)
  {
    if (vis[i])
      continue;
    if (checkCycleUndirected(i, -1))
    {
      cout << "Yes it contains a cycle\n";
      return ;
    }
  }
  cout << "Does't contains a cycle\n";
}

bool checkCycleDirected(int n, int par, set < int > & st){
  vis[n] = true;
  st.insert(n);
  for(auto x : v[n]){
    if (!vis[x]){
      if (checkCycleDirected(x, n, st))
        return true;
    }
    else if (x != par && st.count(x)){
      cout << n << " " << x << " " << par << "\n";
      return true;
    }
  }
  st.erase(n);
  return false;
}

void containcCyclesDirected(){
  int n, m ;
  cin >> n >> m;
  v.resize(n);
  vis.resize(n);
  // ff(i, 0, n) v[i].resize(m);

  for (int i = 0; i < m; ++i){
    int a, b;
    cin >> a >> b;
    v[a].pb(b);
  }
  set<int> st;
  for (int i = 0; i < n; ++i){
    if (vis[i])
      continue;
    if (checkCycleDirected(i, -1, st)){
      cout << "Yes it contains a cycle\n";
      return;
    }
  }
  cout << "It does not contain a cycle\n";
}

void topoSort(int n, stack < int > & sorted){
  vis[n] = true ;
  for(auto x : v[n]){
    if (!vis[x]){
      topoSort(x, sorted);
    }
  }
  sorted.push(n);
}
void topologicalSorting(){
  int n, m ;
  cin >> n >> m;
  v.resize(n);
  vis.resize(n);

  for (int i = 0; i < m; ++i)
  {
    int a, b;
    cin >> a >> b;
    v[a].pb(b);
  }
  stack<int> sorted ; 
  for (int i = 0; i < n; ++i){
    if (!vis[i]){
      topoSort(i, sorted);
    }
  }
  while(!sorted.empty()){
    cout << sorted.top() << " ";
    sorted.pop();
  }
  return;
}

void kahnTopologicalSorting(){
  int n, m ;
  cin >> n >> m;
  v.resize(n);
  vector<int> inDegree(n, 0);
  queue<int> q;
  vector<int> topoSort;
  int from, to, cnt = 0;

  for(int i = 0; i < m; ++i){
    cin >> from >> to;
    v[from].push_back(to);
    ++inDegree[to];
  }

  for (int i = 0; i < n; ++i) {
    if (!inDegree[i])
      q.push(i);
  }

  while(!q.empty()){
    int u = q.front();
    q.pop();
    ++cnt;
    topoSort.push_back(u);
    for(auto x : v[u]){
      if(!(--inDegree[x]))
        q.push(x);
    }
  }
  if(cnt != n) {
    cout << "Cycle Detected\n";
  }
  cout << "Topo SOrt for the above graph is : ";
  for(auto x : topoSort)
    cout << x << " ";
  
}


void kosarajuStronglyConnecComponents(){
  /*  STEPS TO RUN ALGO
    1. Make a stack and apply dfs on all ndoes and push it in stack
    2. Reverse the graph (i.e  Node u -> v now points to v -> u).
    3. Pop element from stack and apply dfs on popped node 
    4. dfs traversal of popped node is SCC .
    For proof : https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
  */

  int n, m;
  cin >> n >> m ;
  vis.resize(n + 1, false);
  v.resize(n + 1);
  rev.resize(n + 1);

  ff(i, 0, m){
    int a, b ;
    cin >> a >> b ;
    v[a].pb(b) ;
    rev[b].pb(a);
  }
  stack<int> st;
  int cc = 0;

  // lambda function for DFS .
  // if opr -> 0 : simple dfs for pushing in stack
  // else opr -> 1 : finding the SCC of graph.
  function<void(vector<vector<int>>, int, int )> dfs = [&](vector<vector<int>>graph, int n, int opr)
  {
    vis[n] = true;
    ++cc;
    for(auto x : graph[n]){
      if (!vis[x])
        dfs(graph, x, opr);
    }
    if(opr & 1) st.push(n);
    else
      cout << n << " ";
  };

  ffd(i, 1, n){
    if (!vis[i])
      dfs(v, i, 1);
  }
  // cout << "njk";
  fill(all(vis), false);
 
  int oddComp = 0 ;

  while(!st.empty()){
    int x = st.top();
    st.pop();
    if (!vis[x]){
      cc = 0;
      dfs(rev, x, 0);
      cout << "\n";
      oddComp += cc & 1 ? cc : -cc;
    }
  }
  cout << oddComp;
  
  /* PRINTING REVERSE GRAPH 
  ffd(i, 1, n){
    cout << i << " : ";
    for(auto c : rev[i])
      cout << c << " ";
    cout << "\n";
  }
  */
}

void kruskalMST(){
  /*
    1. Sort all the edges in non-decreasing order of their weight. 
    2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle is not formed, include this edge. Else, discard it. 
    3. Repeat step#2 until there are (V-1) edges in the spanning tree.
  */

  int n = 15;
  init(n);
  mstGraph.pb({0, 1, 4});
  mstGraph.pb({0, 2, 4});
  mstGraph.pb({1, 2, 2});
  mstGraph.pb({1, 0, 4});
  mstGraph.pb({2, 0, 4});
  mstGraph.pb({2, 1, 2});
  mstGraph.pb({2, 3, 3});
  mstGraph.pb({2, 5, 2});
  mstGraph.pb({2, 4, 4});
  mstGraph.pb({3, 2, 3});
  mstGraph.pb({3, 4, 3});
  mstGraph.pb({4, 2, 4});
  mstGraph.pb({4, 3, 3});
  mstGraph.pb({5, 2, 2});
  mstGraph.pb({5, 4, 3});

  int edges = 0, mst_weight = 0;
  sort(all(mstGraph), comp);

  ff(i, 0, n)
  {
    if (edges == n - 1)
      break;
    if (merge(mstGraph[i].a, mstGraph[i].b))
    {
      mst_weight += mstGraph[i].w;
      cout << mstGraph[i].a << " <-----> " << mstGraph[i].b << "\n";
      ++edges;
    }
  }
  cout << mst_weight;
}

void primMST(){
  int n, m ;
  cin >> n >> m;
  graph.resize(n) ;
  vis.resize(n, false);
  for (int i = 0; i < m; ++i){
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].pb({b, c});
    graph[b].pb({a, c});
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  // weight, source node;
  pq.push({0, 0});
  int mst_weight = 0;
  while(!pq.empty()){
    int weight = pq.top().f, u = pq.top().s;
    pq.pop();
    if (vis[u])
      continue;
    vis[u] = true;
    mst_weight += weight;
    // cout << u << " " << weight << "\n";
    for(auto v : graph[u]){
      if(!vis[v.f])
        pq.push({v.s, v.f});
    }
  }
  cout << mst_weight << "\n";
}

//!SHORTEST PATH ALGO 

void djikstra(){
  int n, m ;
  cin >> n >> m;
  graph.resize(n);
  dis.resize(n, INT_MAX);
  vis.resize(n, false);
  par.resize(n, -1);
  for (int i = 0; i < m; ++i){
    int a, b, c;
    cin >> a >> b >> c;
    graph[a].push_back(make_pair(b, c));
    // IF GRAPH IS UNDIRECTED
    // graph[b].pb({a, c});
  }
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
  // distance of source -> 0, source 1 ;
  pq.push({0, 0});
  dis[0] = 0;
  while(!pq.empty()){
    int weight = pq.top().first, u = pq.top().second;
    pq.pop();
    // cout << u << " <--> " << weight << "\n";
    if (vis[u])
      continue;
    vis[u] = true;
    dis[u] = weight;
    for (auto v : graph[u])
    {
      if (!vis[v.f])
      {
        if (weight + v.s < dis[v.f])
        {
          dis[v.f] = weight + v.s;
          par[v.f] = u;
        }
        pq.push({dis[v.f], v.f});
      }
    }
  }
  for (int j = 0; j < n; ++j)
  {
    int x = j;
    cout << "Dist " << dis[x] << " || ";
    cout << "Path: " << x << " <-- " ;
    int i = par[x];
    while(i != -1){
      cout << i;
      if (i != -1 )
        cout << " <-- ";
      i = par[i];
    }
    // cout << " distance " << dis[i]; 
    cout << "\n";
  }
}

void bellmanFord(){
  int n, m ;
  cin >> n >> m ;
  dis.resize(n, INT_MAX);
  for (int i = 0; i < m; ++i){
    int a, b, c;
    cin >> a >> b >> c;
    mstGraph.push_back({a, b, c});
  }
  dis[0] = 0;
  for (int i = 0; i < n - 1; ++i){
    for (int j = 0; j < m; ++j){
      int u = mstGraph[j].a, weight = mstGraph[j].w, v = mstGraph[j].b;
      // cout << u << "--> "  << v << " " << weight << "\n";
      if(dis[u] != INT_MAX && dis[v] > dis[u] + weight){
        dis[v] = dis[u] + weight;
      }
    }
  }
  for(auto x : dis)
    cout << x << " ";
}

void floydWarshall(){
  int n;
  v.resize(n) ;
  ff(i, 0, n) v[i].resize(n);

  for(int i = 0; i < n; ++i){
    for (int j = 0; j < n; ++j){
      cin >> v[i][j];
    }
  }
  vector<vector<int>> dp = v;
  ff(k, 0, n){
    ff(i, 0, n){
      ff(j, 0, n){
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }

  ff(i,0, n){
    if(dp[i][i] < 0){
      cout << "NEGATIVE CYCLE REPORTED\n";
    }
  }
  ff(i, 0, n){
    ff(j, 0, n){
      cout << dp[i][j] << " ";
    }
    cout << "\n";
  }
}

void solve(){
  set < pl> st ;
  st.insert({10, 20});
  // st.insert({30, 40});
  auto it = st.lower_bound({15, 20}) ;
  // --it;
  auto itr = st.upper_bound({15, 20});
  // cout << *it.first;
  pl x = *it;
  cout << x.f << " " << x.s;
  cout << "\n" << (*itr).f << " " << (*itr).s ; 
}

void grassHopperandTree(){
  int n, m ;
  cin >> n ;
  m = n - 1;
  ++n;
  v.resize(n);
  vis.resize(n, false);
  int a, b;
  vector<double> ans(n, (double)0.0);
  queue<pair<int, double>> q;
  ff(i, 0, m){
    cin >> a >> b ;
    v[a].pb(b);
  }
  q.push({1, (double)1.0});

  while(!q.empty()){
    int u = q.front().f;
    double p = q.front().s;
    // cout << u << " --> " << p << "\n";
    q.pop();
    if(vis[u])
      continue;
    vis[u] = 1 ;
    if(u == 1 && !sz(v[1])){
      ans[1] = p;
      continue;
    }

    int k = sz(v[u]) ;
    if(!k) {
      ans[u] = p ;
      continue;
    }
    double np = double((1.0 * p) / (1.0 * k));
  
    for(auto x : v[u]){
      if(vis[x])
        continue;
      q.push({x, np});
    }
  }
  ff(i, 1, n) cout << fixed << setprecision(10) <<  ans[i] << " ";
}
int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  grassHopperandTree();
}

