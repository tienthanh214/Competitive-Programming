#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> ii;

const int N = 2e5 + 10;
const int MOD = 1e9 + 7;

int n;
int a[N];
int sum[N], sum2[N];

int add(int x, int y) {
    x += y;
    if (x > MOD) x -= MOD;
    if (x < 0) x += MOD;
    return x;
}

void readInput() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        sum[i] = add(sum[i - 1], a[i]);
        sum2[i] = add(sum2[i - 1], 1ll * a[i] * a[i] % MOD);
    }
}

int getSum(int l, int r) {
    return (sum[r] - sum[l - 1] + MOD) % MOD;
}

int getSum2(int l, int r) {
    return (sum2[r] - sum2[l - 1] + MOD) % MOD;
}

int power(int a, int b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    int tmp = power(a, b / 2);
    tmp = 1ll * tmp * tmp % MOD;
    if (b & 1) tmp = 1ll * tmp * a % MOD;
    return tmp;
}

void solve() {
    LL ans = 0;
    for (int k = 2; k <= n; ++k) {
        for (int i = 1; i <= n; i += k) {
            int l = i, r = min(n, i + k - 1);
            ans = add(ans, 1ll * getSum(l, r) * getSum(l, r) % MOD);
            ans = add(ans, MOD - getSum2(l, r));
        }
    }
    cout << 1ll * ans * power(2, MOD - 2) % MOD;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    readInput();
    solve();
    return 0;
}