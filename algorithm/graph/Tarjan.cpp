#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

typedef long long ll;
const int N = 2E4 + 10;

vector <int> adj[N];
int n, m;
int low[N], number[N], Time = 0;
stack <int> S;
bool Free[N];
int component = 0;

void Visit(int u) {
    number[u] = low[u] = ++Time;
    S.push(u);
    for (int v : adj[u]) {
        if (!Free[v]) continue;
        if (!number[v]) {
            Visit(v);
            low[u] = min(low[u], low[v]);
        } else low[u] = min(low[u], number[v]);
    }
    if (number[u] == low[u]) {
        int v;
        component++;
        do {
            v = S.top(); S.pop();
            Free[v] = 0;
        } while (v != u);
    }
}

void Tarjan() {
    memset(Free, 1, sizeof(Free));
    FOR(i, 1, n) if (!number[i])
        Visit(i);
    printf("%d", component);
}

void Read_Input() {
    scanf("%d%d", &n, &m);
    FOR(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
    }
}

int main() {
    Read_Input();
    Tarjan();
    return 0;
}
