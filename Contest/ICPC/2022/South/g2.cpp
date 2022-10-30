#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, m, a[N];

struct DSU {
    int Root[N], Ranked[N];
    void Init(int __n){
        for (int i = 1; i <= n; i++) {
            Root[i] = i;
            Ranked[i] = 1;
        }
    }

    int findRoot(int u) { 
        if (Root[u] == u) return u;
        return Root[u] = findRoot(Root[u]);
    }

    bool join(int u, int v) { 
        u = findRoot(u);
        v = findRoot(v);
        if (u == v) return false;
        if (Ranked[u] > Ranked[v]) swap(u, v);
        Ranked[v] += Ranked[u];
        Root[u] = v;
        return true;
    }
} DSU;

struct FenwickTree {
    int ft[N];
    void Init(){
        for (int i = 0; i < N; i++) ft[i] = 0;
    }

    void Update(int i, int val) {
        assert(i != 0);
        for (; i <= n; i += i & -i)
            ft[i] = max(ft[i], val);
    }

    int getMax(int i) {
        int ret = 0;
        for (; i > 0; i -= i & -i)
            ret = max(ret, ft[i]);
        return ret;
    }
} FT;

vector<int> lst[N];

int getLIS() {
    FT.Init();
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int maxF = FT.getMax(a[i]) + 1;
        ans = max(ans, maxF);
        FT.Update(a[i], maxF);
    }
    return ans;
}

int main() {
    // if (fopen("input.txt", "r"))
    //     freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int result = 0;

    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    //cerr << "huhu" << endl;

    result = getLIS();
    //cerr << result << endl;
    // swap
    DSU.Init(n);
    for (int i = 1; i <= m; ++i) {
        int u, v; cin >> u >> v;
        DSU.join(u, v);
    }
    //cerr << result << endl;

    for (int i = 1; i <= n; ++i) {
        lst[DSU.findRoot(i)].push_back(a[i]);
    }

    for (int i = 1; i <= n; ++i) {
        if (lst[i].empty()) continue;
        sort(lst[i].begin(), lst[i].end(), greater<int>());
    }
    //cerr << result << endl;

    for (int i = 1; i <= n; ++i) {
        int p = DSU.findRoot(i);
        assert(lst[p].size() > 0);
        a[i] = lst[p].back();
        lst[p].pop_back();
    }
    //cerr << result << endl;

    // for (int i = 1; i <= n; ++i) cout << a[i] << ' ';
    result = max(result, getLIS());


    cout << result << endl;
    //cout << result << endl;
    return 0;
}
