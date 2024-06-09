#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAX_N = 5005;
const ll INF = 1e18 + 7;

ll dp[MAX_N][MAX_N];
int n, k, d;
int a[MAX_N], b[MAX_N], t[MAX_N];

void readInput() {
    cin >> n >> k >> d;
    t[0] = -1;
    for (int i = 1; i <= n; ++i) cin >> t[i];
    for (int i = 1; i <= k; ++i) cin >> a[i];
    for (int i = 1; i <= k; ++i) cin >> b[i];
}

/*
    dp(i, x, y) = xét đến nhiệm vụ i, nhiệm vụ trước A làm ở vị trí x và B ở y
    và thoả mãn không có ai làm d nhiệm vụ liên tiếp
    
    dp(i, x, y) -> dp(i + 1, i, y) + (t[x] == t[i] ? b[t[i]] : a[t[i]])
                -> dp(i + 1, x, i) + (t[y] == t[i] ? b[t[i]] : a[t[i]])
    Ta nhận thấy luôn có giá trị i nằm trong x hoặc y, nên ta có thể giảm không gian bằng cách bỏ luôn i
    Gọi dp(i, j) là một người đã làm đến nhiệm vụ i, và người còn lại làm đến nhiệm vụ j
*/

ll cal(int i, int x, int y) {
    if (i - 1 - x > d) return INF;
    if (i - 1 - y > d) return INF;
    if (i > n) return 0;
    ll &ret = dp[x][y];
    if (ret < INF) return ret;
    ret = INF - 1;
    ret = min(ret, cal(i + 1, i, y) + (t[x] == t[i] ? b[t[i]] : a[t[i]]));
    ret = min(ret, cal(i + 1, x, i) + (t[y] == t[i] ? b[t[i]] : a[t[i]]));
    // cout << i << ' ' << x << ' ' << y << ' ' << ret << endl;
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int TC; cin >> TC;
    while (TC--) {
        readInput();
        for (int i = 0; i <= n + 1; ++i) 
            for (int j = 0; j <= n + 1; ++j)
                dp[i][j] = INF;
        ll ans = INF;
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int y = max(0, i - d - 1); y <= i; ++y) {
                dp[i][i - 1] = min(dp[i][i - 1], dp[i - 1][y] + (t[y] == t[i] ? b[t[i]] : a[t[i]]));
                if (i - y <= d) 
                    dp[i][y] = min(dp[i][y], dp[i - 1][y] + (t[i - 1] == t[i] ? b[t[i]] : a[t[i]]));
            }
        }
        for (int i = 0; i < n; ++i) 
            ans = min(ans, dp[n][i]);
        // Brute-force
        // for (int mask = 0; mask < (1 << n); ++mask) {
        //     int prev[2] = {0, 0};
        //     long long res = 0;
        //     for (int i = 0; i < n; ++i) {
        //             if (i + 1 - prev[0] > d + 1 || i + 1 - prev[1] > d + 1) {
        //                 res = INF;
        //                 break;
        //             }
        //             res += (t[i + 1] == t[prev[mask >> i & 1]] ? b[t[i + 1]] : a[t[i + 1]]);
        //             prev[mask >> i & 1] = i + 1;
                
        //     }
        //     ans = min(ans, res);
        // }
        cout << ans << '\n';
    }
    
    return 0;
}