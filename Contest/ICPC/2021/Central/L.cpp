#include <bits/stdc++.h>

#define long long long

using namespace std;

const int INF = 1e9 + 10;
const int N = 4e5 + 10;
const int LG = 20;

int L[N], R[N];
int n, q, timer = 0;
int a[N], x[N], y[N], V[N], head[N], sz[N], h[N];
int p[N][LG + 2], fL[N][LG + 2], fR[N][LG + 2];

struct RMQ {
  int n;
  int lg[N];
  int spT[N][LG];
  void Init(int _n) {
    n = _n;
    for (int i = 1; i <= n; ++i) spT[i][0] = i;
    for (int i = 0; 1 << i <= n; ++i) lg[1 << i] = i;
    for (int i = 1; i <= n; ++i) if (!lg[i]) lg[i] = lg[i - 1];
    for (int j = 1; 1 << j <= n; ++j)
      for (int i = 1; i <= n; ++i) {
        int x = spT[i][j - 1];
        int y = spT[i + (1 << (j - 1))][j - 1];
        int ux = V[x];
        int uy = V[y];
        if (a[ux] > a[uy]) spT[i][j] = x;
        else spT[i][j] = y;
      }
  }
  
  int Query(int l, int r) {
    int k = lg[r - l + 1];
    int x = spT[l][k];
    int y = spT[r - (1 << k) + 1][k];
    int ux = V[x];
    int uy = V[y];
    if (a[ux] > a[uy]) return x;
    return y;
  }
} RMQ;

vector<int> adj[N], child[N];

void DFS(int u) {
  sz[u] = 1;
  for (auto v: adj[u]) {
    if (v == p[u][0]) continue;
    h[v] = h[u] + 1; p[v][0] = u;
    child[u].push_back(v);
    DFS(v);
    sz[u] += sz[v];
  }
}

void HLD(int u) {
  x[u] = ++timer; V[timer] = u;
  for (int i = 1; i < child[u].size(); ++i) {
    if (sz[child[u][i]] > sz[child[u][0]]) {
      swap(child[u][i], child[u][0]);
    }
  }
  for (int i = 0; i < child[u].size(); ++i) {
    int v = child[u][i];
    head[v] = (i == 0 ? head[u] : v);
    HLD(v);
  }
  y[u] = timer;
}

void InitLCA() {
  for (int j = 1; 1 << j <= n; ++j)
    for (int i = 1; i <= n; ++i) p[i][j] = p[p[i][j - 1]][j - 1];
}

int LCA(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  for (int i = LG; i >= 0; --i) if (h[u] - (1 << i) >= h[v]) u = p[u][i];
  if (u == v) return u;
  for (int i = LG; i >= 0; --i) if (p[u][i] != p[v][i]) u = p[u][i], v = p[v][i];
  return p[u][0];
}

void HLDQuery(int a, int u, vector<pair<int, int>> &segs) {
  int v = u;
  while (true) {
    if (head[a] == head[v]) {
      // [x[a], x[v]]
      segs.push_back({x[a], x[v]});
      break;
    }
    int w = head[v];
    segs.push_back({x[w], x[v]});
    v = p[w][0];
  }
}

pair<int, int> ComputeRevInSeg(int lastPosition, int l, int r) {
  pair<int, int> ans;
  ans.first = 1;
  for (int i = LG; i >= 0; --i) 
    if (l <= fL[lastPosition][i] && fL[lastPosition][i] <= r) {
      ans.first += (1 << i);
      lastPosition = fL[lastPosition][i];
    }
  ans.second = lastPosition;
  return ans;
}

