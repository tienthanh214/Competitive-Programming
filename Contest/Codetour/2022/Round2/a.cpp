#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> ii;

const int N = 1e5 + 10;

int n;
int x[N], y[N];

void readInput() {
    for (int i = 1; i <= n; ++i)
        cin >> x[i] >> y[i];
    x[0] = x[n];
    y[0] = y[n];
    x[n + 1] = x[1];
    y[n + 1] = y[1];
}

void solve() {
    long long S = 0;
    for (int i = 1; i <= n; ++i) {
        S += 1ll * x[i] * (y[i + 1] - y[i - 1]);
    }
    cout << fixed << setprecision(2) << abs(S) / 2.0 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    while (cin >> n) {
        if (n == 0) break;
        readInput();
        solve();
    }
    return 0;
}