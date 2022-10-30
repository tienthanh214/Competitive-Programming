#include <bits/stdc++.h>

using namespace std;

long long getSum(long long x) { 
    if (x < 0) 
        return 0; 
    return x * (x + 1) / 2ll; 
}

int visited[2000][2000];
int f[2][2000][2000]; 

int Calc(int type, int x, int y){
    int &ret = f[type][x][y]; 
    if (ret != -1) 
        return ret; 
    if (visited[x][y]) { 
        ret = 2; 
        return ret; 
    }
    if (x % 2 && y % 2) {
        ret = !type; 
        return ret; 
    }
    // cout << type << " " << x << " " << y << " " << ret << endl;
    visited[x][y] = true; 
    if (x % 2 == 0 && Calc(!type, x / 2, y + x / 2) == type)
        return (ret = type); 
    // cout << type << " " << x << " " << y << " " << ret << endl;
    if (y % 2 == 0 && Calc(!type, x + y / 2, y / 2) == type)
        return (ret = type); 
    // cout << type << " " << x << " " << y << " " << ret << endl;
    if (x % 2 == 0 && Calc(!type, x / 2, y + x / 2) == 2)
        return (ret = 2); 
    if (y % 2 == 0 && Calc(!type, x + y / 2, y / 2) == 2)
        return (ret = 2); 
    return ret = !type; 
}

void clear(int n) { 
    for (int i = 1; i <= 2 * n; ++i) { 
        for (int j = 1; j <= 2 * n; ++j) { 
            visited[i][j] = 0; 
            f[0][i][j] = f[1][i][j] = -1; 
        }
    }
}

void solve(int n) { 
    int cnt[3] = {0, 0, 0}; 
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) { 
    //         // memset(visited, 0, sizeof(visited)); 
    //         // memset(f, -1, sizeof(f));
    //         clear(n);  
    //         // cout << i << " " << j << " " << Calc(0, i, j) << endl; 
    //         cout << Calc(0, i, j) << " "; 
    //         // if (i == n || j == n)
    //         cnt[Calc(0, i, j)]++; 
    //     }
    //     cout << endl; 
    // }
    for (int i = 1; (1 << i) <= n; ++i) {
        for (int j = 1; (1 << j) <= n; ++j) { 
            clear(n); 
            // cout << (1 << i) << " " << (1 << j) << " " << Calc(0, 1 << i, 1 << j) << endl; 
            cout << Calc(0, 1 << i, 1 << j) << " "; 
        }
        cout << endl; 
}
    // cout << n << ": " << cnt[0] << " " << cnt[2] << " " << cnt[1] << endl; 
    // cout << cnt[0] << endl; 
    // cout << cnt[2] << endl; 
    // cout << cnt[1] << endl; 
} 

int main() { 
    long long n; 
    cin >> n; 
    // cout << getSum(n / 2) << endl; 
    // cout << (n % 2 ? 0 : n) + getSum((n - 1) / 2) * 4 << endl; 
    // cout << 1ll * ((n + 1) / 2) * ((n + 1) / 2)  + getSum(n / 2 - 1) << endl;  

    long long ans[3];
    ans[0] = ans[1] = ans[2] = 0;
    int k = 0;
    int tmp = 1;
    while (tmp * 2 <= n){
        tmp *= 2;
        k++;
    }
    cout << k << endl;
    
    for (int i = 2; i <= k; i += 2){
        cnt[1] += (n / (1 << i)) * (n / (1 << i));
    }
    for (int i = 1; i <= k; i += 2){
        cnt[0] += (k - i + 1) * 
    }
    for (int i = n; i <= n; ++i) 
        solve(i); 
    // int cnt[3] = {0, 0, 0}; 
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = 1; j <= n; ++j) { 
    //         // memset(visited, 0, sizeof(visited)); 
    //         // memset(f, -1, sizeof(f));
    //         clear(n);  
    //         cout << i << " " << j << " " << Calc(0, i, j) << endl; 
    //         // if (i == n || j == n)
    //             cnt[Calc(0, i, j)]++; 
    //     }
    // }
    // cout << cnt[0] << endl; 
    // cout << cnt[2] << endl; 
    // cout << cnt[1] << endl; 

    // for (int i = 1; i <= n; i += 2)
    // for (int j = 1; j <= n; j += 2) f[i][j] = 2;

    // long long even = n / 2;
    // long long odd = n - even;
    // cout << endl;
    // cout << dp
    // cout << even * odd * 2 << endl;
    return 0; 
}