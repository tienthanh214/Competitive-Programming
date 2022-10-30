#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10; 

int n, m, res = 0; 
int a[N], f[N]; 
int par[N]; 
vector<int> idx[N]; 

int root(int u) { 
    return par[u] < 0 ? u : (par[u] = root(par[u])); 
}

bool join(int u, int v) { 
    if ((u = root(u)) == (v = root(v))) 
        return false; 
    if (par[u] > par[v]) 
        swap(u, v); 
    par[u] += par[v]; 
    par[v] = u; 
    return true; 
}

int main() { 
    memset(par, -1, sizeof(par)); 
    cin >> n >> m; 
    for (int i = 1; i <= n; ++i) 
        cin >> a[i]; 
    for (int i = 1; i <= m; ++i) { 
        int x, y; 
        cin >> x >> y; 
        if (x < 0 || x > n || y < 0 || y > n) 
            continue; 
        join(x, y); 
    }
    for (int i = 1; i <= n; ++i) 
        idx[root(i)].push_back(i); 
    for (int i = 1; i <= n; ++i) 
        if (par[i] < 0) { 
            assert(idx[i].size() != 0); 
            vector<int> val; 
            for (int x: idx[i]) 
                val.push_back(a[x]); 
            sort(val.begin(), val.end()); 
            for (int j = 0; j < val.size(); ++j) 
                a[idx[i][j]] = val[j]; 
        }
    for (int i = 1; i <= n; ++i) { 
        int id = lower_bound(f + 1, f + 1 + res, a[i]) - f; 
        f[id] = a[i]; 
        res = max(res, id); 
    }
    cout << res << endl; 

    return 0; 
}