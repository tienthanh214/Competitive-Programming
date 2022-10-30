#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10 ;

int n; 
int f[N][2]; 
string s[3]; 

void solve() { 
    cin >> s[0] >> s[1] >> s[2]; 
    for (int i = 0; i < 3; ++i)
        reverse(s[i].begin(), s[i].end());
    for (int i = 0; i <= n; ++i) 
        // f[0][i] = f[1][i] = (int)(1e9);
        f[i][0] = f[i][1] = int(1e9); 
    f[0][0] = 0; 
    for (int i = 0; i < n; ++i) { 
        for (int j = 0; j < 2; ++j) { 
            if (f[i][j] == (int)(1e9)) 
                continue; 
            int a = s[0][i] - '0', 
                b = s[1][i] - '0', 
                c = s[2][i] - '0'; 
            if ((a + b + j) % 10 == c) 
                f[i + 1][(a + b + j) / 10] = min(f[i + 1][(a + b + j) / 10], f[i][j]);  
            f[i + 1][j] = min(f[i + 1][j], f[i][j] + 1); 
            // if (i + 1 == 4) 
            //     cout << i << " " << j << " " << f[i][j] << endl; 
        }
    }
    int res = n; 
    for (int i = 1; i <= n; ++i) { 
        // cout << i << " " << f[i][0] << " " << f[i][1] << endl; 
        res = min(res, f[i][0] + n - i); 
    }
    cout << res << endl; 
}

int main() { 
    while (true) { 
        cin >> n; 
        if (n == 0) 
            break; 
        solve(); 
    }

    return 0; 
}