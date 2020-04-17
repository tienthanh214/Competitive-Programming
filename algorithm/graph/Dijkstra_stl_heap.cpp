#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long LL;
typedef pair<LL, int> II;

const LL INF = 1e15;
const int N = 1e5 + 10;

int n, m;
LL dist[N];
int trace[N];
vector<II> adj[N];

void Dijkstra(int start, int finish) {
    priority_queue<II, vector<II>, greater<II>> heap;
    for (int i = 1; i <= n; i++) 
        dist[i] = INF;
    dist[start] = 0;
    heap.push({0, start});
    while (heap.size()) {
        LL du = heap.top().first;
        int u = heap.top().second;
        heap.pop();
        if (u == finish) break;
        if (du != dist[u]) continue;
        for (int i = 0; i < adj[u].size(); i++) {
            LL w = adj[u][i].first;
            int v = adj[u][i].second;
            if (dist[v] > dist[u] + w) {
                trace[v] = u;
                dist[v] = dist[u] + w;
                heap.push({dist[v], v});
            }
        }
    }
}

void Trace(int u) { //trace path from source
    if (!u) return;
    Trace(trace[u]);
    printf("%d ", u);
}

int main() {
    // read graph
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v, w; 
        scanf("%d%d%d", &u, &v, &w);
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    // run Dijkstra from 1 to n
    Dijkstra(1, n);
    if (dist[n] < INF) Trace(n);
    else puts("-1");
    return 0;
}
