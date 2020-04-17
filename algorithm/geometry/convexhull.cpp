#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}
#define fs first
#define sc second

typedef long long ll;
typedef pair <int, int> Point;

const int N = 1E5 + 10;

int n, k = 0;
Point a[N], P[N];

void Read_Input() {
    #ifdef LOCAL
        freopen("GEO.INP", "r", stdin);
    #endif // LOCAL
    scanf("%d", &n);
    FOR(i, 1, n) scanf("%d%d", &a[i].fs, &a[i].sc);
}

ll operator * (const Point &A, const Point &B) {
    return 1ll * A.fs * B.sc - 1ll * B.fs * A.sc;
}

Point operator - (const Point &A, const Point &B) {
    return Point(A.fs - B.fs, A.sc - B.sc);
}

int CCW(Point A, Point B, Point C) {
    ll s = (B - A) * (C - B);
    if (s > 0) return 1;
    if (s < 0) return -1;
    return 0;
}

void ConvexHull() {
    sort(a + 1, a + 1 + n);
    FOR(i, 1, n) {
        while (k >= 2 && CCW(P[k - 2], P[k - 1], a[i]) <= 0)
            k--;
        P[k++] = a[i];
    }
    int t = k + 1;
    FOD(i, n - 1, 1) {
        while (k >= t && CCW(P[k - 2], P[k - 1], a[i]) <= 0)
            k--;
        if (i > 1) P[k++] = a[i];
    }
}

bool Inside(Point X) { //check a point inside convex hull ?
    int l = 1, h = k - 1, m;
    if (CCW(P[0], P[l], X) < 0 || CCW(P[0], P[h], X) > 0)
        return 0;
    while (h - l > 1) {
        m = (l + h) >> 1;
        if (CCW(P[0], P[m], X) < 0) h = m;
            else l = m;
    }
    return CCW(P[l], P[h], X) >= 0;

}

void Solve() {
    int q; scanf("%d", &q);
    while (q--) {
        Point X; scanf("%d%d", &X.fs, &X.sc);
        if (Inside(X)) puts("YES");
            else puts("NO");
    }
}

int main() {
    Read_Input();
    ConvexHull();
    Solve();

    return 0;
}
