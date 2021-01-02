#include <bits/stdc++.h>

using namespace std;

template<typename T> void Read(T &n) {
    char c; n = 0;
    while (!isdigit(c = getchar()));
    do {
        n = n * 10 + c - '0';
    } while (isdigit(c = getchar()));
}

typedef long long LL;
typedef pair<LL, int> ii;

#ifdef LOCAL
const int MAXN = 1e5 + 10;
const int MAXV = 5e5 + 10;
#else
const int MAXN = 1e5 + 10;
const int MAXV = 5e5 + 10;
#endif

#define index abcdef

int n;
int lab[MAXN];
bool inSet[MAXN];
vector<int> divs[MAXV];
vector<int> index[MAXV];
vector<int> listOfDivisors;
vector<ii> adj[MAXN], curAdj[MAXN];

void sieve() {
    for (int i = 1; i < MAXV; ++i)
        for (int j = i; j < MAXV; j += i)
            divs[j].push_back(i);
}

void readInput() {
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
        inSet[i] = false;
        Read(lab[i]);
        for (int x : divs[lab[i]]) {
            if (index[x].empty())
                listOfDivisors.push_back(x);
            index[x].push_back(i);
        }
    }
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        Read(u); Read(v); Read(w);
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
}

void resetData() {
    for (int x : listOfDivisors)
        index[x].clear();
    listOfDivisors.clear();
}

/* -------------- SOLVING PROBLEM ------------------ */

int tin[MAXN], tout[MAXN];
LL d[MAXN];
int id[MAXN], pos[MAXN];
int mas[MAXN << 1];
int mlog[MAXN << 1];
int mini[20][MAXN << 1];

class LCA {
private:
    int timer;
    int ptr;
public:
    LCA() {}
    void init() {
        timer = 0;
        ptr = 0;
        d[1] = 0;
    }

    void DFS(int u, int p) {
        tin[u] = ++timer;
        pos[u] = ++ptr;
        id[timer] = u;
        mas[ptr] = tin[u];
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].second;
            int w = adj[u][i].first;
            if (v == p) continue;
            d[v] = d[u] + w;
            DFS(v, u);
            mas[++ptr] = tin[u];
        }
        tout[u] = timer;
    }

    void build() {
        init();
        DFS(1, 1);
        mlog[1] = 0;
        for (int i = 2; i <= ptr; ++i) mlog[i] = 1 + mlog[i >> 1];
        for (int i = 1; i <= ptr; ++i) mini[0][i] = mas[i];
        for (int k = 0; k < 19; ++k) {
           for (int i = 1; i <= ptr; ++i) {
              if (i + (1 << (k + 1)) - 1 > ptr) break;
              mini[k + 1][i] = min(mini[k][i], mini[k][i + (1 << k)]);
           }
        }
    }
    // get tin, tout, dist[u][v]
    int lca(int u, int v) {
       int l = pos[u], r = pos[v];
       if (l > r) swap(l, r);
       int k = mlog[r - l + 1];
       int w = id[min(mini[k][l], mini[k][r - (1 << k) + 1])];
       return w;
    }

    LL dist(int u, int v) {
        return d[v] + d[u] - 2 * d[lca(u, v)];
    }
} LCA;

LL calc(vector<int>& a) {
    int root = a[0];
    LL diameter = 0;
    for (int i = 1; i < a.size(); ++i)
        if (LCA.dist(a[0], a[i]) > LCA.dist(a[0], root))
            root = a[i];
    for (int i = 0; i < a.size(); ++i)
        if (LCA.dist(root, a[i]) > diameter)
            diameter = LCA.dist(root, a[i]);
    return diameter;
}

void solve() {
    LCA.build();
    LL ans = 0;
    for (int x : listOfDivisors) {
        ans = max(ans, calc(index[x]) * x);

    }
    printf("%lld\n", ans);
}

int Rand(int l, int r) {
    return l + ((LL)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (LL)rand() * (RAND_MAX + 1) +
                (LL)rand()) % (r - l + 1);
}

int main() {
    //gen();
   // return 0;
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    sieve();

    while (true) {
        Read(n);
        if (n == 0) break;
        readInput();
        solve();
        resetData();
    }
    return 0;
}
