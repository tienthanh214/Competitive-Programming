#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long ll;

const int N = 1000 * 2 + 5;
const int INF = 1e9 + 10;

int m, n;
int profit[N], cost[N], a[N][N];

namespace Dinitz {
    int s, t;
    int level[N], f[N][N], c[N][N];
    bool visited[N];
    vector <int> adj[N];

    void addEdge(int u, int v, int cap){
        adj[u].push_back(v);
        adj[v].push_back(u);
        c[u][v] = cap;
    }

    void BuildNetwork() {
        s = 0; // source of network
        t = n + m + 1; // sink of network
        for(int i = 1; i <= m; i++)
            addEdge(s, i, profit[i]);
        for(int i = 1; i <= n; i++)
            addEdge(i + m, t, cost[i]);
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                if (a[i][j]) {
                    addEdge(i, j + m, INF);
                }
            }
        }
    }
    bool FindPath() {
        for(int i = 0; i <= n + m + 1; i++)
            level[i] = -1;
        queue<int> qu;
        level[s] = 0;
        qu.push(s);
        while (!qu.empty()){
            int u = qu.front(); qu.pop();
            if (u == t) return true;
            for(int v : adj[u])
                if (level[v] == -1 && f[u][v] < c[u][v]){
                    level[v] = level[u] + 1;
                    qu.push(v);
                }
        }
        return false;
    }
    int IncFlow(int u, int flow){
        if (u == t) return flow;
        if (visited[u]) return 0;
        for(int v : adj[u])
            if (level[v] == level[u] + 1 && f[u][v] < c[u][v]){
                int x = IncFlow(v, min(flow, c[u][v] - f[u][v]));
                if (x > 0){
                    f[u][v] += x;
                    f[v][u] -= x;
                    return x;
                }
            }
        visited[u] = 1;
        return 0;
    }
    int maxFlow(){
        int res = 0;
        while (FindPath()){
            for(int i = 0; i <= n + m + 1; i++)
                visited[i] = 0;
            while (1){
                int x = IncFlow(s, INF);
                res += x;
                if (x == 0)
                    break;
            }
        }
        return res;
    }
    void Solve(){
        BuildNetwork();
        int res = 0;
        for(int i = 1; i <= m; i++)
            res += profit[i];
        res -= maxFlow();
        cout << res << '\n';
        
        bool flag = 1;
        for(int i = 1; i <= m; i++)
            if (level[i] != -1){
                cout << i << ' ';
                flag = 0;
            }
        if (flag)
            cout << 0;
        cout << '\n';

        flag = 1;
        for(int i = 1; i <= n; i++)
            if (level[i + m] != -1){
                cout << i << ' ';
                flag = 0;
            }
        if (flag)
            cout << 0;
        cout << '\n';
    }
}

void ReadInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> m >> n;
    for(int i = 1; i <= m; i++)
        cin >> profit[i];
    for(int i = 1; i <= n; i++)
        cin >> cost[i];
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            cin >> a[i][j];
}


int main() {
    ReadInput();
    Dinitz::Solve();
    return 0;
}
