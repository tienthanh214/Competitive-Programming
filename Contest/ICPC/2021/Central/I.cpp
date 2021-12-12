#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> ii;

const int MAX_N = 2505 * 2;

int n;
struct Rect {
    LL x, y, w, h;

    Rect(int _x = 0, int _y = 0, int _w = 0, int _h = 0): 
        x(_x), y(_y), w(_w), h(_h) {};

    Rect rotate() {
        return Rect(x, y, h, w);
    }

    bool isIntersect(const Rect &other) {
        LL x0 = max(2 * x - w, 2 * other.x - other.w);
        LL y0 = max(2 * y - h, 2 * other.y - other.h);
        LL x1 = min(2 * x + w, 2 * other.x + other.w);
        LL y1 = min(2 * y + h, 2 * other.y + other.h);
        // cout << x0 /2.0 << " " << y0/2.0 << " " << x1/2.0 << " " << y1/2.0 << endl;
        return (x0 < x1 && y0 < y1);
    }
} rect[MAX_N];

vector<ii> conflict;

void readInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y, w, h;
        cin >> x >> y >> w >> h;
        rect[i] = Rect(x, y, w, h);
    }
}

void buildConflict() {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int ro0 = 0; ro0 <= 1; ++ro0) {
                for (int ro1 = 0; ro1 <= 1; ++ro1) {
                    Rect a = rect[i];
                    Rect b = rect[j];
                    if (ro0) a = a.rotate();
                    if (ro1) b = b.rotate();
                    if (a.isIntersect(b)) {
                        conflict.push_back({i * 2 + ro0, j * 2 + ro1});
                    }
                }
            }
        }
    }
}

vector<int> g[MAX_N];
int timer = 0;
int low[MAX_N], num[MAX_N];
stack<int> S;
int col[MAX_N];
bool invalid = false;

void setColor(int u, int x) {
    if (col[u] == -x || col[u ^ 1] == x)
        invalid = true;
    else {
        col[u] = x;
        col[u ^ 1] = -x;
    }
}

void DFS(int u) {
    low[u] = num[u] = ++timer;
    S.push(u);
    for (int v : g[u]) {
        if (!num[v]) {
            DFS(v);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], num[v]);
        }
        if (col[u] == -1) 
            setColor(u, -1); 
    }
    if (low[u] == num[u]) {
        if (col[u] == 0) 
            setColor(u, 1);
        int x = 0;
        do {
            x = S.top(); S.pop();
            setColor(x, col[u]);
            low[x] = num[x] = 1e9;
        } while (x != u);
    }
}

void solve() {
    for (auto [x, y] : conflict) {
        g[x].push_back(y ^ 1);
        g[y].push_back(x ^ 1);
    }
    for (int i = 0; i < 2 * n; ++i)
        sort(g[i].begin(), g[i].end());
    timer = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (!num[i]) {
            DFS(i);
        }
    }
    for (int i = 0; i < 2 * n; ++i)
        if (col[i] == col[i ^ 1])
            invalid = true;
    
    if (invalid) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        for (int i = 0; i < n; ++i) {
            if (col[2 * i] == 1) {
                cout << 'K';
            } else {
                cout << 'Q';
            }
        }
    }    
}

int main() {
    readInput();
    buildConflict();
    solve();
    return 0;
}