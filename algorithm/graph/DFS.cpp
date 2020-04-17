#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1e5 + 10;

bool visited[MAXN];
vector<int> adj[MAXN];

void DFS(int u) {
    cout << u << " ";
    visited[u] = true;
    for (int v : adj[u]) 
        if (!visited[v]) DFS(v);
}

int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    DFS(1);
    return 0;
}
