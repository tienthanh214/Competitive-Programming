#include <iostream>
#include <string.h>

using namespace std;

class DisjointSet {
    static const int MAXN = 1e5 + 10;
private:
    int par[MAXN];
public:
    DisjointSet() {
        memset(par, -1, sizeof(par));
    }
    ~DisjointSet() {}
    int Root(int u) {
        if (par[u] < 0) return u;
        return par[u] = Root(par[u]); //path compressed
    }
    bool Union(int x, int y) {
        //return 0 if x, y same set else 1.
        x = Root(x); y = Root(y);
        if (x == y) return 0;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y]; //union by rank
        par[y] = x;
        return 1;
    }
};

int main() {
    DisjointSet DSU;
    cout << DSU.Union(1, 3);
    cout << DSU.Union(2, 4);
    cout << DSU.Union(2, 3);
    cout << DSU.Union(1, 4);
    return 0;
}