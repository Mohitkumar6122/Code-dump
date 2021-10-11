// CSES DP SOLTUIONS 

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

void print(vector<vector<int>> dp)
{
  for (auto x : dp)
  {
    for (auto c : x)
      cout << c << " ";
    cout << "\n";
  }
}

ll rodCut(vl &v, ll n)
{
  vl dp(n + 1, 0);
  ll maxVal = INT_MIN;
  for (int i = 1; i <= n; ++i)
  {
    maxVal = INT_MIN;
    for (int j = 0; j < i; ++j)
    {
      maxVal = max(maxVal, v[j] + dp[i - j - 1]);
    }
    dp[i] = maxVal;
  }
  return dp[n];
}

ll findMinSum(vl v, ll n)
{
  ll sum = accumulate(all(v), 0);
  vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
  ffd(i, 0, n) dp[i][0] = true;
  ffd(i, 1, n)
  {
    ffd(j, 1, sum)
    {
      dp[i][j] = dp[i - 1][j];
      if (j >= v[i - 1])
        dp[i][j] = dp[i][j] || dp[i - 1][j - v[i - 1]];
    }
  }
  ll diff = INT_MAX;
  for (int i = sum / 2; i >= 0; --i)
  {
    if (dp[n][i])
    {
      return sum - 2 * i;
    }
  }
  return INT_MAX;
}

ll maxIncreasingSubsequenceSum(vl &v, ll n)
{
  vl dp(n + 1, 0);
  ll ans = 0;
  ff(i, 0, n)
  {
    ff(j, 0, i)
    {
      if (v[i] > v[j] && dp[i] < dp[j] + v[i])
        dp[i] = dp[j] + v[i];
    }
    ans = max(ans, dp[i]);
  }
  return ans;
}

ll coinCombinationsI(vl &v, ll n, ll targetSum)
{
  vl dp(targetSum + 1, 0);
  dp[0] = 1;
  for (int i = 0; i <= targetSum; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      if (v[j] <= i)
      {
        dp[i] += dp[i - v[j]];
        dp[i] %= mod;
      }
    }
  }
  // for(auto x : dp)
  //   cout << x << " ";
  return dp[targetSum];
}

ll maxProductSubsequence(vl &v, ll n)
{
  vl dp = v;
  ll ans = INT_MIN;
  ff(i, 0, n)
  {
    ff(j, 0, i)
    {
      if (v[i] > v[j] && dp[i] < dp[j] * v[i])
        dp[i] = dp[j] * v[i];
    }
    ans = max(ans, dp[i]);
  }
  // for(auto x : dp)
  //   cout << x << " ";
  // cout << "\n";
  return ans;
}
void gridPaths(ll n)
{
  vector<vector<char>> v(n, vector<char>(n));
  vector<vector<int>> dp(n, vector<int>(n, 0));
  ff(i, 0, n)
  {
    ff(j, 0, n) cin >> v[i][j];
  }
  if (v[0][0] == '*' || v[n - 1][n - 1] == '*')
  {
    cout << "0";
    return;
  }
  ll i = 0;
  while (i < n && v[i][0] != '*')
    dp[i++][0] = 1;
  i = 0;
  while (i < n && v[0][i] != '*')
    dp[0][i++] = 1;

  for (int i = 1; i < n; ++i)
  {
    for (int j = 1; j < n; ++j)
    {
      if (v[i][j] != '*')
      {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        dp[i][j] %= mod;
      }
    }
  }
  cout << dp[n - 1][n - 1];
  return;
}

void bookshop()
{
  int n, k;
  cin >> n >> k;

  vector<int> pages(n), price(n);
  vector<vector<int>> dp(n, vector<int>(k + 1, 0));

  ff(i, 0, n) cin >> price[i];
  ff(i, 0, n) cin >> pages[i];

  ff(i, 0, n)
  {
    ffd(j, 0, k)
    {
      if (!j)
        continue;
      dp[i][j] = i ? dp[i - 1][j] : 0;
      if (price[i] <= j)
      {
        int a = i ? dp[i - 1][j - price[i]] : 0;
        dp[i][j] = max(dp[i][j], a + pages[i]);
      }
    }
  }
  cout << dp[n - 1][k];
}

