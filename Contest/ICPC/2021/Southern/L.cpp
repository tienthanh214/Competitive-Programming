#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10; 

int n, m; 
int a[N]; 
int nxt[2][N]; 
long long sum = 0; 
long long f[N]; 
string cmd; 

int main() { 
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) { 
        scanf("%d", &a[i]); 
        sum += a[i]; 
    }
    cin >> cmd; 
    m = cmd.size(); 
    nxt[0][m + 1] = nxt[1][m + 1] = m + 1; 
    for (int i = m; i >= 1; --i) { 
        nxt[0][i] = nxt[0][i + 1]; 
        nxt[1][i] = nxt[1][i + 1]; 
        nxt[cmd[i - 1] - '0'][i] = i; 
        // cout << nxt[0][i] << " " << nxt[1][i] << endl; 
    }
    
    memset(f, 0, sizeof(f)); 
    for (int i = 1; i <= n; ++i) { 
        int j = 1; 
        while (a[i] > 0) { 
            if (a[i] % 2) { 
                j = nxt[1][j]; 
                if (j > m) 
                    break; 
                    // cout << i << " " << j << " " << 0 << endl; 
                f[j]++; 
                a[i]--; 
                j++; 
            } else { 
                j = nxt[0][j]; 
                if (j > m) 
                    break; 
                    // cout << i << " " << j << " " << 1 << endl; 
                f[j] += a[i] / 2; 
                a[i] /= 2; 
                j++; 
            }
        }
    }
    for (int i = 1; i <= m; ++i) { 
        f[i] += f[i - 1]; 
        printf("%lld\n", sum - f[i]); 
    }


    return 0; 
}