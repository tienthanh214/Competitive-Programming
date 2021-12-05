#include <bits/stdc++.h>

using namespace std;

#define long long long

const int N = 1e5 + 10;

int n, q;
int p[N], d[N], max_depth[N], max_depth_parent[N];
int child[N];

vector<int> adj[N];
vector<int> V[N];

set<pair<int, int>> SET[N];

void DFS(int u) {
  max_depth[u] = d[u];
  for (int v: adj[u]) if (v != p[u]) {
    p[v] = u;
    d[v] = d[u] + 1;
    child[u]++;
    DFS(v);
    max_depth[u] = max(max_depth[u], max_depth[v]);
    V[u].push_back(max_depth[v] - d[u]);
    SET[u].insert({max_depth[v] - d[u], v});
  }
}

void Compute(int u, int max_parent) {
  // compute max_depth_parent for u
  if (SET[p[u]].size()) {
    // have children
    max_depth_parent[u] = max(SET[p[u]].rbegin() -> first, max_parent) + 1;
  } else {
    max_depth_parent[u] = max_parent + 1;
  }
  for (int v: adj[u]) if (v != p[u]) {
    SET[u].erase({max_depth[v] - d[u], v});
    Compute(v, max(max_parent, max_depth_parent[u]));
    SET[u].insert({max_depth[v] - d[u], v});
  }
}

void Solve() {
  for (int i = 1; i <= n; ++i) {
    sort(V[i].begin(), V[i].end());
  }
  while (q--) {
    int x, t; cin >> x >> t;
    int total_ans = child[x] + 1;
    if (max(d[x], max_depth_parent[x]) <= t) --total_ans; // parent --> x
    int p = upper_bound(V[x].begin(), V[x].end(), t) - V[x].begin();
    total_ans -= (p - 1 + 1);
    cout << total_ans << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  cin >> n >> q;
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  DFS(1);
  Compute(1, -1);
  Solve();

  return 0;
}