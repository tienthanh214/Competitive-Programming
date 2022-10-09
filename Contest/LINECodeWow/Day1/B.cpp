#include <bits/stdc++.h>

using namespace  std;

const int N = 1e5 + 10;

typedef pair<int, int> ii;

int n;
ii a[N];

bool comp(ii x, ii y) {
    return x.first < y.first;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    #endif // LOCAL
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &a[i].second, &a[i].first);
    }
    sort(a, a + n);
    // for (int i = 0; i < n; ++i) cout << a[i].first << " " << a[i].second << endl;
    int pos;
    while (scanf("%d", &pos) == 1) {
        // cout << pos << endl;
        int x = lower_bound(a, a + n, ii(pos, -1)) - a;
        int y = upper_bound(a, a + n, ii(pos, -1)) - a - 1;
        if (!(0 <= x && x < n)) x = 0;
        if (!(0 <= y && y < n)) y = 0;
        if (abs(a[x].first - pos) < abs(a[y].first - pos)) {
            printf("%d\n", a[x].second);
        } else if (abs(a[x].first - pos) > abs(a[y].first - pos)) {
            printf("%d\n", a[y].second);
        } else {
            printf("%d\n", min(a[x].second, a[y].second));
        }
    }
    return 0;
}
