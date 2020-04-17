include <bits/stdc++.h>

using namespace std;

const int N = 1E4 + 10;

int n, m, timer;
bool critical[N];
int cutive, bridge;
int num[N], low[N];
vector <int> adj[N];

void Read_Input() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void DFS(int u, int p) {
    int branch = 0;
    low[u] = num[u] = ++timer;
    for (int v : adj[u]) if (v != p) {
        if (num[v]) low[u] = min(low[u], num[v]);
            else {
                DFS(v, u); branch++;
                low[u] = min(low[u], low[v]);
                if (low[v] >= num[v]) bridge++;
                if (low[v] >= num[u]) {
                    if (p == -1) {
                        if (branch >= 2) critical[u] = 1;
                    } else critical[u] = 1;
                }
            }
    }
}

void Solve() {
    for (int i = 1; i <= n; i++) 
        if (!num[i]) DFS(i, -1);
    for (int i = 1; i <= n; i++) 
        cutive += critical[i];
    printf("%d %d", cutive, bridge);
}

int main() {
    Read_Input();
    Solve();
    return 0;
}
