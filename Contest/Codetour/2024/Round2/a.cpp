#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    vector<pair<int, long long>> a(n + 1);
    a[0].first = a[0].second = 0;
    for (int i = 1; i <= n; ++i) cin >> a[i].second >> a[i].first;
    sort(a.begin() + 1, a.end());
    for (int i = 1; i <= n; ++i) a[i].second += a[i - 1].second;
    while (q--) {
        int x; cin >> x;
        int l = 1, r = n;
        int res = 0;
        while (l <= r) {
            int mid = l + r >> 1;
            if (a[mid].first <= x) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << a[res].second << '\n';
    }
    return 0;
}