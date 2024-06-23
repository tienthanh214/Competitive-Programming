#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    sort(a.begin(), a.end());
    double ans = 0;
    for (int i = 1; i < n; ++i) {
        ans += sqrt(1 + (a[i] - a[i - 1]) * (a[i] - a[i - 1]));
    }
    cout << fixed << setprecision(6) << ans;
    return 0;
}