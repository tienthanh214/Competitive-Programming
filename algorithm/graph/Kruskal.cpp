#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

typedef long long LL;
const int N = 1e5 + 10;

struct Edge {
    int u, v, w;
    Edge(int _u = 0, int _v = 0, int _w = 0) : u(_u), v(_v), w(_w) {};
    bool operator < (const Edge &other) const {
        return w < other.w;
    }
};

struct DSU {
    int par[N];
    void Init() {
        memset(par, -1, sizeof(par));
    }
    int Root(int u) {
        if (par[u] < 0) return u;
        return par[u] = Root(par[u]);
    }
    bool Union(int x, int y) {
        x = Root(x); y = Root(y);
        if (x == y) return 0;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return 1;
    }
} DSU;

int n; //number of vertices
vector<Edge> E; //edge list

void Kruskal() {
    LL mst = 0;
    DSU.Init();
    sort(E.begin(), E.end());
    for (int i = 0; i < E.size(); i++) {
        if (DSU.Union(E[i].u, E[i].v)) 
            mst += E[i].w;
    }
    cout << mst;
}

int main() {
    int m;
    cin >> n >> m; 
    for (int i = 0; i < m; i++) {
        int u, v, w; //edge u - v weight w
        cin >> u >> v >> w;
        E.push_back(Edge(u, v, w));
    }
    Kruskal();
    return 0;
}
