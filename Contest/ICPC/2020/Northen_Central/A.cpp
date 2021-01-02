#include <bits/stdc++.h>

using namespace std;

int main() {
    int TC; scanf("%d", &TC);
    while (TC--) {
        int n, k;
        scanf("%d%d", &n, &k);
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (1ll * i * (i + 1) / 2 <= k) {
                ans = i;
            }
        }
        printf("%d\n", ans);
    }
   return 0;
}
