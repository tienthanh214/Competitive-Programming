#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

const int N = 105;

int n, m;
vector <int> adj[N];
int match[N], vis[N], Timer = 0;

void Read_Input() {
    scanf("%d%d", &n, &m);
    int x, y;
    while (scanf("%d%d", &x, &y) == 2)
        adj[x].push_back(y);
}

int DFS(int u) {
    if (vis[u] == Timer) return 0;
    vis[u] = Timer;
    for (int v: adj[u])
        if (!match[v] || DFS(match[v])) {
            match[v] = u;
            return 1;
        }
    return 0;
}

void MaxMatch() {
    int ans = 0;
    for (int u = 1; u <= n; u++) {
        Timer++;
        ans += DFS(u);
    }
    printf("%d\n", ans);
    for (int u = 1; u <= m; u++) 
        if (match[u])
            printf("%d %d\n", match[u], u);
}

int main() {
    Read_Input();
    MaxMatch();
    return 0;
}
