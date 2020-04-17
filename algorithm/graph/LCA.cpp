#include <stdio.h>
#include <vector>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 1E5 + 10;
const int K = 20; // ~log2(MAXN)

int n;
vector<int> adj[MAXN];

struct LCATable {
    int par[MAXN], h[MAXN];
    int P[MAXN][K];

    void DFS(int u) {
        for (int v : adj[u])
            if (par[v] == 0) {
                par[v] = u;
                h[v] = h[u] + 1;
                DFS(v);
            }
    }
    void Build() {
        memset(par, 0, sizeof(par));
        h[1] = 1; par[1] = 1; //root = 1
        DFS(1);
        for (int i = 1; i <= n; i++) 
            P[i][0] = par[i];
        for (int j = 1; 1 << j <= n; j++)
            for (int i = 1; i <= n; i++)
                P[i][j] = P[P[i][j - 1]][j - 1];
    }
    int LCA(int u, int v) {
        if (h[u] < h[v]) swap(u, v);
        int k = log2(h[u]);
        for (int i = k; i >= 0; i--) if (h[P[u][i]] >= h[v]) u = P[u][i];
        for (int i = k; i >= 0; i--) if (h[P[v][i]] >= h[u]) v = P[v][i];
        if (u == v) return u;
        for (int i = k; i >= 0; i--) if (P[u][i] != P[v][i]) 
            u = P[u][i], v = P[v][i];
        return par[u];
    }
} LCATable;

void readInput() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) 
        adj[i].clear();
    for (int i = 1; i <= n; i++) {
        // i has k child
        int k; scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            int x; scanf("%d", &x);
            adj[i].push_back(x);
        }
    }
}

void Solve(int TC) {
    int q; scanf("%d", &q);
    LCATable.Build();
    printf("Case %d:\n", TC);
    while (q--) {
        int u, v;
        scanf("%d%d", &u, &v);
        printf("%d\n", LCATable.LCA(u, v));
    }
}

int main() {
    int TC; scanf("%d", &TC);
    for (int Test = 1; Test <= TC; Test++) {
        readInput();
        Solve(Test);
    }
    return 0;
}
