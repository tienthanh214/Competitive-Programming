#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long lli;

const int N = 3e5 + 10;
const lli MOD = 1e9 + 7;

int n, a[N], fval[N];
int fact[N];

void init() {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }
    for (int i = 1; i <= n; i++){
        fval[a[i]] = fact[n - i];
    }
}

int q;

void readInput() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
}

void Add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

void Sub(int &x, int y) {
    x -= y;
    if (x < 0) x += MOD;
}

int findPermutation() {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        int cntLess = 0;
        for (int j = i + 1; j <= n; ++j)
            cntLess += a[i] > a[j];
        Add(res, 1ll * fact[n - i] * cntLess % MOD);
    }
    return res + 1;
}

void Solve(){
    int origin = findPermutation();
    while (q--) {
        int i, j;
        cin >> i >> j;

        swap(a[i], a[j]);
        int res = findPermutation();
        swap(a[i], a[j]);
        cout << res << '\n';
    }

}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("answer.txt", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int testcase = 1;
    // cin >> testcase;
    while (testcase--){
        readInput();
        init();
        Solve();
    }

    return 0;
}