void arrayDescription()
{
  int n, m;
  cin >> n >> m;
  vl v(n);
  ff(i, 0, n) cin >> v[i];
  vector<vector<int>> dp(n + 2, vector<int>(m + 2, 0));
  int ans = 0;

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= m; ++j)
    {
      if (i == 1)
      {
        dp[i][j] = (!v[i - 1] || j == v[i - 1]);
      }
      else if (v[i - 1] && v[i - 1] != j)
        dp[i][j] = 0;
      else
      {
        dp[i][j] = ((dp[i - 1][j] + dp[i - 1][j + 1]) % mod + dp[i - 1][j - 1]) % mod;
      }
      if (i == n)
        ans += dp[i][j], ans %= mod;
    }
  }
  cout << ans << "\n";
}
void countingStairs()
{
  vector<vector<ll>> dp(1e6 + 5, vl(2, 0));
  // transition:
  //              _  _    _  _    _  _    _  _     _ _
  //  _  _       | || |  |_|| |  | ||_|  |_||_|   |_ _|
  // | || | =>   | || |, | || |, | || |, | || |,  | | |
  //              _ _    _ _    _ _
  //  _ _        |   |  |_|_|  |_ _|
  // |   |  =>   |   |, |   |, |   |
  dp[1][0] = dp[1][1] = 1;
  ffd(i, 2, 1e6 + 2)
  {
    dp[i][0] = ((dp[i - 1][0] * 4) % mod + dp[i - 1][1]);
    dp[i][1] = ((dp[i - 1][1] * 2) % mod + dp[i - 1][0]);
    dp[i][0] %= mod;
    dp[i][1] %= mod;
  }
  int t, n;
  cin >> t;
  while (t--)
  {
    cin >> n;
    // countingStairs(dp, n);
    cout << (dp[n][0] + dp[n][1]) % mod << "\n";
  }
}

void editDistance()
{
  string s, t;
  cin >> s >> t;
  int n = s.size(), m = t.size();

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (int i = 0; i <= n; ++i)
  {
    for (int j = 0; j <= m; ++j)
    {
      if (!i)
        dp[i][j] = j;
      else if (!j)
        dp[i][j] = i;
      else if (s[i - 1] == t[j - 1])
      {
        dp[i][j] = dp[i - 1][j - 1];
      }
      else
      {
        dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
      }
    }
  }
  cout << dp[n][m];
}

void rectangleCutting()
{
  int a, b;
  cin >> a >> b;
  vector<vector<int>> dp(a + 1, vector<int>(b + 1, 0));

  for (int height = 1; height <= a; ++height)
  {
    for (int width = 1; width <= b; ++width)
    {
      if (height == width)
        dp[height][width] = 0;
      else
      {
        int mn = INT_MAX;
        for (int i = 1; i < width; ++i)
          mn = min(mn, 1 + dp[height][i] + dp[height][width - i]);
        for (int i = 1; i < height; ++i)
          mn = min(mn, 1 + dp[i][width] + dp[height - i][width]);
        dp[height][width] = mn;
      }
    }
  }
  // printdp(dp);
  cout << dp[a][b];
}
void moneySums()
{
  int n;
  cin >> n;
  vector<int> v(n);
  int sum = 0;
  int cnt = 0;

  ff(i, 0, n) cin >> v[i], sum += v[i];
  vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

  for (int i = 0; i <= n; ++i)
    dp[i][0] = true;

  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= sum; ++j)
    {
      dp[i][j] = dp[i - 1][j];
      if (v[i - 1] <= j)
        dp[i][j] = dp[i][j] || dp[i - 1][j - v[i - 1]];
      if (i == n && dp[i][j])
        ++cnt;
    }
  }
  cout << cnt << "\n";
  for (int i = 1; i <= sum; ++i)
    if (dp[n][i])
      cout << i << " ";
}
vector<vl> memo(5005, vector<ll>(5005, -1));

ll removalGame(vl &v, ll i, ll j)
{
  if (i > j)
    return 0;
  if (memo[i][j] != -1)
    return memo[i][j];
  // if (i == j)
  //   return v[i];
  // if (j - i == 1)
  //   return max(v[i], v[j]);
  ll a = (v[i] + min(removalGame(v, i + 1, j - 1), removalGame(v, i + 2, j)));
  ll b = (v[j] + min(removalGame(v, i, j - 2), removalGame(v, i + 1, j - 1)));
  return memo[i][j] = max(a, b);
}

