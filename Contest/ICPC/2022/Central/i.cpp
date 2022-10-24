#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10; 

long long dp[N][5][4]; 
long long cnt[6];

int main() {
    int n; 
    cin >> n; 
    vector<int> a(n); 
    for (int i = 0; i < n; ++i) { 
        cin >> a[i]; 
        a[i] %= 5; 
    }
    /*dp[0][0][0] = 1;
    for (int i = 1; i <= n; ++i) { 
        for (int j = 0; j < 5; ++j) { 
            for (int k = 0; k <= 3; ++k) {
                dp[i][j][k] = dp[i - 1][j][k];
                if (k >= 0) {
                    dp[i][j][k] += dp[i - 1][(j - a[i - 1] + 5) % 5][k - 1];
                }
            }
        }
    }
    
    cout << dp[n][0][3] << endl;
    */
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++){
        cnt[a[i]]++;
    }
    long long ans = 0;
    for (int i = 0; i < 5; i++)
    for (int j = i + 1; j < 5; j++)
    for (int k = j + 1; k < 5; k++) if ((i + j + k) % 5 == 0){
        ans += cnt[i] * cnt[j] * cnt[k];
    }
    for (int i = 0; i < 5; i++)
    for (int j = 0; j < 5; j++) if (i != j && (i * 2 + j) % 5 == 0){
        ans += cnt[i] * (cnt[i] - 1) / 2 * cnt[j]; 
    }
    for (int i = 0; i < 5; i++) if (3 * i % 5 == 0){
        ans += cnt[i] * (cnt[i] - 1) * (cnt[i] - 2) / 6;
    }
    cout << ans << endl;
    /*
    ans = 0;
    for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    for (int k = j + 1; k < n; k++) if ((a[i] + a[j] + a[k]) % 5 == 0) ans++;
    cout << ans << endl;*/
    return 0; 
}