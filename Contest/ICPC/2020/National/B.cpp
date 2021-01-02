#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair

const int N = 2e6 + 10;
const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int n, m;
vector<vector<int>> a, f;
int fr, top;
pii dq[N];

bool inside(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

int main() {
//    freopen("a.inp", "r", stdin);
//    freopen("a.out", "w", stdout);
    while (1) {
        scanf("%d%d\n", &n, &m);
        if (!n && !m) break;
        a.clear(); f.clear();
        a.resize(n, vector<int>(m, 0));
        f.resize(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char ch;
                do {
                    ch = getchar();
                } while (ch != '@' && ch != '.' && ch != '#');
                if (ch == '@') a[i][j] = 0;
                else if (ch == '#') a[i][j] = 1;
                else a[i][j] = 2;
            }
        }
        fr = (int)(1e6 + 1); top = (int)(1e6);
        for (int i = 1; i < m; i++) {
            if (!a[0][i]) continue;
            f[0][i] = a[0][i] - 1;
            if (!f[0][i]) dq[--fr] = mp(0, i);
            else dq[++top] = mp(0, i);
        }
        for (int i = 1; i < n - 1; i++) {
            if (!a[i][m - 1]) continue;
            f[i][m - 1] = a[i][m - 1] - 1;
            if (!f[i][m - 1]) dq[--fr] = mp(i, m - 1);
            else dq[++top] = mp(i, m - 1);
        }
        while (fr <= top) {
            pii coor = dq[fr++];
            for (int dir = 0; dir < 8; dir++) {
                pii newcoor = mp(coor.fi + dx[dir], coor.se + dy[dir]);
                if (!inside(newcoor.fi, newcoor.se)) continue;
                if (!a[newcoor.fi][newcoor.se]) continue;
                if (f[newcoor.fi][newcoor.se] != -1) continue;
                if (a[newcoor.fi][newcoor.se] == 1) {
                    f[newcoor.fi][newcoor.se] = f[coor.fi][coor.se];
                    dq[--fr] = newcoor;
                } else {
                    f[newcoor.fi][newcoor.se] = f[coor.fi][coor.se] + 1;
                    dq[++top] = newcoor;
                }
            }
        }
        int res = -1;
        if (a[0][0] == 2 || a[n - 1][m - 1] == 2) res = 1;
        if (a[0][0] == 1 || a[n - 1][m - 1] == 1) res = 0;
        for (int i = 0; i < n; i++) if (f[i][0] != -1) {
            if (res == -1 || res > f[i][0])
                res = f[i][0];
        }
        for (int i = 0; i < m; i++) if (f[n - 1][i] != -1) {
            if (res == -1 || res > f[n - 1][i])
                res = f[n - 1][i];
        }
        printf("%d\n", res);
    }
}
