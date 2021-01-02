#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair

const int N = 55;

int n;
pii a[N];

ll cross(pii A, pii B, pii C) {
    return  1ll * (B.fi - A.fi) * (C.se - A.se) -
            1ll * (B.se - A.se) * (C.fi - A.fi);
}

int check(vector<pii> pts) {
    vector<pii> hull;
    for (int i = 0; i < pts.size(); i++) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
    int s = hull.size();
    for (int i = pts.size() - 2; i >= 0; i--) {
        while (hull.size() >= s + 1 && cross(hull[hull.size() - 2], hull.back(), pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }
    hull.pop_back();
    return (int)(hull.size()) == 4;
}

int main() {
    while (1) {
        scanf("%d", &n);
        int res = 0;
        if (n == 0) break;
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &a[i].fi, &a[i].se);
        sort(a + 1, a + 1 + n);
        vector<pii> pts(4);
        for (int i0 = 1; i0 <= n; i0++) {
            pts[0] = a[i0];
            for (int i1 = i0 + 1; i1 <= n; i1++) {
                pts[1] = a[i1];
                for (int i2 = i1 + 1; i2 <= n; i2++) {
                    pts[2] = a[i2];
                    for (int i3 = i2 + 1; i3 <= n; i3++) {
                        pts[3] = a[i3];
                        res += check(pts);

                    }
                }
            }
        }
        printf("%d\n", res);
    }
}
