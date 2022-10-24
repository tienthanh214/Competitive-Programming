#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

int f[N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int n, m, s;
    cin >> m >> n >> s;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    memset(f, -1, sizeof(f));
    f[s] = 0;
    queue<int> Q;
    Q.push(s);
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        if (u == 0) {
            cout << f[u] << endl;
            return 0;
        }
//        cout << u << " "  << f[u] << endl;
        for (int i = 0; i < n; ++i) {
            int newU = (1ll * u * a[i] + b[i]) % m;
            if (f[newU] == -1) {
                f[newU] = f[u] + 1;
                Q.push(newU);
            }
        }
    }
    cout << -1 << endl;



    return 0;
}
