#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

const int N = 3E4 + 10;

int n, m, timer, ans;
vector <int> adj[N];
int num[N], low[N];
stack <int> S;

void Read_Input() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    scanf("%d%d", &n, &m);
    FOR(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void DFS(int u, int p) {
    int branch = 0; S.push(u);
    num[u] = low[u] = ++timer;
    for (int v : adj[u]) if (v != p) {
        if (num[v]) low[u] = min(low[u], num[v]);
            else {
                DFS(v, u); branch++;
                low[u] = min(low[u], low[v]);
                if (low[v] >= num[u]) {
                    int x; int cnt = 1;
                    do {
                        x = S.top(); S.pop();
                        cnt++;
                    } while (x != v);
                    ans = max(ans, cnt);
                }
            }
    }
}

void Solve() {
    ans = 1;
    FOR(i, 1, n) if (!num[i]) DFS(i, -1);
    printf("%d", ans);
}

int main() {
    Read_Input();
    Solve();
    return 0;
}
