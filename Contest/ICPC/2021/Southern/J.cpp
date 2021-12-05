#include <bits/stdc++.h>

using namespace std;

#define long long long

const int N = 5e3 + 10;

string s[N];

int n, m;
int L[N][N], R[N][N], U[N][N], D[N][N];

const int INF = 1e9;

int main() {
  ios_base::sync_with_stdio(false); cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> s[i];
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      L[i][j] = (s[i - 1][j - 1] == '0' ? 0 : L[i][j - 1] + 1);
      U[i][j] = (s[i - 1][j - 1] == '0' ? 0 : U[i - 1][j] + 1);
    }
    for (int j = m; j >= 1; --j) {
      R[i][j] = (s[i - 1][j - 1] == '0' ? 0 : R[i][j + 1] + 1);
    }
  } 
  int ans = -INF;
  pair<int, int> pos;
  for (int i = n; i >= 1; --i) {
    for (int j = 1; j <= m; ++j) {
      D[i][j] = (s[i - 1][j - 1] == '0' ? 0 : D[i + 1][j] + 1);
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) if (s[i - 1][j - 1] == '1') {
      int h = min({L[i][j], R[i][j], U[i][j], D[i][j]});
      if (h > ans) {
        ans = h;
        pos = {i, j};
      }
    }
  }
  if (ans < 0) {
    cout << -1;
  } else {
    cout << (4 * (ans - 1) + 1) << '\n';
    cout << pos.first << " " << pos.second;
  }
  

  return 0;
}