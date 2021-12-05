#include <bits/stdc++.h>

using namespace std;

double A, H;

double f1(double x) {
    return (H - x) * 6 * A * x / H;
}

double f2(double x) {
    return (H - x) * ((6 * (100 - A) * x / H) - (100 - 2*A));
}

int main() {
    double ans = 0;
    cin >> A >> H;
    // [H/3 -> H]
    ans = (H - H/3) * 100;
    // [0 -> H/6]
    ans = max(ans, f1(H/6));
    // [H/6 -> H/3]
    double x = (700 - 8 * A) * H / (1200 - 12 * A);
    ans = max(ans, max(f2(H/6), f2(H/3)));
    if (H/6 <= x && x <= H/3)
        ans = max(ans, f2(x));
    cout << fixed << setprecision(8) << ans;    
    return 0;
}