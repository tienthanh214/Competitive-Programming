#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int M = 1010;
const int N = 1010;
const int INF = 1E9 + 7;

int n, m, s, t;
int c[N][N], f[N][N];
int d[N];
bool visited[N];

bool FindPath() {
    queue <int> Q;
    memset(d, 0, sizeof(d));
    Q.push(s); d[s] = 1;
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        if (u == t) return 1;
        for (int v = 1; v <= n; v++)
            if (c[u][v] - f[u][v] > 0 && !d[v]) {
                Q.push(v);
                d[v] = d[u] + 1;
            }
    }
    return 0;
}

int IncFlow(int u, int flow) {
    visited[u] = 0;
    if (u == t) return flow;
    for (int v = 1; v <= n; v++)
        if (c[u][v] - f[u][v] > 0 && d[v] == d[u] + 1 && visited[v]) {
            int x = IncFlow(v, min(flow, c[u][v] - f[u][v]));
            if (x > 0) {
                f[u][v] += x;
                f[v][u] -= x;
                return x;
            }
        }
    return 0;
}

void Dinitz() {
    int maxflow = 0;
    while (FindPath()) {
        memset(visited, 1, sizeof(visited));
        int x;
        while (x = IncFlow(s, INF)) {
            maxflow += x;
            memset(visited, 1, sizeof(visited));
        }
    }
    printf("%d", maxflow);
}


int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        c[u][v] += w;
    }

    Dinitz();
    return 0;
}
