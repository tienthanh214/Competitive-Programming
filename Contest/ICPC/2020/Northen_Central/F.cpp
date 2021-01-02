#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

const int N = 40;

LL f[N];

int main() {
    f[0] = 1; f[1] = 9; f[2] = 9;
    for (int i = 3; i < N; ++i) {
        f[i] = f[i - 2] * 10ll;
        //cout << f[i] << endl;
    }
    int TC; cin >> TC;
    while (TC--) {
        int n; cin >> n;
        unsigned long long ans = 0;
        for (int i = 0; i <= n; ++i)
            ans += f[i];
        for (int i = 1; i < n; ++i)
            ans += f[i] * (n - i);
        cout << ans + 1 << endl;
    }
    return 0;
}
