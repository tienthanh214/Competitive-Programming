#include <bits/stdc++.h>

using namespace std;

int main() {
    int TC; scanf("%d", &TC);
    while (TC--) {
        int V; scanf("%d", &V);
        double h = cbrt(4 * V / acos(-1));
        double r = h / 2;
        cout << fixed << setprecision(6) << 2 * acos(-1) * (r * r + r * h) << '\n';
    }
   return 0;
}
