#include <stdio.h>
#include <cmath>
#include <algorithm>

using namespace std;

int xA, xB, yA, yB, v1, v2;

double Dist(double x, double y, double u, double v) {
    return sqrt((x - u) * (x - u) + (y - v) * (y - v));
}

double F(double x) {
    return Dist(xA, yA, x, 0) / (1.0 * v1) + Dist(x, 0, xB, yB) / (1.0 * v2);
}

double TernarySearch() {
    double l = min(xA, xB), r = max(xA, xB);
    for (int timer = 1; timer <= 100; timer++) {
        double m1 = l + (r - l) / 3.0;
        double m2 = r - (r - l) / 3.0;
        if (F(m1) < F(m2)) r = m2;
            else l = m1;
    }
    return F(l);
}

int main() {
    int TC; scanf("%d", &TC);
    while (TC--) {
        scanf("%d%d%d%d%d%d", &xA, &yA, &xB, &yB, &v1, &v2);
        printf("%.5f\n", TernarySearch());
    }
    return 0;
}
