#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> II;

const int INF = 1e9 + 7;
const int MAXN = 1005;

int n, m;
int dist[MAXN];
bool inqueue[MAXN];
vector<II> adj[MAXN];

void FordBellman(int start, int finish) { // SPFA (Shortest Path Faster Algorithm)
    queue<int> Q;
    for (int i = 1; i <= n; i++)
        dist[i] = INF,
        inqueue[i] = false;
    Q.push(start);
    dist[start] = 0;
    inqueue[start] = true;
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        inqueue[u] = false;
        for (int i = 0; i < adj[u].size(); i++) {
            int w = adj[u][i].first;
            int v = adj[u][i].second;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                if (!inqueue[v]) {
                    Q.push(v);
                    inqueue[v] = true;
                }
            }
        }
    }
    cerr << dist[finish];
}

int main() {
    cin >> n >> m; 
    for (int i = 0; i < m; i++) {
        int u, v, w; //edge u - v weight w
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});// undirected graph
    }
    FordBellman(1, n);
    return 0;
}
