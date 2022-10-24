#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10; 

int n, k; 
pair<int, int> a[N]; 
long long f[11][N]; 
long long bit[11][N]; 

void update(int id, int x, long long value) { 
    for (; x <= n; x += x & -x) 
        bit[id][x] += value; 
}

long long get(int id, int x) { 
    long long ret = 0; 
    for (; x; x -= x & -x) 
        ret += bit[id][x]; 
    return ret; 
}

int main() { 
    ios_base::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 

    cin >> n >> k; 
    for (int i = 1; i <= n; ++i) { 
        cin >> a[i].first >> a[i].second; 
    }
    sort(a + 1, a + 1 + n); 
    int j = 1; 
    for (int i = 1; i <= n; ++i) { 
        while (j <= n && a[j].first < a[i].first) { 
            for (int i2 = 1; i2 <= 10; ++i2) { 
                update(i2, a[j].second, f[i2][j]);  
            }
            ++j; 
        }
        // cout << "first: " << i << " " << j << " " << get(1, 1) << endl; 
        f[1][i] = 1; 
        for (int i2 = 2; i2 <= 10; i2++) { 
            f[i2][i] = get(i2 - 1, a[i].second - 1);
            // cout << i2 << " " << i << " " << f[i2][i] << endl; 
        }
    }
    
    long long res = 0; 
    for (int i = 1; i <= n; ++i) 
        res += f[k][i]; 

    cout << res << endl; 


    return 0; 
}