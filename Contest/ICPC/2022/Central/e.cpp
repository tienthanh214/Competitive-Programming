#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int MOD = 1e9 + 7;

int n, m, K;
int p[N];
int a[N][N];
int dp[N][N][12];
long long sum[N][N];

void readInput() {
    cin >> n >> m >> K;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
        }
    }

    for (int i = 1; i <= K; ++i) {
        cin >> p[i];
    } 
}

long long getSum(int x, int y, int u, int v) {
    if (x > u || y > v) return 1e9;
    return sum[u][v] - sum[x - 1][v] - sum[u][y - 1] + sum[x - 1][y - 1];
}

void Add(int &x, int y) {
    x += y;
    if (x >= MOD) x-= MOD;
}

void solve() {
    dp[1][1][1] = 1;
    for (int k = 1; k < K; ++k) {
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= m; ++y) {
                for (int i = x + 1; i <= n; ++i) {
                    // if (i == 2 && y == 1 && k + 1 == 2)     
                    //     cout << x << " " << y << " " << k << " " <<  getSum(x, y, i - 1, y) << endl; 
                    if (getSum(x, y, i - 1, m) <= p[k]) {
                        Add(dp[i][y][k + 1], dp[x][y][k]);
                    }
                }
                for (int i = y + 1; i <= m; ++i) {
                    // if (x == 2 && i == 1 && k + 1 == 2)     
                    //     cout << x << " " << y << " " << k << " " << getSum(x, y, x, i - 1) << endl; 
                    if (getSum(x, y, n, i - 1) <= p[k]) {
                        Add(dp[x][i][k + 1], dp[x][y][k]);
                    }
                }
            }
            // cout << "DEBUG: " << k << " " << x << " " << y << " " << dp[x][y][k] << endl;
        }
    }
    // cout << dp[2][1][2] << " " << dp[1][2][2] << endl; 
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (getSum(i, j, n, m) <= p[K]) { 
                // cout << i << " " << j << " " << dp[i][j][K] << endl; 
                Add(ans, dp[i][j][K]);
            }
        }
    }
    cout << ans;
}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    readInput();
    solve();


    return 0; 
}