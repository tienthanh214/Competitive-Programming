#include <iostream>

const int MAXN = 105;
const int INF = 1e9 + 7;

int n, m;
int cost[MAXN][MAXN];
int trace[MAXN][MAXN];

void Floyd() {
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            trace[u][v] = v;

    for (int k = 1; k <= n; k++)
        for (int u = 1; u <= n; u++)
            for (int v = 1; v <= n; v++)
                if (cost[u][v] > cost[u][k] + cost[k][v]) 
                    cost[u][v] = cost[u][k] + cost[k][v],
                    trace[u][v] = trace[u][k];
     
}

void Trace(int start, int finish) {
    if (cost[start][finish] >= INF) puts("-1");
    else {
        printf("%d\n", cost[start][finish]);
        while (start != finish) {
            printf("%d -> ", start);
            start = trace[start][finish];
        }
        printf("%d\n", finish);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cost[i][j] = i == j ? 0 : INF;
    
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        cost[u][v] = w;
        cost[v][u] = w; // undirected graph
    }
    Floyd();
    Trace(1, 4);
    return 0;
}
