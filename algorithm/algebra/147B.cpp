#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}
#define fs first
#define sc second

const int N = 305;
const int INF = 0x3f3f3f3f;

struct Matrix {
    int n, m, d[N][N];
};
int n, m;
int a[N][N];
Matrix res, ret, tmp, c;

Matrix operator * (Matrix a, Matrix b) {
    REP(i, 0, n) REP(j, 0, n) {
        c.d[i][j] = -INF;
        REP(k, 0, n)
            c.d[i][j] = max(c.d[i][j], a.d[i][k] + b.d[k][j]);
    }
    return c;
}

Matrix operator ^ (Matrix a, int b) {
    bool foo = 1; tmp = a;
    while (b > 0) {
        if (b & 1) ret = foo ? tmp : ret * tmp, foo = 0;
        tmp = tmp * tmp;
        b >>= 1;
    }
    return ret;
}

void Read_Input() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    scanf("%d%d", &n, &m);
    memset(a, -INF, sizeof(a));
    REP(i, 0, n) a[i][i] = 0;
    REP(i, 0, m) {
        int u, v, x, y;
        scanf("%d%d%d%d", &u, &v, &x, &y);
        u--; v--;
        a[u][v] = x; a[v][u] = y;
    }
}

bool Check(int len) {
    REP(i, 0, n) REP(j, 0, n)
        res.d[i][j] = a[i][j];
    res = res ^ len;
    REP(i, 0, n) if (res.d[i][i] > 0) return 1;
    return 0;
}

void Solve() {
    int l = 2, h = n * 2, ans = 0;
    while (l <= h) {
        int mid = (l + h) >> 1;
        if (Check(mid)) {
            ans = mid;
            h = mid - 1;
        } else l = mid + 1;
    }
    printf("%d", ans);
}

int main() {
    Read_Input();
    Solve();
    return 0;
}
