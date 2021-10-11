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

struct Node
{
  int data;
  struct Node *left = nullptr, *right = nullptr;
  Node(int val)
  {
    this->data = val;
  }
};

Node *newNode(int val)
{
  Node *temp = new Node(val);
  temp->data = val;
  temp->left = nullptr;
  temp->right = nullptr;

  return temp;
};

void inorder(Node *root)
{
  if (!root)
    return;
  inorder(root->left);
  cout << root->data << " ";
  // v.pb(root->data);
  inorder(root->right);
}

int find(string s, int start, int end)
{
  if (end < start)
    return -1;
  stack<char> st;
  for (int i = start; i <= end; ++i)
  {
    if (s[i] == '(')
      st.push('(');
    else if (s[i] == ')')
    {
      if (st.top() == '(')
      {
        st.pop();
        if (st.empty())
          return i;
      }
    }
  }
  return -1;
}

Node *solve(string s, int start, int end)
{
  if (start > end)
    return nullptr;
  Node *temp = new Node(s[start] - '0');
  int index = -1;
  if (start + 1 <= end and s[start + 1] == '(')
    index = find(s, start + 1, end);
  // cout << index << "\n";
  if (index != -1)
  {
    temp->left = solve(s, start + 2, index - 1);
    temp->right = solve(s, index + 2, end - 1);
  }
  return temp;
}

// swaps needed to sort bst 
ll solve(vl &v, ll n)
{
  vl vc = v;
  ll ans = 0;
  sort(all(vc));
  bool vis[n];
  memset(vis, 0, sizeof(vis));
  unordered_map<ll, ll> ma;
  ff(i, 0, n) ma[vc[i]] = i;
  ff(i, 0, n)
  {
    if (vis[i] or v[i] == vc[i])
      vis[i] = 1;
    else
    {
      ll cnt = 0, ind = i;
      while (v[ind] != vc[i])
      {
        ++cnt;
        vis[ind] = 1;
        ind = ma[v[ind]];
      }
      if (cnt > 1)
        ans += --cnt;
    }
  }
  return ans;
}

ll sumtree(Node * root)
{
  if (!root)
    return 0;
  root->data += sumtree(root->left) +  sumtree(root->right);
  return root->data;
}

pl in(Node * root)
{
  if (!root)
    return {0, 0};
  pl a = in(root->left);
  pl b = in(root->right);
  pl res;
  res.first = root->data + a.second + b.second ;
  res.second = max(a.first, a.second) + max(b.first, b.second);
  return res;
}

void qsolve(Node * root){
  static int l = 0;
  if (!root )
    return;
  cout << " static " << l << " \n";
  ++l;
  qsolve(root->left);
  qsolve(root->right);
}

Node * solve(vl v, ll l, ll r){
  if (l > r or l < 0 or r < 0)
    return nullptr;
  if (l == r)
    return new Node(v[l]);
  ll val = v[l], m;
  m = ub(all(v), val) - v.begin();
  cout << l << " " << m << " " << r << "\n";
  Node *root = new Node(val);
  root->left = solve(v, l + 1, m - 1);
  root->right = solve(v, m, r);
  return root;
}

void inorder(Node * root, vl & v){
  if (!root)
    return;
  inorder(root->left, v);
  v.pb(root->data);
  inorder(root->right, v);
}

vl merge(vl & left, vl & right){
  ll l = 0, r = 0, k = 0, n1 = sz(left), n2 = sz(right);
  vl v(n1 + n2);
  while(l < n1 and r < n2){
    if (left[l] <= right[r])
      v[k++] = left[l++];
    else
      v[k++] = right[r++];
  }
  while(l < n1)
    v[k++] = left[l++];
  while(r < n2)
    v[k++] = right[r++];
  return v;
}
Node * makebst(vl v, int l, int r){
  if (l > r)
    return nullptr;
  if (l == r)
    return new Node(v[l]);
  int m = l + (r - l) / 2;
  Node *root = new Node(v[m]);
  root->left = makebst(v, l, m - 1);
  root->right = makebst(v, m + 1, r);
  return root;
}

void cnt(Node * root, ll & ans){
  /*
    @param : root node and ans-> count of current nodes (passed by reference)
    @return : void (as count is passsed by reference).
  */
  if(!root)
    return;
  ++ans;
  cnt(root -> left, ans) ;
  cnt(root->right, ans);
}

void medianNode(Node * root, ll ans, ll & cnt, ll & first){
  if (!root)
    return;
  medianNode(root->left, ans, cnt, first);
  cout << root->data << " " << ans << " " << cnt <<  " " << first << "\n";
  if (!cnt) {
    cout << "Median Node is ";
    cout << ( ans & 1 ? root -> data : (root -> data + first) / 2.0) << "\n";
    return;
  }
  
  if (ans % 2 == 0 and cnt == 1)
    first = root->data;
  --cnt;
  medianNode(root->right, ans, cnt, first);
}
int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  ll t, q, n, a, b, c, d, k, l, m, r, x = 0, y = 0, z = 0, sum = 0, ans = 0, temp = 0, res = 0;
  Node *root = new Node(100);
  root->left = new Node(50);
  root->right = new Node(150);
  root->left->left = new Node(20);
  root->left->right = new Node(70);
  root->right->left = new Node(120);
  // root->right->right = new Node(200);

  // qsolve(root);
  Node *root1 = new Node(1);
  root1->right = new Node(2);
  ans = 0; // Gives count of nodes in bst
  cnt(root1, ans);
  if(ans & 1)
    res = (ans + 1) / 2;
  else
    res = 1 + (ans / 2);
  --res;
  cout << ans << " " << res << "\n";
  medianNode(root1, ans, res, temp); 
}
