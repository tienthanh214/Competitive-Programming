#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 13;

int n, k;
int a[N], l[N];
ll s[N];
ll res = 0;

ll findres() {
    ll ret = 0;
    for (int i = 1; i <= n; i++)
        s[i] = s[i - 1] + a[i];
    int Max = 1;
    for (int i = 1; i <= n; i++) {
        if (a[i] >= a[Max]) Max = i;
        l[i] = Max;
    }
    Max = n;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i] >= a[Max]) Max = i;
        ret += min(a[l[i]], a[Max]) - a[i];
    }
    return ret;
}

void Try(int x, int remain) {
    if (x == n) {
        a[x] += remain;
        res = max(res, findres());
        a[x] -= remain;
        return;
    }
    for (int j = 0; j <= remain; j++) {
        a[x] += j;
        Try(x + 1, remain - j);
        a[x] -= j;
    }
}

int main() {
//    freopen("a.inp", "r", stdin);
//    freopen("a.out", "w", stdout);
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    Try(1, k);
    cout << res;
//    cout << findres();
}
