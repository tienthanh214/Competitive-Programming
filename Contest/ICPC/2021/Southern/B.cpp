#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAX_N = 1e7 + 10;
const int base = 1e9 + 7;


int fact[MAX_N];
int sumFact[MAX_N];
int coefFact[MAX_N];

void prepare(int n) {
    fact[0] = sumFact[0] = 1;
    coefFact[0] = 0;
    for (int i = 1; i <= n; ++i) {
        fact[i] = (1ll * fact[i - 1] * i) % base;
        sumFact[i] = (sumFact[i - 1] + fact[i]) % base;
        coefFact[i] = (coefFact[i - 1] + 1ll * fact[i] * i % base) % base;
    }
}

int solve(int n) {
    if (n <= 1) return 0;
    int ans = fact[n];
    ans = (ans - (2ll * sumFact[n - 1]) % base + base) % base;
    ans = (ans + 1) % base;
    ans = (ans + (1ll * (n - 1) * sumFact[n - 2]) % base) % base;
    ans = (ans - coefFact[n - 2] + base) % base;
    return ans;
}

int main() {
    prepare(1e7);
    /*
    LL ans = fact(n);
    for (int i = 1; i <= n - 1; ++i) {
        ans -= 2 * fact(i);
    }
    ans -= 1;
    // cout << ans << endl;
    for (int i = 0; i <= n - 2; ++i)
        ans += fact(i) * ((n - 1) - i);
    cout << ans;
    */
    int TC; scanf("%d", &TC);
    while (TC--) {
        int n; scanf("%d", &n);
        printf("%d\n", solve(n));
    }
    return 0;
}