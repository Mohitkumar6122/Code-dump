// C++ implementation to find the
// minimum labelled node to be
// removed such that there is no
// cycle in the undirected graph

#include <bits/stdc++.h>

using namespace std;

const int MAX = 100005;

int totBackEdges;
int countAdj[MAX], small[MAX];

// Variables to store if a node V has
// at-most one back edge and store the
// depth of the node for the edge
int isPossible[MAX], depth[MAX];

vector<int> adj[MAX];
int vis[MAX];

// Function to swap the pairs of the graph
void change(pair<int, int>& p, int x)
{
	// If the second value is
	// greater than x
	if (p.second > x)
		p.second = x;

	// Put the pair in the ascending
	// order internally
	if (p.first > p.second)
		swap(p.first, p.second);
}

// Function to perform the DFS
pair<int, int> dfs(int v, int p = -1, int de = 0)
{
	// Initialise with the large value
	pair<int, int> answer(100000000, 100000000);

	// Storing the depth of this vertex
	depth[v] = de;

	// Mark the vertex as visited
	vis[v] = 1;
	isPossible[v] = 1;

	// Iterating through the graph
	for (int u : adj[v]) {

		// If the node is a child node
		if (u ^ p) {

			// If the child node is unvisited
			if (!vis[u]) {

				// Move to the child and increase
				// the depth
				auto x = dfs(u, v, de + 1);

				// increase according to algorithm
				small[v] += small[u];

				change(answer, x.second);
				change(answer, x.first);

				// If the node is not having
				// exactly K backedges
				if (x.second < de)
					isPossible[v] = 0;
			}

			// If the child is already visited
			// and in current dfs
			// (because colour is 1)
			// then this is a back edge
			else if (vis[u] == 1) {
				totBackEdges++;

				// Increase the countAdj values
				countAdj[v]++;
				countAdj[u]++;
				small[p]++;
				small[u]--;
				change(answer, depth[u]);
			}
		}
	}

	// Colour this vertex 2 as
	// we are exiting out of
	// dfs for this node
	vis[v] = 2;
	return answer;
}

// Function to find the minimum labelled
// node to be removed such that
// there is no cycle in the undirected graph
int minNodetoRemove(
	int n,
	vector<pair<int, int> > edges)
{

	// Construct the graph
	for (int i = 0; i < edges.size(); i++) {
		adj[edges[i].first]
			.push_back(edges[i].second);
		adj[edges[i].second]
			.push_back(edges[i].first);
	}

	// Mark visited as false for each node
	memset(vis, 0, sizeof(vis));

	totBackEdges = 0;

	// Apply dfs on all unmarked nodes
	for (int v = 1; v <= n; v++) {
		if (!vis[v])
			dfs(v);
	}

	// If no backedges in the initial graph
	// this means that there is no cycle
	// So, return -1
	if (totBackEdges == 0)
		return -1;

	int node = -1;

	// Iterate through the vertices and
	// return the first node that
	// satisfies the condition
	for (int v = 1; v <= n; v++) {

		// Check whether the count sum of
		// small[v] and count is the same as
		// the total back edges and
		// if the vertex v can be removed
		if (countAdj[v] + small[v]
				== totBackEdges
			&& isPossible[v]) {
			node = v;
		}
		if (node != -1)
			break;
	}

	return node;
}

// Driver code
int main()
{
	int N = 5;
	vector<pair<int, int> > edges;
	edges.push_back(make_pair(5, 1));
	edges.push_back(make_pair(5, 2));
	edges.push_back(make_pair(1, 2));
	edges.push_back(make_pair(2, 3));
	edges.push_back(make_pair(2, 4));

	cout << minNodetoRemove(N, edges);
}
