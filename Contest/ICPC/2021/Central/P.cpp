#include <bits/stdc++.h>

using namespace std;

const int N = 101; 

long long g[11][N][N][N];

// pair<int, int> get(int x, int y, int z) { 
//     if (x <= y && x <= z) 
//         return {x, y * z}; 
//     if (y <= x && y <= z) 
//         return {y, x * z}; 
//     return {z, x * y}; 
// }

long long getG(int u, int x, int y, int z) { 
    if (x > y) swap(x, y); 
    if (x > z) swap(x, z); 
    if (y > z) swap(y, z); 
    return g[u][x][y][z]; 
}

int main() { 
    double t1 = clock(); 

    ios_base::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0); 
    memset(g, 0, sizeof(g)); 
    for (int u = 1; u <= 10; ++u) { 
        for (int i = 1; i < N; ++i) 
            for (int j = i; j < N; ++j) 
                for (int k = j; k < N; ++k) { 
                    // auto p = get(i, j, k); 
                    // if (p.first >= u) 
                    //     g[u][i][j][k] = p.second; 
                    if (i >= u)
                        g[u][i][j][k] = j * k;
                    for (int cut = u; cut <= min(i - 1, u * 2); ++cut) { 
                        if (i > cut) 
                            // g[u][i][j][k] = max(g[u][i][j][k], g[u][cut][j][k] + g[u][i - cut][j][k]); 
                            g[u][i][j][k] = max(g[u][i][j][k], getG(u, cut, j, k) + getG(u, i - cut, j, k)); 
                        if (j > cut)
                            // g[u][i][j][k] = max(g[u][i][j][k], g[u][i][cut][k] + g[u][i][j - cut][k]); 
                            g[u][i][j][k] = max(g[u][i][j][k], getG(u, i, cut, k) + getG(u, i, j - cut, k)); 
                        if (k > cut)
                            // g[u][i][j][k] = max(g[u][i][j][k], g[u][i][j][cut] + g[u][i][j][k - cut]); 
                            g[u][i][j][k] = max(g[u][i][j][k], getG(u, i, j, cut) + getG(u, i, j, k - cut)); 
                    }
                }
    }
    int tc; 
    cin >> tc; 
    while (tc--) { 
        int x, y, z, u; 
        cin >> x >> y >> z >> u; 
        // cout << x << " " << y << " " << z << " " << u << endl; 
        // cout << g[u][x][y][z] << endl; 
        cout << getG(u, x, y, z) << endl; 
    }

    cout << (clock() - t1) / CLOCKS_PER_SEC << endl; 

    return 0; 
}