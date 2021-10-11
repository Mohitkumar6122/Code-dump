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

//!INTERVAL TREE IN CPP 
struct interval {
  int low, high;
};
interval non = {-1, -1};

struct Node{
  interval i;
  int max;
  Node *left = nullptr, *right = nullptr;
  Node (interval it){
    this->i = it;
    this->max = it.high;
  }
};

Node * insert(Node * root, interval it){
  if (!root)
    return new Node(it);
  if (root-> i.low > it.low){
    root->left = insert(root->left, it);
  }
  else
    root->right = insert(root->right, it);
  if (root ->max < it.high)
    root->max = it.high;
  return root;

}

bool overlap(interval i1, interval i2){
  return (i1.low <= i2.high and i2.low <= i1.high); 
}

interval search(Node * root, interval i){
  if (!root)
    return {-1, -1};
  
  if (overlap((root->i), i))
    return root->i;
  if (root -> left and root -> left->max >= i.low)
    return search(root->left, i);
  return search(root->right, i);
}

void inorder(Node * root){
  if (!root )
    return ;
  inorder(root->left);
  cout << "[" << root->i.low << ", " << root->i.high << "]" << " max = " << root->max << endl;
  inorder(root->right);
}

int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  ll t, q, n, a, b, c, d, k, l, m, r, x = 0, y = 0, z = 0, sum = 0, ans = 0, temp = 0, res = 0;
  interval v[] = {{15, 20}, {10, 30}, {17, 19},
           {5, 20}, {12, 15}, {30, 40}};
  n = 6;
  Node *root = nullptr;
  ff(i, 0, n){
    root = insert(root, v[i]);
  }
  inorder(root);
  interval it = {6, 7};
  interval  rs = search(root, it);
  if (rs.low == -1 and rs.high == -1 )
    cout << "No intersection\n";
  else
    cout << "Overlaps with " << rs.low << " " << rs.high;
  
}
