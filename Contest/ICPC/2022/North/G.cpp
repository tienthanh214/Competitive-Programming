#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int Mod = 1e9 + 7;

int n, a[N], f[N];

long long Pow(long long n, long long k){
    if (k == 0) return 1;
    if (k == 1) return n;
    long long tmp = Pow(n, k / 2);
    tmp = tmp * tmp % Mod;
    if (k % 2 == 0) return tmp;
    return tmp * n % Mod;
}

long long Sum(long long l, long long r){
    if (l > r) return 0;
    return r * (r + 1) / 2 - l * (l - 1) / 2;
}

long long SumBin(long long l, long long r){
    if (l > r) return 0;
    l--;
    return r * (r + 1) * (2 * r + 1) / 6 - l * (l + 1) * (2 * l + 1) / 6;
}

long long Calc(int i){
//    long long x = min(i, n - i + 1);
//    long long ret = x * (x + 1) * (2 * x + 1) / 6;
//    ret +=
    long long x = i, y = n - i + 1;
    if (x > y) swap(x, y);
    long long ret = 0;
//    for (int len = 1; len <= n; len++){
//        ret += 1ll * len * min(min(len, x), n - len + 1) % Mod;
//        ret %= Mod;
//    }
    long long len = x;
    /// xet len <= x <= n - len + 1
    /// -> len <= min(n - x + 1)
    //ret += len * (len + 1) * (2 * len + 1) / 6
    /// len <= n - len +

    ///
    ret += len * (len + 1) * (2 * len + 1) / 6 % Mod;
    ret %= Mod;
    ret += Sum(x + 1, n - x + 1) % Mod * x % Mod;
    ret %= Mod;
    ret += 1ll * (n + 1) * Sum(n - x + 2, n) % Mod;
    ret -= SumBin(n - x + 2, n) % Mod;
    if (ret < 0) ret += Mod;
    return ret;
    //return ret * Pow(2, Mod - 2) % Mod;
}

void Solve(){
    string s; cin >> s;
    n = s.size();
    long long sum = 0;
    for (int i = 0; i < s.size(); i++){
        long long val = s[i] - 'a' + 1;
        sum = (sum + Calc(i + 1) * val % Mod) % Mod;
        //cout << val << " " << Calc(i + 1) << endl;
    }
    cout << sum << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int testcase;
    cin >> testcase;
    while (testcase--){
        Solve();
    }
}
