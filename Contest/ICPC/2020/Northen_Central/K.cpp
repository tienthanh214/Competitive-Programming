#include <bits/stdc++.h>

using namespace std;

template<typename T> void Read(T &n) {
    char c; n = 0;
    while (!isdigit(c = getchar()));
    do {
        n = n * 10 + c - '0';
    } while (isdigit(c = getchar()));
}

template<> void Read<string>(string &n) {
    n.clear(); char c;
    while (!isalnum(c = getchar()));
    do {
        n += c;
    } while (isalnum(c = getchar()));
}

template<typename T> void Writeln(T n) {
    if (n == 0) {
        puts("0");
        return;
    }
    char c[20];
    int k = 0;
    while (n > 0) {
        c[k++] = n % 10 + '0';
        n /= 10;
    }
    for (int i = k - 1; i >= 0; --i)
        putchar(c[i]);
    putchar('\n');
}

const int N = 305;

struct Edge {
    int u, v, cap, flow;
    Edge(int _u = 0, int _v = 0, int _cap = 0, int _flow = 0) {
        u = _u; v = _v; cap = _cap; flow = _flow;
    }
};

int n, m, k, l;
unordered_map<string, int> mp1, mp2;
int c[N][N], f[N][N];
//vector<int> adj[N];

void addEdge(int u, int v, int cap) {
    c[u][v] += cap;
//    adj[u].push_back(edge.size());
//    edge.push_back(Edge(u, v, cap, 0));
//    adj[v].push_back(edge.size());
//    edge.push_back(Edge(v, u, 0, 0));
}

void readInput() {
  //  string s1, s2;
    mp1.clear(); mp2.clear();
    Read(n); Read(m); Read(k); Read(l);
    for (int i = 0; i <= n + m + k + 1; ++i) {
        //adj[i].clear();
        for (int j = 0; j <= n +  m + k + 1; ++j)
            c[i][j] = f[i][j] = 0;
    }
    //cerr << l << endl;
    string s1, s2;
    for (int i = 0; i < l; ++i) {
        int A; //string s1, s2;
        Read(A);
        Read(s1); Read(s2);
        if (!mp1.count(s1)) mp1[s1] = mp1.size();
        if (!mp2.count(s2)) mp2[s2] = mp2.size();
        int u = mp1[s1], v = mp2[s2];
        addEdge(u, A + m, 1);
        addEdge(A + m, v + m + n , 1);
    }

    for (int i = 1; i <= m; ++i)
        addEdge(0, i, 1);
    for (int i = 1; i <= k; ++i)
        addEdge(i + m + n, m + n + k + 1, 1);
}

bool visit[N];
int d[N];

bool findPath(int s, int t) {
    queue<int> Q;
    for (int i = 0; i <= n + m + k + 1; ++i)
        d[i] = 0;
    d[s] = 1; Q.push(s);
    while (Q.size()) {
        int u = Q.front(); Q.pop();
        if (u == t) return true;
        for (int v = 0; v <= n + m + k + 1; ++v) {
            if (d[v] != 0) continue;
            if (c[u][v] - f[u][v] <= 0) continue;
            d[v] = d[u] + 1;
            Q.push(v);
        }
    }
    return false;
}

int incFlow(int u, int t, int flow) {
    visit[u] = true;
    if (u == t) return flow;
    for (int v = 0; v <= n + m + k + 1; ++v)
        if (c[u][v] - f[u][v] > 0 && d[v] == d[u] + 1 && !visit[v]) {
            int x = incFlow(v, t, min(flow, c[u][v] - f[u][v]));
            if (x > 0) {
                f[u][v] += x;
                f[v][u] -= x;
                return x;
            }
        }
    return 0;
}

void solve() {
    int maxFlow = 0;
    while (findPath(0, n + m + k + 1)) {
        int x;
        memset(visit, false, sizeof(visit));
        while (x = incFlow(0, n + m + k + 1, 1e9)) {
            maxFlow += x;
            memset(visit, false, sizeof(visit));
        }
    }
    //Writeln(maxFlow);
    //cout << maxFlow << "\n";
    printf("%d\n", maxFlow);
}

void gen() {
    srand(time(0));
    freopen("input.txt", "w", stdout);
    cout << 1 << endl;
    n = 100; m = 100; k = 100; l = 1e6;
    cout << n << " " << m << " " << k << " " << l << endl;
    map<int, string> mp1, mp2;
    for (int i = 1; i <= 100; ++i) {
        string u, v;
        for (int j = 1; j <= 20; ++j) {
            u += rand() % 26 + 'a';
            v += rand() % 26 + 'a';
        }
        mp1[mp1.size()] = u;
        mp2[mp2.size()] = v;
    }
    //for (auto it : mp1) cerr << it.first << "  " << it.second << endl;
    for (int i = 1; i <= l; ++i) {
        string u = mp1[rand() % 100], v = mp2[rand() % 100];

        cout << rand() % 100 + 1 << " " << u << " " << v << endl;
    }
}


int main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0); cout.tie(0);

    //gen(); return 0;
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL

    int TC; Read(TC);
    while (TC--) {
        readInput();
        solve();
    }
    return 0;
}
