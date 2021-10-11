// MOHIT KUMAR
#pragma GCC optimize("O3")
#pragma GCC target("sse4")

#include <bits/stdc++.h>
#include<chrono>
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

// MergeSort
// Time complexity O(n log n)
// Space Complexity O(n)
void merge(vl &v, ll l, ll m, ll r)
{
  int n1 = m - l + 1, n2 = r - m;
  vl left(n1), right(n2);
  ff(i, 0, n1) left[i] = v[l + i];
  ff(i, 0, n2) right[i] = v[m + 1 + i];

  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2)
  {
    if (left[i] <= right[j])
      v[k++] = left[i++];
    else
      v[k++] = right[j++];
  }
  while (i < n1)
    v[k++] = left[i++];
  while (j < n2)
    v[k++] = right[j++];
}
void mergeSort(vl & v, ll l, ll r){
  if (l < r){
    int m = l + ((r - l) >> 1);
    mergeSort(v, l, m);
    mergeSort(v, m + 1, r);
    merge(v, l, m, r);
  }
  return;
}

// Quick Sort 
// Time complexity O(n log n)
// Space Complexity O(log n) due to recursive stack 
int partititonIndex(vl & v, ll l, ll n){
  int last = v[n];
  int i = l - 1;
  ff(j, l, n){
    if (v[j] < last){
      ++i;
      swap(v[i], v[j]);
    }
  }
  swap(v[i + 1], v[n]);
  return i + 1;
}
void quickSort(vl & v, ll l, ll r){
  if (l < r){
    int m = partititonIndex(v, l, r);
    quickSort(v, l, m - 1);
    quickSort(v, m + 1, r);
  }
}

// Heap Sort
// Time Complexity O(n logn)
// Space COmplexity O(1)
void heapify(vl & v, ll i, ll n){
  ll largest = i;
  ll left = (i << 1) + 1;
  ll right = (i << 1) + 2;

  if (left < n && v[left] > v[largest])
    largest = left;

  if (right < n && v[right] > v[largest])
    largest = right;

  if (largest != i){
    swap(v[largest], v[i]);
    heapify(v, largest, n);
  }
}

void heapSort(vl & v, ll n) {
  ll idx = (n - 2) / 2;
  for (int i = idx; i >= 0; --i){
    heapify(v, i, n);
  }

  for (int i = n - 1; i > 0; --i){
    swap(v[0], v[i]);
    heapify(v, 0, i);
  }
}

// Bubble Sort 
// Time Complexity O(n^2)
// Space Complexity O(1)
void bubbleSort(vl & v, ll n){
  bool isSorted ;

  for (int i = 0; i < n; ++i){
    isSorted = false;
    for (int j = 0; j < n - i - 1; ++j){
      if (v[j] > v[j + 1]) {
        isSorted = true;
        swap(v[j], v[j + 1]);
      }
    }
    if (!isSorted)
      break;
  }
}

// Selection Sort
// Time Complexity O(n^2)
// Space Complexity O(1)
void selectionSort(vl & v, ll n){
  for (int i = 0; i < n; ++i){
    int minIndex = i;
    for (int j = i + 1; j < n; ++j){
      if (v[j] < v[minIndex])
        minIndex = j;
    }
    swap(v[minIndex], v[i]);
  }
}

// Insertion Sort
// Time Complexity O(n^2)
// Space Complexity O(1)
void insertionSort(vl & v, ll n){
  for (int i = 0; i < n; ++i){
    int idx = i - 1, key = v[i];
    while(idx >= 0 && v[idx] > key){
      v[idx + 1] = v[idx];
      --idx;
    }
    v[idx + 1] = key;
  }
}

int main()
{
  ios_base::sync_with_stdio(0), cin.tie(0);
  vl v = {5,6,4,3,2,1,4,5,6,7,8,89,6,5,4,2,2,3,5,4,6,76,45} ;
  ll n = sz(v);
  insertionSort(v, n);
  for (auto x: v)
    cout << x << " ";
}
