#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<int> f(1 << m);
        for (int i = 0; i < n; ++i) {
            string str;
            cin >> str;
            int x = 0;
            for (int j = 0; j < m; ++j) {
                x += (str[j] - '0') << j;
            }
            f[x] = (f[x] + f[((1 << m) - 1) ^ x] + 1) % MOD;
        }
        int res = 0;
        for (int x: f)
            res = (res + x) % MOD;
        cout << res << endl;
    }

    return 0;
}
