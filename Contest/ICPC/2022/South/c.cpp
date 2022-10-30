#include <bits/stdc++.h>

using namespace std;

const int N = 5005; 

int n, k;
long long sSquare[N], sSecond[N]; 
long long g[N][N], f[N][N];  
int opt[N][N]; 
pair<int, int> a[N]; 

long long costL(int l, int r) { 
    if (l > r) 
        return 0; 
    // cout << l << " " << r << " " << (sSquare[r] - sSquare[l - 1]) << " " << 1ll * a[l].first * (sSecond[r] - sSecond[l - 1]) << endl; 
    return (sSquare[r] - sSquare[l - 1]) - 1ll * a[l].first * (sSecond[r] - sSecond[l - 1]); 
}

long long costR(int l, int r) { 
    if (l > r) 
        return 0; 
    // cout << l << " " << r << " " << (sSquare[r] - sSquare[l - 1]) << " " << 1ll * a[l].first * (sSecond[r] - sSecond[l - 1]) << endl; 
    return 1ll * a[r].first * (sSecond[r] - sSecond[l - 1]) - (sSquare[r] - sSquare[l - 1]); 
}

int main() {
    cin >> n >> k; 
    for (int i = 1; i <= n; ++i) 
        cin >> a[i].first >> a[i].second; 
    sort(a + 1, a + 1 + n); 
    a[0] = {-1e7, -1}; 
    sSquare[0] = sSecond[0] = 0; 
    for (int i = 1; i <= n; ++i) { 
        sSquare[i] = sSquare[i - 1] + 1ll * a[i].first * a[i].second; 
        sSecond[i] = sSecond[i - 1] + a[i].second; 
    }
    // for (int i = 1; i <= n; ++i) 
    //     for (int j = i; j <= n; ++j) 
    //         cout << i << " " << j << " " << costL(i, j) << " " << costR(i, j) << endl; 
    for (int i = 1; i <= n; ++i) { 
        for (int j = i, j2 = i; j <= n; ++j) { 
            while (j2 <= j && a[j2].first - a[i - 1].first < a[j].first - a[j2].first)     
                ++j2; 
            g[i][j] = (i > 1 ? costL(i - 1, j2 - 1) : 0) + costR(j2, j); 
            // cout << i << " " << j << " " << j2 << " " << g[i][j] << endl; 
        }
    }

    memset(f, 60, sizeof(f)); 
    f[0][0] = 0; 
    for (int i = 0; i <= n; ++i) { 
        opt[0][i] = 1; 
    }
    long long res = (long long)(1e18); 
    for (int ii = 1; ii <= k; ++ii) { 
        f[ii][0] = 0; 
        opt[ii][0] = 1; 
        opt[ii][n + 1] = n; 
        for (int i = n; i >= 1; --i) { 
            for (int j = opt[ii - 1][i]; j <= opt[ii][i + 1]; ++j) { 
                long long val = f[ii - 1][j - 1] + g[j][i]; 
                if (val < f[ii][i]) { 
                    f[ii][i] = val; 
                    opt[ii][i] = j; 
                }
            }
            // cout << ii << " " << i << " " << f[ii][i] << " " << opt[ii][i] << endl; 
            res = min(res, f[ii][i] + costL(i, n)) ; 
        }
    }

    cout << res << endl; 

    return 0; 
}