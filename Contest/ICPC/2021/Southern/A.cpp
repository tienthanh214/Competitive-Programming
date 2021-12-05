#include <bits/stdc++.h>

using namespace std;

#define long long long

const int N = 2e2 + 10;

struct Edge {
  int u, v, cap, flow;
  Edge() {}
  Edge(int u, int v, int cap, int flow) : u(u), v(v), cap(cap), flow(flow) {}
  int remain() const {
    return cap - flow;
  }
};

struct MaxFlow {
  vector<int> d, ptr;
  vector<vector<int>> g;
  vector<Edge> e;
  int n, s, t;
  MaxFlow() {}
  MaxFlow(int _n) {
    n = _n;
    e.clear();
    d.resize(n);
    ptr.resize(n);
    g.resize(n);
    for (int i = 0; i < n; ++i) {
      d[i] = ptr[i] = 0;
      g[i].clear();
    }
  }

  void addEdge(int u, int v, int cap) {
    g[u].push_back(e.size());
    e.push_back(Edge(u, v, cap, 0));
    g[v].push_back(e.size());
    e.push_back(Edge(v, u, cap, 0));
  }

  int maxFlow(int _s, int _t) {
    s = _s;
    t = _t;
    int flow = 0;
    while (bfs()) {
      while (int x = dfs(s, 1e9)) {
        flow += x;
      }
    }
    return flow;
  }
 private:
  bool bfs() {
    queue<int> q;
    for (int i = 0; i < n; ++i) ptr[i] = 0, d[i] = -1;
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int id : g[u]) if (e[id].flow < e[id].cap) {
        int v = e[id].v;
        if (d[v] == -1) {
          d[v] = d[u] + 1;
          q.push(v);
        }
      }
    }
    return d[t] != -1;
  }

  int dfs(int u, int flow) {
    if (u == t) return flow;
    for (; ptr[u] < (int)g[u].size(); ++ptr[u]) {
      int id = g[u][ptr[u]];
      int v = e[id].v;
      if (d[v] == d[u] + 1 && e[id].cap > e[id].flow) {
        if (int x = dfs(v, min(flow, e[id].cap - e[id].flow))) {
          e[id].flow += x;
          e[id ^ 1].flow -= x;
          return x;
        }
      }
    }
    return 0;
  }
};

struct GomoryHuTree {
  vector<bool> vis;
  MaxFlow mf;

  void dfs(int u) {
    vis[u] = 1;
    for (int id: mf.g[u]) {
      int v = mf.e[id].v, c = mf.e[id].remain();
      if (c && !vis[v]) dfs(v);
    }
  }

  vector<pair<int, int>> Solve(int n, vector<Edge> &e) {
    vector<pair<int, int>> ret(n);
    mf = MaxFlow(n);
    vis.resize(n);
    for (const auto& edge: e) {
      mf.addEdge(edge.u, edge.v, edge.cap);
    }
    for (int i = 1; i < n; ++i) {
      // reset flow
      for (auto& edge : mf.e) edge.flow = 0;
      ret[i].second = mf.maxFlow(i, ret[i].first);
      for (int j = 0; j < n; ++j) vis[j] = 0;
      dfs(i);
      for (int j = i + 1; j < n; ++j) {
        if (ret[j].first == ret[i].first && vis[j]) ret[j].first = i;
      }
    }
    return ret;
  }
} gom;

vector<Edge> e;

int n;
int adj[N][N], ans[N][N];

struct DSU {
  int n;
  int p[N];
  vector<int> vertexes[N];
  void Init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i) {
      p[i] = -1;
      vertexes[i].clear();
      vertexes[i].push_back(i);
    }
  }
  int Root(int u) {
    return (p[u] < 0 ? u : p[u] = Root(p[u]));
  }
  void Union(int u, int v) {
    u = Root(u); v = Root(v);
    if (u == v) return;
    // Merge v to u
    for (int vertex: vertexes[v])
      vertexes[u].push_back(vertex);
    p[u] += p[v];
    p[v] = u;
  }
} DSU;

void Solve(int kTC) {
  cout << "Case #" << kTC << ":" << '\n';
  e.clear();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cin >> adj[i][j];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      e.push_back(Edge(i, j, adj[i][j], 0));
    }
  }
  auto ret = gom.Solve(n, e);
  // for (auto pp: ret) cout << pp.first << " " << pp.second << '\n';
  vector<Edge> tree_edge;
  assert(ret.size() == n);
  for (int i = 0; i < n; ++i) {
    int p = ret[i].first, w = ret[i].second;
    if (p != i)
      tree_edge.push_back(Edge(p, i, w, 0)); // reuse egde
  }
  sort(tree_edge.begin(), tree_edge.end(), [&](const auto &A, const auto &B) {
    return A.cap > B.cap;
  });
  DSU.Init(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) ans[i][j] = 0;
  }
  for (const auto &[u, v, w, f] : tree_edge) {
    // cout << "check: add edge " << u << " " << v << " with w: " << w << '\n';
    int ru = DSU.Root(u), rv = DSU.Root(v);
    if (ru == rv) continue; // same component
    // cout << "yes: add edge " << u << " " << v << " with w: " << w << '\n';
    for (const auto &u: DSU.vertexes[ru]) {
      for (const auto &v: DSU.vertexes[rv]) {
        // add edge (u, v) with weight w
        ans[u][v] = ans[v][u] = w;
      }
    }

    // Unite two components
    DSU.Union(u, v);
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) cout << ans[i][j] << " ";
    cout << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
  int TC; cin >> TC;
  int ptr = 0;
  while (TC--) {
    cin >> n;
    Solve(++ptr);
  }  

  return 0;
}