#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef long double ld;

const int N = 1e5 + 10;

int n, a[N];
LL T[N], S[N];

struct Line {
    LL a, b;
    Line (LL _a = 0, LL _b = 0) : a(_a), b(_b) {}
};

struct Hull {
    vector <Line> p;
    int head, tail;

    void Init() {
        tail = 0; head = 1;
    }
    bool Check(Line l1, Line l2, Line l3) {
        return ld(l3.b - l1.b) / (l1.a - l3.a)
                > ld(l2.b - l1.b) / (l1.a - l2.a);
        return (l3.b - l1.b) * (l1.a - l2.a)
             > (l2.b - l1.b) * (l1.a - l3.a);
    }
    void Update(Line l) {
        while (p.size() > 1 && Check(p[tail - 2], p[tail - 1], l))
            p.pop_back(), tail--;
        p.push_back(l); tail++;
    }
    LL F(int m, LL x) {
        return p[m].a * x + p[m].b;
    }
    LL Query(LL x) {
        int l = 0, h = p.size() - 1, m;
        while (l < h) {
            m = (l + h) >> 1;
            if (F(m, x) <= F(m + 1, x)) l = m + 1;
                else h = m;
        }
        return F(l, x);
    }
} Hull;

void readInput() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    reverse(a + 1, a + 1 + n);
    for (int i = 1; i <= n; ++i) {
        T[i] = T[i - 1] + 1ll * i * a[i];
        S[i] = S[i - 1] + a[i];
    }
}

void solve() {
    // T(r) - T(l - 1) - (l - 1) * S(r) + (l - 1) * S(l - 1)
    // T(r) + (-S(r) * x - T(x) + x * S(x))
    LL ans = -1e18;
    for (int i = 1; i <= n; ++i) {
        Hull.Update(Line(-(i - 1), -T[i - 1] + 1ll * (i - 1) * S[i - 1]));
        ans = max(ans, T[i] + (Hull.Query(S[i])));
    }
    printf("%lld", ans);
}

int main() {
    readInput();
    solve();
    return 0;
}
