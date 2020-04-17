//centroid decomposition
// this code count number of pairs vertex (x, y) that simple path x -> y equal to k
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

typedef long long LL;
const int N = 5E4 + 10;

vector <int> adj[N];
int n, k;
int a[N];
LL ans = 0;

void Read_Input() {
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    scanf("%d %d", &n, &k);
    REP(i, 1, n) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    FOR(i, 1, n) adj[i].push_back(0);
}

int rsz;
int child[N], dist[N];
bool Free[N];

void GetSize(int u, int p) {
    child[u] = 1; rsz++;
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p && Free[v]) {
            GetSize(v, u);
            child[u] += child[v];
        }
}

int GetCentroid(int u, int p) {
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p && Free[v] && child[v] * 2 > rsz)
            return GetCentroid(v, u);
    return u;
}

void Add(int u, int p, int level) {
    dist[level]++;
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p && Free[v])
            Add(v, u, level + 1);
}

void Query(int u, int p, int level) {
    if (k - level < 0) return;
    ans += dist[k - level];
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p && Free[v])
            Query(v, u, level + 1);
}

void Decompose(int u, int precentroid) {
    rsz = 0; GetSize(u, u);
    int centroid = GetCentroid(u, u);
    Free[centroid] = 0;
    FOR(i, 0, n) if (dist[i]) dist[i] = 0;
        else break;
    dist[0]++;
    for (int i = 0; int v = adj[centroid][i]; i++)
        if (v != precentroid && Free[v]) {
            Query(v, centroid, 1);
            Add(v, centroid, 1);
        }

    for (int i = 0; int v = adj[centroid][i]; i++)
        if (Free[v]) Decompose(v, centroid);
}

int main() {
    Read_Input();
    memset(Free, 1, sizeof(Free));
    Decompose(1, -1);
    printf("%I64d", ans);
    return 0;
}
