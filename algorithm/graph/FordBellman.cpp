#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9 + 7;
const int MAXN = 1005;
struct Edge {
    int u, v, w;
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {};
};

int n, m;
int dist[MAXN];
vector<Edge> E;

void FordBellman(int start, int finish) {
    bool check;
    for (int i = 1; i <= n; i++)
        dist[i] = INF;
    dist[start] = 0;
    for (int i = 0; i < n; i++) {
        check = true;
         for (int j = 0; j < E.size(); j++)
            if (dist[E[j].v] > dist[E[j].u] + E[j].w) {
                dist[E[j].v] = dist[E[j].u] + E[j].w;
                check = false;
            }
    }
    if (check == false) cout << "Have negative cycle from source";
    else cerr << dist[finish];
}

int main() {
    cin >> n >> m; 
    for (int i = 0; i < m; i++) {
        int u, v, w; //edge u - v weight w
        cin >> u >> v >> w;
        E.push_back(Edge(u, v, w));
        E.push_back(Edge(v, u, w)); // undirected graph
    }
    FordBellman(1, n);
    return 0;
}
