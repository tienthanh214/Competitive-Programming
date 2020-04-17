#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int N = 150;
const int INF = 1e9 + 7;

int n, m, s, t, send;
int c[N][N], w[N][N], f[N][N];
int ans = 0;
int inqueue[N];
int d[N], trace[N];

bool FordBellman(int s, int t) {
    queue <int> Q;
    memset(inqueue, 0, sizeof(inqueue));
    memset(trace, 0, sizeof(trace));
    for (int i =1; i <= n; i++) d[i] = INF;
    Q.push(s); inqueue[s] = 1;
    trace[s] = -1; d[s] = 0;
    while (Q.size()) {
        int u = Q.front();
        Q.pop(); inqueue[u] = 0;
        for (int v = 1; v <= n; v++) {
            if (w[u][v] == INF) continue;
            if (c[u][v] - f[u][v] <= 0) continue;
            int cost = f[u][v] >= 0 ? w[u][v] : -w[u][v];
            if (d[v] > d[u] + cost) {
                d[v] = d[u] + cost;
                trace[v] = u;
                if (inqueue[v]) continue;
                Q.push(v); inqueue[v] = 1;
            }
        }
    }
    return d[t] < INF;
}

int IncFlow(int s, int t) {
    int delta = INF;
    for (int v = t; trace[v] != -1; v = trace[v]) {
        int u = trace[v];
        if (f[u][v] < 0) delta = min(delta, -f[u][v]);
            else delta = min(delta, c[u][v] - f[u][v]);
    }
    for (int v = t; trace[v] != -1; v = trace[v]) {
        int u = trace[v];
        f[u][v] += delta;
        f[v][u] -= delta;
    }
    ans += delta * d[t];
    return delta;
}

void MinCostFlow() {
    while (FordBellman(s, t)) {
        if (send == 0) break;
        send -= IncFlow(s, t);
    }
    printf("%d\n", ans);
}

void readInput() {
    scanf("%d%d", &n, &m);
    scanf("%d", &send);
    scanf("%d%d", &s, &t);
    for (int i = 1; i <= n; i++) 
        for (int j = 1; j <= n; j++)
            w[i][j] = INF;
    for (int i = 0; i < m; i++) {
        int u, v, cost, cap;
        scanf("%d%d%d%d", &u, &v, &cost, &cap);
        c[u][v] = c[v][u] = cap;
        w[u][v] = w[v][u] = cost;
    }
}

int main() {
    readInput();
    MinCostFlow();
    return 0;
}