void twoSetsII()
{
  ll n;
  cin >> n;
  int sum = (n * (n + 1)) / 2;
  if (sum & 1)
  {
    cout << "0";
    return;
  }
  sum >>= 1;
  vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
  // for (int i = 0; i < n; ++i)
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i)
  {
    for (int j = 1; j <= sum; ++j)
    {
      dp[i][j] = dp[i - 1][j];
      if (i <= j)
        dp[i][j] += dp[i - 1][j - i];
      dp[i][j] %= mod;
    }
  }
  // print(dp);
  cout << dp[n][sum];
}

void longestIncreasingSubsq()
{
  ll n;
  cin >> n;
  vl v(n), dp;
  ff(i, 0, n) cin >> v[i];
  ff(i, 0, n)
  {
    auto it = lb(all(dp), v[i]) - dp.begin();
    // cout << it << " <--  " << sz(dp) << "\n";

    //if it is the greatest element push it
    if (it == sz(dp))
      dp.pb(v[i]);
    else
      // place it in its sorted position
      dp[it] = v[i];
  }

  // this is not a valid subsequence but its length is the answer
  cout << sz(dp) << "\n";
}

//@ This method prints LIS in O(N log(N)) Time 
void printlongestIncreasingSubs(){
  ll n;
  cin >> n ;
  vl v(n);
  ff(i, 0, n) cin >> v[i];
  vl idx(n + 1, 0), parent(n + 1, -1);
  ll len = 1;

  // lambda function to find index of element using bs
  auto index = [&](ll x)
  {
    ll l = 0, r = len;
    while(l < r){
      ll mid = l + (r - l) / 2;
      if (v[idx[mid]] >= x)
        r = mid;
      else
        l = mid + 1;
    }
    return l;
  };

  ff(i, 1, n)
  {
    // if this is the smallest elem insert  it into beginning of idx
    if (v[i] < v[idx[0]]){
      // change the first elemnt idx of LIS
      // we dont change parent as parent array is initilaized with -1
      idx[0] = i;
    }
    // if this is the larget element in LCS
    else if (v[i] > v[idx[len - 1]]){
      // this element points to the previous last elemtn in LCS just lesser than it.
      parent[i] = idx[len - 1];
      // insert into index array and increase length of LIS
      idx[len++] = i;
    }
    // else find the lower bound of this element in current lcs bucket array 
    else {
      ll pos = index(v[i]);
      // change parent of current with its previous element
      parent[i] = pos ? idx[pos - 1] : -1;
      idx[pos] = i; 
    }
  }
  
  // prints the LIS in reverse order
  cout << "Length of LIS is : " << len << "\n";
  ll i = idx[len - 1];
  while(i != -1){
    cout << v[i] << " ";
    i = parent[i];
  }
}

// ! for projects function
struct interval{
  ll start, end, profit;
};

bool comp(const interval & a, const interval & b){
  return a.end < b.end;
}

void projects() {
  ll n, a, b, p;
  cin >> n;
  vector<interval> v;
  for (int i = 0; i < n; ++i){
    cin >> a >> b >> p;
    v.pb({a, b, p});
  }
  sort(all(v), comp);
  vl dp(n, 0);
  dp[0] = v[0].profit;
  for (int i = 1; i < n; ++i){
    ll incl = v[i].profit;
    ll l = 0, r = i - 1, x = v[i].start;

    ll pos = -1;
    while(l <= r){
      ll m = l + (r - l) / 2;
      if (v[m].end < x){
        pos = m;
        l = m + 1;
      }
      else
        r = m - 1;
    }
    if (pos != -1)
      incl += dp[pos];
    dp[i] = max(dp[i - 1], incl);
  }
  cout << dp[n - 1];
}

void elevatorRides(){
  int n, k;
  cin >> n >> k;
  int a[n];
  for (int i = 0; i < n; i++)
    cin >> a[i];
  pair<int, int> dp[1 << n];
  dp[0] = {0, k + 1};
  for (int s = 1; s < (1 << n); s++)
  {
    dp[s] = {25, 0};
    for (int i = 0; i < n; i++)
    {
      if (s >> i & 1)
      {
        auto c = dp[s ^ (1 << i)].f, w = dp[s ^ (1 << i)].s;
        if (w + a[i] > k)
        {
          c++;
          w = min(a[i], w);
        }
        else
          w += a[i];
        dp[s] = min(dp[s], {c, w});
      }
    }
  }
  cout << dp[(1 << n) - 1].first;
}

int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  elevatorRides();
  return 0;
}
