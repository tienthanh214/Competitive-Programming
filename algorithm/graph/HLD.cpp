#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

const int N = 1E5 + 10;
const int INF = 1E9 + 7;

vector <int> adj[N];
int n;
int par[N], h[N], child[N];
int chain[N], pos[N], cnt = 0;

struct SegmentTree {
    int It[N * 4];

    void Update(int id, int l, int r, int i, int val) {
        if (i < l || r < i || l > r) return;
        if (l == r) {
            It[id] += val;
            return;
        }
        int mid = (l + r) >> 1;
        Update(id << 1, l, mid, i, val);
        Update(id << 1 | 1, mid + 1, r, i, val);
        It[id] = max(It[id << 1], It[id << 1 | 1]);
    }
    int Find(int id, int l, int r, int u, int v) {
        if (v < l || r < u || l > r) return 0;
        if (u <= l && r <= v) return It[id];
        int mid = (l + r) >> 1;
        return max(Find(id << 1, l, mid, u, v),
                   Find(id << 1 | 1, mid + 1, r, u, v));
    }
    void Update(int i, int val) {
        Update(1, 1, n, i, val);
    }
    int Find(int l, int r) {
        return Find(1, 1, n, l, r);
    }
} ST;

void Read_Input() {
    #ifdef LOCAL
        freopen("HLD.INP", "r", stdin);
        freopen("HLD.OUT", "w", stdout);
    #endif // LOCAL
    scanf("%d", &n);
    REP(i, 1, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    FOR(i, 1, n) adj[i].push_back(0);
    chain[1] = -1; h[1] = 1; par[1] = 1;
}

void DFS(int u) {
    child[u] = 1;
    for (int i = 0; int v = adj[u][i]; i++)
        if (par[v] == 0) {
            par[v] = u;
            h[v] = h[u] + 1;
            DFS(v);
            child[u] += child[v];
        }
}

void HLD(int u) {
    int special = -1, maxchild = 0;
    if (chain[u] == -1) chain[u] = u;
    pos[u] = ++cnt;
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != par[u] && child[v] > maxchild) {
            maxchild = child[v];
            special = v;
        }
    if (special != -1) {
        chain[special] = chain[u];
        HLD(special);
    }
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != par[u] && v != special) {
            chain[v] = -1;
            HLD(v);
        }
}

int LCA(int u, int v) {
    while (chain[u] != chain[v]) {
        if (h[chain[u]] < h[chain[v]]) v = par[chain[v]];
            else u = par[chain[u]];
    }
    return h[u] < h[v] ? u : v;
}

int GetMax(int u, int v) {
    int ret = 0;
    while (chain[u] != chain[v]) {
        ret = max(ret, ST.Find(pos[chain[u]], pos[u]));
        u = par[chain[u]];
    }
    return max(ret, ST.Find(pos[v], pos[u]));
}

int Query(int u, int v) { //maximum value on path u -> v
    int p = LCA(u, v);
    return max(GetMax(u, p), GetMax(v, p));
}

void Solve() {
    int q; scanf("%d\n", &q);
    while (q--) {
        char c; int u, v;
        scanf("%c %d %d\n", &c, &u, &v);
        if (c == 'I') ST.Update(pos[u], v); //assign value of node u to v
            else printf("%d\n", Query(u, v));
    }
}

int main() {
    Read_Input();
    DFS(1);
    HLD(1);
    Solve();
    return 0;
}
