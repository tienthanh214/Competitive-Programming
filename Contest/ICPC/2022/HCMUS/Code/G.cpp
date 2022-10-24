#include <bits/stdc++.h>

using namespace std;

const int N = 200; 
const int MOD = 1e9 + 7; 

struct matrix2D { 
    int n; 
    int a[N][N]; 

    matrix2D(int _n = 0) { 
        n = _n; 
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < n; ++j) 
                a[i][j] = 0; 
    }

    void setN(int _n = 0) { 
        n = _n; 
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < n; ++j) 
                a[i][j] = 0; 
    }

    matrix2D mul(matrix2D m1, matrix2D m2) { 
        matrix2D ret(m1.n); 
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < n; ++j) 
                for (int k = 0; k < n; ++k)  
                    ret.a[i][j] = (ret.a[i][j] + 1ll * m1.a[i][k] * m2.a[k][j] % MOD) % MOD; 
        return ret; 
    }

    matrix2D Pow(int x) {
        if (x == 1) 
            return (*this); 
        matrix2D ret = (*this).Pow(x / 2); 
        ret = mul(ret, ret); 
        if (x % 2) 
            ret = mul(ret, *this); 
        return ret; 
    }
};

int n, m; 
matrix2D matrix; 

void solve() {
    int al = 131; 
    matrix.setN(al); 
    for (int i = 0; i < 26; ++i) { 
        for (int j = 0; j < 26; ++j) { 
            matrix.a[i * 5][j * 5] = 1; 
        }
        for (int j = 1; j < 5; ++j) { 
            matrix.a[i * 5 + j - 1][i * 5 + j] = 1;
        }
        matrix.a[i * 5][al - 1] = 1; 
    }
    matrix.a[al - 1][al - 1] = 1;
    cin >> n >> m; 
    for (int i = 0; i < m; ++i) { 
        char x, y; 
        int value; 
        cin >> x >> y >> value; 
        if (value == 1) 
            continue; 
        x -= 'a'; y -= 'a'; 
        matrix.a[x * 5][y * 5] = 0;
        matrix.a[x * 5 + value - 1][y * 5] = 1;
        matrix.a[y * 5][x * 5] = 0;
        matrix.a[y * 5 + value - 1][x * 5] = 1;
    }
    matrix = matrix.Pow(n + 1); 
    int res = 0; 
    for (int i = 0; i < 26; ++i) 
        res = (res + matrix.a[i * 5][al - 1]) % MOD; 
    cout << res << endl; 
    // cout << matrix.a[0][al - 1] << " " << matrix.a[1][al - 1] << endl; 
}   

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int testCase = 1;
    // cin >> testCase;
    while (testCase--) {
        solve();
    }

    return 0;
}