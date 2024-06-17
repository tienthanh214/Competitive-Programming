#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 1;

int n;
int prime[N], cnt[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for (int i = 2; i < N; i++) if (!prime[i])
        for (int j = i; j < N; j += i)
            prime[j] = i;
    function<void(int)> fact = [&](int x) {
        while (x > 1) {
            int y = prime[x];
            while (x % y == 0) {
                x /= y;
                cnt[y]++;
            }
        }
    };
    scanf("%d", &n);
    while (n--) {
        int x;
        scanf("%d", &x);
        fact(x);
    }
    scanf("%d", &n);
    while (n--) {
        int x, y;
        scanf("%d%d", &x, &y);
        int fl = 1;
        while (x > 1) {
            int z = prime[x];
            int c = 0;
            while (x % z == 0) {
                x /= z;
                c++;
            }
            if (cnt[z] < c * y) {
                fl = 0;
                break;
            }
        }
        putchar(fl + '0');
    }
}
