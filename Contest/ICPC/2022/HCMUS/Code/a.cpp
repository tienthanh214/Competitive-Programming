#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;

int n, m;
int f[N];
vector<int> adj[N];

void Solve(){
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
            int u, v;
        cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    }
    memset(f, -1, sizeof(f));
    queue<int> Q;
    Q.push(1);
    f[1] = 0;
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        for (int v: adj[u])
        if (f[v] == -1) {
            f[v] = f[u] + 1;
            Q.push(v);
        }
    }
    cout << max(0, f[n] - 1);
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int testcase = 1;
    // cin >> testcase;
    while (testcase--){
        Solve();
    }

    return 0;
}
