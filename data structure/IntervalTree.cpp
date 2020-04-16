#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef long long LL;

int n, m;

namespace myIntervalTree {
    static const int N = 2E5 + 10;
    static const LL INF = 1E18;

    struct Line {
        LL a, b;
        Line (LL _a = 0, LL _b = 0) : a(_a), b(_b) {};
        LL Get(int x) {
            return a * x + b;
        }
    };

    struct IntervalTree {
        Line It[N * 4]; //manager max 1 -> n
        void Update(int id, int l, int r, int u, int v, Line val) {
            if (v < l || r < u || l > r) return;
            int mid = (l + r) >> 1;
            if (u <= l && r <= v) {
                Line A = It[id], B = val;
                if (A.Get(l) > B.Get(l)) swap(A, B);
                if (A.Get(r) <= B.Get(r)) It[id] = B;
                    else {
                        if (A.Get(mid) > B.Get(mid)) {
                            It[id] = A;
                            Update(id << 1, l, mid, u, v, B);
                        } else {
                            It[id] = B;
                            Update(id << 1 | 1, mid + 1, r, u, v, A);
                        }
                    }
            } else {
                Update(id << 1, l, mid, u, v, val);
                Update(id << 1 | 1, mid + 1, r, u, v, val);
            }
        }
        LL Query(int id, int l, int r, int pos) {
            if (pos < l || r < pos || l > r) return -INF;
            LL res = It[id].Get(pos);
            if (l == r) return res;
            int mid = (l + r) >> 1;
            return max(res, max(Query(id << 1, l, mid, pos), Query(id << 1 | 1, mid + 1, r, pos)));
        }
        void Update(int u, int v, Line val) { //update line val x = [u..v]
            Update(1, 1, n, 1, n, val);
        }
        LL Query(int pos) { // maximum at x = pos
            return Query(1, 1, n, pos);
        }
    };
}

using namespace myIntervalTree;

int main() {
    IntervalTree IT;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int s, e, v, d;
        scanf("%d%d", &d, &v); // y = dx + v
        Line val = Line(d, v);
        IT.Update(1, n, val);
    }
    for (int i = 1; i <= n; i++) printf("%lld\n", IT.Query(i));
    return 0;
}
