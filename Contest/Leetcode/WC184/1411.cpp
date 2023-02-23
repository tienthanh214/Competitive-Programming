class Solution {
public:
    typedef long long LL;
    static const int base = 1e9 + 7;
    int f[5005][4][4][4];
    int numOfWays(int n) {
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int x = 1; x <= 3; x++)
                for (int y = 1; y <= 3; y++)
                    for (int z = 1; z <= 3; z++) {
                        f[i][x][y][z] = 0;
                        if (x == y || y == z) continue;
                        if (i == 1) f[i][x][y][z] = 1;
                        for (int a = 1; a <= 3; a++)
                            for (int b = 1; b <= 3; b++)
                                for (int c = 1; c <= 3; c++)
                                    if (a != x && b != y && c != z)
                                        f[i][x][y][z] = (f[i][x][y][z] + f[i - 1][a][b][c]) % base;
                        
                        if (i == n) ans = (ans + f[n][x][y][z]) % base;
                    }
        }
        
        
        return ans;
    }
};