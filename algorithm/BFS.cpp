#include <bits/stdc++.h>

using namespace std;

const int N = 1E5 + 10; //number of vertex

int n, m;
int d[N]; //minimum path(edge) from source
vector <int> adj[N];

void BFS(int s, int t) { // s -> t
    queue <int> Q;
    memset(d, 0, sizeof(d));
    Q.push(s); d[s] = 1;
    while (Q.size()) {
        int u = Q.front();
        Q.pop();
        if (u == t) break; 
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if (d[v] == 0) { //if v not visited
                d[v] = d[u] + 1;
                Q.push(v);
            }
        }
    }
    printf("%d", d[t]);
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u); //undirected-graph
    }
    BFS(1, n);
    return 0;
}
