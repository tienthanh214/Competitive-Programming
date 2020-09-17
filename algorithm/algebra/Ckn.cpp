#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

const int base = 1E9 + 7;
const int N = 1E6 + 10;

int n, k;
int fact[N], inv[N];

int Power(int a, int b) {
    if (b == 0) return 1;
    int tmp = Power(a, b / 2);
    tmp = 1ll * tmp * tmp % base;
    if (b & 1) return 1ll * tmp * a % base;
    return tmp % base;
}

int C(int k, int n) {
    /// nCk = n! / (k! * (n - k)!)
    return 1LL * fact[n] * inv[k] % base * inv[n - k] % base;
}

int Catalan(int n) {
    /// Catalan(n) = 2nCn / (n + 1)
    return 1LL * C(n, n * 2) * fact[n] % base * inv[n + 1] % base;
}

int main() {
    freopen("math.INP", "r", stdin);
    freopen("math.out", "w", stdout);
    cin >> n; n *= 2;
    fact[0] = 1;
    FOR(i, 1, n) fact[i] = 1LL * fact[i - 1] * i % base;
    inv[n] = Power(fact[n], base - 2);
    FOD(i, n - 1, 1) inv[i] = 1LL * inv[i + 1] * (i + 1) % base;
    cout << Catalan(n / 2);
    return 0;
}
