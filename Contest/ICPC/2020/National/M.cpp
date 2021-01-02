#include <bits/stdc++.h>

using namespace std;

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        long long h = abs(x1 - x2), w = abs(y1 - y2);
        long long res = min(h, w) * 2;
        long long dist = max(h, w) - min(h, w);
        res += dist + dist / 2 * 2;
        cout << res << endl;
    }
}
