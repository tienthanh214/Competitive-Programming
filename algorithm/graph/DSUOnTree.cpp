#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

typedef long long LL;
const int N = 1E5 + 10;

vector <int> adj[N];
int n, maxappear = 0;
int col[N], child[N], cnt[N];
LL answer = 0, ans[N];
bool big[N];

void Read_Input() {
    #ifdef LOCAL
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // LOCAL
    scanf("%d", &n);
    FOR(i, 1, n) scanf("%d", &col[i]);
    REP(i, 1, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    FOR(i, 1, n) adj[i].push_back(0);
}

void GetChild(int u, int p) {
    child[u] = 1;
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p) {
            GetChild(v, u);
            child[u] += child[v];
        }
}

void Add(int u, int p, int val) {
    cnt[col[u]] += val;
    if (val == 1)
        if (cnt[col[u]] > maxappear) maxappear = cnt[col[u]], answer = col[u];
            else if (cnt[col[u]] == maxappear) answer += col[u];
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p && !big[v])
            Add(v, u, val);
}

void DFS(int u, int p, bool keep) {
    int mx = -1, bigchild = -1;
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p && child[v] > mx) {
            mx = child[v];
            bigchild = v;
        }
    for (int i = 0; int v = adj[u][i]; i++)
        if (v != p && v != bigchild)
            DFS(v, u, 0);
    if (bigchild != -1)
        DFS(bigchild, u, 1), big[bigchild] = 1;
    Add(u, p, 1);
    ans[u] = answer;
    if (bigchild != -1) big[bigchild] = 0;
    if (keep == 0) Add(u, p, -1), answer = maxappear = 0;
}

void Solve() {
    memset(ans, 0, sizeof(ans));
    memset(cnt, 0, sizeof(cnt));
    memset(child, 0, sizeof(child));
    GetChild(1, -1);
    DFS(1, -1, 0);
    FOR(i, 1, n) printf("%I64d ", ans[i]);
}

int main() {
    Read_Input();
    Solve();
    return 0;
}
