#include <iostream>
#include <cstring>

using namespace std;

int maximize(int r1, int s1, int p1, int r2, int s2, int p2) {
    int a = min(r1, s2);
    int b = min(s1, p2);
    int c = min(p1, r2);
    int p = a + b + c;
    r1 -= a; s2 -= a;
    s1 -= b; p2 -= b;
    p1 -= c; r2 -= c;
    a = min(r1, r2);
    b = min(s1, s2);
    c = min(p1, p2);
    r1 -= a; r2 -= a;
    s1 -= b; s2 -= b;
    p1 -= c; p2 -= c;
    return p - r2 - s2 - p2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n;
    int x[2][3];
    memset(x, 0, sizeof(x));
    cin >> n;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < n; ++j) {
            string v; cin >> v;
            if (v == "R") x[i][0]++;
            if (v == "S") x[i][1]++;
            if (v == "P") x[i][2]++;
        }
    }
    // cout << minimize(a1, b1, c1, a2, b2, c2) << " ";
    int res = maximize(x[0][0], x[0][1], x[0][2], x[1][0], x[1][1], x[1][2]);
    // res -= maximize(x[1][0], x[1][1], x[1][2], x[0][0], x[0][1], x[0][2]);
    cout << res;
    return 0;
}