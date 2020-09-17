#include <bits/stdc++.h>

using namespace std;

int a, b, c;

int ExtendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int x1, y1;
    int gcd = ExtendedGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    freopen("math.inp", "r", stdin);
    freopen("math.out", "w", stdout);
    cin >> a >> b;
    int x, y;
    int g = ExtendedGCD(a, b, x, y);
    cout << g << " " << x << " " << y;
    return 0;
}