int JumpLeft(int lastPosition, int x, int y) {
  int l = x, r = y, f = -1;
  int val = a[V[lastPosition]];
  if (a[V[RMQ.Query(x, y)]] <= a[V[lastPosition]]) return -1;
  while (l <= r) {
    int m = (l + r) >> 1;
    if (a[V[RMQ.Query(m, y)]] > val) {
      f = m;
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return f;
}

pair<int, int> ComputeRev(const vector<pair<int, int>> &segs) {
  int lastPosition = segs[0].second;
  int ans = 0;
  auto in_segment = ComputeRevInSeg(lastPosition, segs[0].first, segs[0].second);
  ans += in_segment.first;
  lastPosition = in_segment.second;

  for (int i = 1; i < segs.size(); ++i) {
    const auto &[l, r] = segs[i];
    int leftPos = JumpLeft(lastPosition, l, r);
    if (leftPos == -1) {
      continue;
    } else {
      lastPosition = leftPos;
    }

    auto in_segment = ComputeRevInSeg(lastPosition, l, r);
    ans += in_segment.first;
    lastPosition = in_segment.second;
  }
  return {ans, lastPosition};
}

pair<int, int> ComputeNxtInSeg(int lastPosition, int l, int r) {
  pair<int, int> ans;
  ans.first = 1;
  for (int i = LG; i >= 0; --i) if (l <= fR[lastPosition][i] && fR[lastPosition][i] <= r) {
    ans.first += (1 << i);
    lastPosition = fR[lastPosition][i];
  }
  ans.second = lastPosition;
  return ans;
}

int JumpRight(int lastPosition, int x, int y) {
  int val = a[V[lastPosition]];
  if (a[V[RMQ.Query(x, y)]] <= val) return -1;
  int l = x, r = y, f = -1;
  while (l <= r) {
    int m = (l + r) >> 1;
    if (a[V[RMQ.Query(x, m)]] > val) {
      f = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }
  return f;
}

pair<int, int> ComputeNxt(const vector<pair<int, int>> &segs, int lastPosition) {
  int ans = 0;
  for (int i = 0; i < segs.size(); ++i) {
    const auto &[l, r] = segs[i];

    int rightPos = JumpRight(lastPosition, l, r);
    // cout << l << " " << r << ": " << lastPosition << " " << rightPos << '\n';
    if (rightPos == -1) {
      continue;
    } else {
      lastPosition = rightPos;
    }
    auto in_segment = ComputeNxtInSeg(lastPosition, l, r);
    ans += in_segment.first;
    lastPosition = in_segment.second;
  }
  return {ans, lastPosition};
}

int Query(int s, int t) {
  int w = LCA(s, t);
  // query from s --> w
  vector<pair<int, int>> rev_segs;
  HLDQuery(w, s, rev_segs);
  
  auto rev_ans = ComputeRev(rev_segs);
  // cout << "Rev ans: " << rev_ans.first << " " << rev_ans.second << '\n';

  vector<pair<int, int>> segs;
  // query from w --> t
  HLDQuery(w, t, segs);
  reverse(segs.begin(), segs.end());
  auto nxt_ans = ComputeNxt(segs, rev_ans.second);
  // cout << "Nxt ans: " << nxt_ans.first << " " << nxt_ans.second << '\n';

  // cout << "Query: " << s << " " << t << ": " << rev_ans.first + nxt_ans.first << '\n';

  return rev_ans.first + nxt_ans.first;
}


void Prep() {
  // R[i] is the next timer that a[V[timer]] > a[V[i]]
  // L[i] is the previous timer that a[V[timer]] > a[V[i]]
  vector<int> rar;
  for (int i = 1; i <= n; ++i) rar.push_back(a[i]);
  sort(rar.begin(), rar.end());
  rar.resize(unique(rar.begin(), rar.end()) - rar.begin());
  auto Pos = [&](int v) {
    return lower_bound(rar.begin(), rar.end(), v) - rar.begin() + 1; // 1-indexed
  };
  vector<int> fw(rar.size() + 2, INF);
  auto update = [&](int i, int v, bool mx) {
    for (i; i > 0; i -= i & -i) {
      if (mx) fw[i] = max(fw[i], v);
      else fw[i] = min(fw[i], v);
    }
  };
  auto query = [&](int i, bool mx) {
    int ans = mx == true ? -INF : INF;
    for (i; i <= rar.size(); i += i & -i) 
      if (mx) ans = max(ans, fw[i]);
      else ans = min(ans, fw[i]);
    return ans;
  };
  for (int i = n; i >= 1; --i) {
    int u = V[i];
    int v = Pos(a[u]);
    int q = query(v + 1, false);
    R[i] = (q == INF ? n + 1 : q);
    update(v, i, false);
  }

  fw.assign(rar.size() + 2, -INF);
  for (int i = 1; i <= n; ++i) {
    int u = V[i];
    int v = Pos(a[u]);
    int q = query(v + 1, true);
    L[i] = (q == -INF ? 0 : q);
    update(v, i, true);
  }
  // cout << "L: ";
  // for (int i = 1; i <= n; ++i) cout << L[i] << ' '; cout << '\n';
  // cout << "R: ";
  // for (int i = 1; i <= n; ++i) cout << R[i] << ' '; cout << '\n';

  for (int i = 1; i <= n; ++i) {
    fL[i][0] = L[i];
    fR[i][0] = R[i];
  }
  for (int j = 1; 1 << j <= n; ++j) {
    for (int i = 1; i <= n; ++i) {
      fL[i][j] = fL[fL[i][j - 1]][j - 1];
      fR[i][j] = fR[fR[i][j - 1]][j - 1];
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);

  cin >> n >> q;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  DFS(1);
  HLD(1);
  InitLCA();
  Prep();
  RMQ.Init(n);
  // for (int i = 1; i <= n; ++i) cout << setw(1) << x[i] << ' '; cout << '\n';
  // for (int i = 1; i <= n; ++i) cout << setw(1) << V[x[i]] << ' '; cout << '\n';
  // for (int i = 1; i <= n; ++i) cout << setw(1) << a[V[x[i]]] << ' '; cout << '\n';
  int lastAns = 0;
  while (q--) {
    int u, v; cin >> u >> v;
    // cout << u << " " << v << '\n';
    u = (u + lastAns) % n + 1;
    v = (v + lastAns) % n + 1;
    lastAns = Query(u, v);
    cout << lastAns << '\n';
    // cout << "-------------\n";
  }

  return 0;
}
