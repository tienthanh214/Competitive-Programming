#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 1e3 + 1;

int n, m, k;
int a[MAX_N * 2][MAX_N * 2];
int S[MAX_N * 2][MAX_N * 2];

int getSum(int x, int y, int u, int v) {
    x = max(x + MAX_N, 1); y = max(y, 1);
    u = min(u + MAX_N, MAX_N * 2 - 1); v = min(v, MAX_N * 2 - 1);
    return S[u][v] - S[u][y - 1] - S[x - 1][v] + S[x - 1][y - 1];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) 
            cin >> a[i - j + MAX_N][i + j];
    for (int i = 1; i < MAX_N * 2; ++i)
        for (int j = 1; j < MAX_N * 2; ++j)
            S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + a[i][j];
    int q; cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << getSum(x - y - k, x + y - k, x - y + k, x + y + k) << '\n';
    }
    return 0;
}