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

int f[N]; 

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
         if (u < 0 || u > n || v < 0 || v > n) 
            assert(false);
        DSU.join(u, v);
    }
    //cerr << result << endl;

    for (int i = 1; i <= n; ++i) {
        lst[DSU.findRoot(i)].push_back(a[i]);
    }

    for (int i = 1; i <= n; ++i) { 
        sort(lst[i].begin(), lst[i].end(), greater<int>()); 
    }

    int res = 0;
    for (int i = 1; i <= n; ++i) { 
        int j = res + 1; 
        int root = DSU.findRoot(i);
        assert(1 <= root && root <= n);  
        // for (int x: lst[root]) { 
        for (int ii = 0; ii < lst[root].size(); ++ii) {  
            int x = lst[root][ii]; 
            // cout << i << " " << x << " " << j << " " << f[j - 1] << endl; 
            while (j > 1 && f[j - 1] >= x) 
                --j; 
            f[j] = x; 
            res = max(res, j); 
        }
        // cout << i << " " << f[1] << endl; 
    }
    cout << res << endl; 

    return 0;
}

