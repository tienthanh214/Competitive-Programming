#include <bits/stdc++.h>

using namespace std;

int n;
int a[55][55];

bool visited[55];
vector<int> g[55];
int match[55];

bool findMatch(int u) {
	if (visited[u]) return false;
  visited[u] = true;
  for (int v : g[u]) {
    if (!match[v] || findMatch(match[v])) {
      match[v] = u;
      return true;
    }
  }
  return false;
}

void buildGraph() {
	for (int i = 1; i <= n; ++i) {
  	match[i] = 0;
    g[i].clear();
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (a[i][j] != 0)
        g[j].push_back(i);
}

void run() {
  int ans = 0;
  vector<vector<int>> p;
  vector<int> X;
  while (true) {
    buildGraph();
    for (int i = 1; i <= n; ++i) {
      memset(visited, false, sizeof(visited));
      if (!findMatch(i)) {
        cout << ans << '\n';
        for (int j = 0; j < ans; ++j) {
            cout << X[j];
            for (int x : p[j]) cout << ' ' << x;
            cout << '\n';
        }
        return;
      }
    }
    ans += 1;
    int toAdd = -1;
    for (int i = 1; i <= n; ++i) {
      toAdd = min(toAdd == -1 ? (int)1e9 : toAdd, a[i][match[i]]);
    }
    // cout << toAdd << endl;
    vector<int> permut;
    for (int i = 1; i <= n; ++i) {
      a[i][match[i]] -= toAdd;
      permut.push_back(match[i]);
    }
    p.push_back(permut);
    X.push_back(toAdd);
  }
 
  
}

int main() {
  int TC; cin >> TC;
  while (TC-- > 0) {
    cin >> n;
    vector<long long> sum(n + 1, 0);
    for (int i = 1; i <= n; ++i) 
      for (int j = 1; j <= n; ++j) {
        cin >> a[i][j];
        sum[i] += a[i][j];
      }

    bool flag = true;
    for (int i = 1; i <= n; ++i)
      if (sum[i] != sum[1]) {
        cout << "-1" << "\n";
        flag = false;
        break;
      }
    if (flag) run();
  }
  return 0;
}