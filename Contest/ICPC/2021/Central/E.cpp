#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> ii;

vector<ii> p;

LL cross(const ii &a, const ii &b) {
    return a.first * b.second - a.second * b.first;
}

LL area(ii a, ii b, ii c) {
    return cross(a, b) + cross(b, c) + cross(c, a);
}

vector<ii> convexHull(vector<ii> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    vector<ii> up, down;
    for (int i = 0; i < p.size(); ++i) {
        while (up.size() > 1 && area(up[up.size() - 2], up[up.size() - 1], p[i]) >= 0)
            up.pop_back();
        while (down.size() > 1 && area(down[down.size() - 2], down[down.size() - 1], p[i]) <= 0)
            down.pop_back();
        up.push_back(p[i]);
        down.push_back(p[i]);
    }
    vector<ii> hull = down;
    for (int i = up.size() - 2; i >= 1; --i)
        hull.push_back(up[i]);
    return hull;
}

bool check() {
    return convexHull(p).size() == 4;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int TC; cin >> TC;
    while (TC--) {
        p.clear();
        for (int i = 0; i < 4; ++i) {
            int x, y;
            cin >> x >> y;
            p.push_back({x, y});
        }
        cout << (check() ? "YES" : "NO") << '\n';
    }
    return 0;
}