#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10; 

int n, k;
long long a[N], f[N][2], sum[N];

void Solve(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) f[i][0] = f[i][1] = -1e16;
    for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i];
    long long ans = 0;
    for (int i = 1; i <= n; i++){
        f[i][0] = f[i - 1][0];
        if (i - k >= 0) f[i][0] = max(f[i][0], f[i - k][1] + sum[i] - sum[i - k]);
        f[i][1] = f[i - 1][1];
        if (i - k >= 0) f[i][1] = max(f[i][1], f[i - k][0] - sum[i] + sum[i - k]);
        if (i >= k) ans = max(ans, f[i][0]);
        if (i >= k) ans = max(ans, f[i][1]);
    }
    cout << ans << '\n';
}

int main() {
   ios_base::sync_with_stdio(0);
   cin.tie(0); cout.tie(0);
    int tcase = 1;
    cin >> tcase;
    // cout << tcase << endl;
    while (tcase--){
        Solve();
    }
    return 0; 
}