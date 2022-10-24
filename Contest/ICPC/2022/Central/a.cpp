#include <bits/stdc++.h>

using namespace std;

const int N = 333; 

int n, k; 
string str; 
int s[N][N]; 
int f[N][N][N]; 

int check(int type, int x, int y, int black0, int black1) { 
    // cout << type << " " << x << " " << y << " " << black << endl; 
    int &ret = f[x][y][black0]; 
    if (ret != -1) 
        return ret; 
    if (black0 >= k) { 
        ret = 1; 
        return ret; 
    }
    if (black1 >= k) { 
        ret = 0; 
        return ret; 
    }
    ret = !type; 
    if (check(!type, x + 1, y, black0 + (1 - type) * (str[x + 1] == 'B'), black1 + type * (str[x + 1] == 'B')) == type || 
        check(!type, x, y - 1, black0 + (1 - type) * (str[y - 1] == 'B'), black1 + type * (str[y - 1] == 'B')) == type)
            ret = type; 
    return ret; 
}

int main() {
    memset(f, -1, sizeof(f)); 
    cin >> n >> k; 
    cin >> str; 
    str = " " + str; 
    for (int i = 1; i <= n; ++i) { 
        s[i][n + 1] = str[i] == 'B'; 
        for (int j = n; j >= i; --j) { 
            s[i][j] = s[i][j + 1] + (str[j] == 'B'); 
        }
    }
    // 0: Quyen 
    // 1: Thang
    cout << (check(0, 0, n + 1, 0, 0) ? "NO" : "YES"); 
    // cout << check(1, 1, n + 1, 0) << endl; 

    return 0;
}