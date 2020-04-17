#include <stdio.h>
#include <string.h>
#include <queue>

using namespace std;

const int N = 50005;
const int INF = 1E9;

int n, m, p;
vector <int> adj[N];
int matchX[N], matchY[N], d[N];

bool FindPath() {
    queue <int> Q;
    memset(d, 0, sizeof(d));
    for (int u = 1; u <= n; u++) 
        if (!matchX[u]) {
            Q.push(u);
            d[u] = 1;
        }
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        for (int v : adj[u]) {
            if (d[matchY[v]]) continue;
            d[matchY[v]] = d[u] + 1;
            Q.push(matchY[v]);
        }
    }
    return d[0] > 0;
}

bool DFS(int u) {
    if (u == 0) return 1;
    for (int v : adj[u]) {
        if (d[matchY[v]] == d[u] + 1)
            if (DFS(matchY[v])) {
                matchX[u] = v;
                matchY[v] = u;
                return 1;
            }
    }
    d[u] = 0;
    return 0;
}

void MaxMatch() {
    int ans = 0;
    while (FindPath())
        for (int u = 1; u <= n; u++) 
            if (!matchX[u])
                ans += DFS(u);
    printf("%d\n", ans);
    //FOR(i, 1, n) if (matchX[i]) printf("%d %d\n", i, matchX[i]);
}

void readInput() {
    scanf("%d%d%d", &n, &m, &p); //set N - set M , p edge
    int x, y;
    while (p--) {
        scanf("%d%d", &x, &y);
        adj[x].push_back(y); //x in N - y in M
    }
}

int main() {
    readInput();
    MaxMatch();
    return 0;
}
