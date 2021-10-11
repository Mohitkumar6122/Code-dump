// Stack Implementation

#pragma GCC optimize("O3")
#pragma GCC target("sse4")

#include <bits/stdc++.h>
// for calculating time elapsed for each function
#include <chrono>
using namespace std::chrono;

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

const int mx = 100;

class Node
{
public:
  int data;
  Node *next = nullptr;
};

class StackUsingArray
{
private:
  int idx = -1;
  int v[mx];

public:
  StackUsingArray()
  {
    memset(v, -1, sizeof(v));
  }

  void push(int val)
  {
    try
    {
      if (idx >= mx)
      {
        throw string("StackUsingArray OverFlow :(\n");
      }
      v[++idx] = val;
    }
    catch (string s)
    {
      cout << s;
    }
  }

  int pop();
  bool isEmpty();
  int peek();
};

int StackUsingArray::pop()
{
  // cout << idx << " <--\n ";
  try
  {
    if (idx < 0)
    {
      throw string("StackUsingArray Underflow :(");
    }
    int temp = v[idx];
    v[idx--] = -1;
    return temp;
  }
  catch (string s)
  {
    cout << s;
  }
  return -1;
}

int StackUsingArray::peek()
{
  try
  {
    if (idx < 0)
    {
      throw string("StackUsingArray Underflow :(");
    }
    return v[idx];
  }
  catch (string s)
  {
    cout << s;
  }
  return -1;
}

bool StackUsingArray::isEmpty()
{
  // cout << idx << " <--\n";
  return idx == -1;
}

class StackUsingLL
{
private:
  Node *n;
  Node *root = nullptr;

public:
  void push(int val);
  int pop();
  int peek();
  bool isEmpty();
};

void StackUsingLL::push(int val)
{
  Node *newNode = new Node;
  newNode->data = val;
  newNode->next = root;
  root = newNode;
}

int StackUsingLL::peek()
{
  try
  {
    if (!root)
    {
      throw("UnderFlow Error\n");
    }
    return root->data;
  }
  catch (const char *s)
  {
    cout << s;
  }
  return -1;
}

int StackUsingLL::pop()
{
  try
  {
    if (!root)
    {
      throw("UnderFlow Error\n");
    }
    int val = root->data;
    root = root->next;
    return val;
  }
  catch (const char *s)
  {
    cout << s;
  }
  return -1;
}

bool StackUsingLL::isEmpty()
{
  // cout << (root ? "Fill" : "Empty") << "\n";
  return !root;
}

class Priorityq
{
  vector<int> heap;
  int maxCap, curCap;

public:
  Priorityq(){};
  Priorityq(int n)
  {
    heap.resize(n);
    maxCap = n;
    curCap = 0;
  };

  void push(int);
  void pop();
  int top();
  void balance(vector<int> &);
  void heapify(vector<int> &, int, int);
  friend void print(Priorityq &);
};
void Priorityq::push(int n)
{
  try
  {
    if (curCap >= maxCap)
    {
      throw string("Stack Overflow :( \n");
    }
    heap.push_back(n);
    ++curCap;
    balance(heap);
  }
  catch (const string s)
  {
    cout << s;
  }
}

void Priorityq::pop()
{
  try
  {
    if (curCap <= 0)
    {
      throw string("Stack Underflow :( \n");
    }
    heap.erase(heap.begin());
    --curCap;
    balance(heap);
  }
  catch (const string s)
  {
    cout << s;
  }
}

int Priorityq::top()
{
  try
  {
    if (curCap <= 0 || curCap > maxCap)
    {
      throw string("Stack error\n");
    }
    return heap.front();
  }
  catch (string s)
  {
    cout << s;
  }
  return -1;
}

void Priorityq::balance(vector<int> &heap)
{
  int n = heap.size();
  for (int i = n / 2 - 1; i >= 0; --i)
  {
    heapify(heap, i, n);
  }
}

void Priorityq::heapify(vector<int> &heap, int i, int n)
{
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int largest = i;

  if (l < n && heap[l] > heap[largest])
    largest = l;
  if (r < n && heap[r] > heap[largest])
    largest = r;

  if (largest != i)
  {
    swap(heap[largest], heap[i]);
    heapify(heap, largest, n);
  }
}

void print(Priorityq &pq)
{
  cout << "Printing Priority queue ";
  for (auto x : pq.heap)
    cout << x << " ";
  cout << "\n";
}

void heapify(vector<int> &v, int i, int n)
{
  int largest = i, l = (i << 1) + 1, r = (i << 1) + 2;

  if (l < n && v[l] > v[largest])
    largest = l;

  if (r < n && v[r] > v[largest])
    largest = r;

  if (largest != i)
  {
    swap(v[i], v[largest]);
    heapify(v, largest, n);
  }
}

void heapsort(vector<int> &v, int n)
{
  for (int i = n / 2 - 1; i >= 0; --i)
  {
    heapify(v, i, n);
  }
  for (int i = n - 1; i >= 0; --i)
  {
    swap(v[i], v[0]);
    heapify(v, 0, i);
  }
  for (auto x : v)
    cout << x << " ";
}

int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  Priorityq pq = Priorityq(5);
  pq.push(1);
  pq.push(2);
  pq.push(56);
  pq.push(234);
  pq.push(2334);
  pq.push(234);
  // pq.pop();
  print(pq);
  cout << pq.top();
  cout << "----------------------------------------------------------------\n";
  vector<int> v = {7, 234, 2, 34, 5, 2, 3, 768, 123, 234, 54, 23, 5, 2, 3, 23, 768, 567, 8, 3, 4, 67, 53, 45776, 87, 2345676, 6};
  heapsort(v, sz(v));
}
