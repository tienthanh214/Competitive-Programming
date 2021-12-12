#include <bits/stdc++.h>

#define long long long

using namespace std;

const int N = 1e5 + 10;

struct DSU {
  int n;
  int p[N];
  void Init(int _n) {
    n = _n;
    for (int i = 1; i <= n; ++i) p[i] = -1;
  }

  int Root(int u) {
    return p[u] < 0 ? u : p[u] = Root(p[u]);
  }

  void Union(int u, int v) {
    u = Root(u); v = Root(v);
    if (u == v) return;
    if (p[u] > p[v]) swap(u, v);
    p[u] += p[v];
    p[v] = u;
  }
} DSU;

const int BASE = 1e9 + 7;

int main() {
  int n, m; cin >> n >> m;
  DSU.Init(n);
  for (int i = 1; i <= m; ++i) {
    int u, v; cin >> u >> v;
    ++u; ++v;
    DSU.Union(u, v);
  }
  vector<int> fact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = 1LL * fact[i - 1] * i % BASE;

  int ans = 0;
  for (int i = 1; i <= n; ++i) if (DSU.p[i] < 0) {
    int v = -DSU.p[i];
    if (v <= 2) continue;
    ans = (ans + fact[v]) % BASE;
  }
  cout << ans;

  return 0;
}
