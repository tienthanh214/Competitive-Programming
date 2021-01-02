#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int N = 1e6 + 10;
const int base = 1e9 + 7;

int n, m;
int fact[2 * N], inv[2 * N];
int fib[2 * N];

int power(int a, int b) {
    if (b == 0) return 1;
    int tmp = power(a, b / 2);
    tmp = 1ll * tmp * tmp % base;
    if (b & 1) return 1ll * tmp * a % base;
    return tmp;
}

void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = 1ll * fact[i - 1] * i % base;
    inv[n] = power(fact[n], base - 2);
    for (int i = n - 1; i >= 0; --i)
        inv[i] = 1ll * inv[i + 1] * (i + 1) % base;
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i <= n; ++i)
        fib[i] = (fib[i - 1] + fib[i - 2]) % base;

}

int Ckn(int n, int k) {
    if (k > n) return 0;
    return 1ll * fact[n] * (1ll * inv[k] * inv[n - k] % base) % base;
}

void solve() {
    int ans = 0;
    for (int i = 1; i <= m; ++i) {
        ans = (ans + 1ll * Ckn(n + m - i - 1, m - i) * fib[i] % base) % base;
    }
    for (int i = 1; i <= n; ++i) {
        ans = (ans + 1ll * Ckn(n + m - i - 1, m - 1) * fib[i] % base) % base;
    }
    printf("%d", ans);
}

int main() {
    scanf("%d%d", &n, &m);
    init(n + m);
    solve();
    return 0;
}
