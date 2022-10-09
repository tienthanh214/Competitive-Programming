#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long lli;

const int N = 2e5 + 10;
const lli Mod = 998244353;

bool Check(string s){
    for (int i = 1; i < s.size(); i++) if (s[i] == s[i - 1]) return 0;
    return 1;
}

lli Pow(lli n, lli k){
    if (k == 0) return 1;
    if (k == 1) return n % Mod;
    lli tmp = Pow(n, k / 2);
    tmp = tmp * tmp % Mod;
    if (k % 2 == 0) return tmp;
    return tmp * n % Mod;
}

lli Calc(string s){
    if (s.size() == 1) return s[0] - '0';
    lli ret = 0;
    int n = s.size();
    for (int i = 0; i < n; i++){
        lli x = s[i] - '0';
        if (i == 0) ret = (ret + (x - 1) * Pow(9, n - i - 1) % Mod) % Mod;
        else if (i > 0){
            if (s[i] <= s[i - 1]){
                ret = (ret + x * Pow(9, n - i - 1) % Mod) % Mod;
                if (s[i] == s[i - 1]) break;
                if (i == n - 1) ret++;
            }
            else{
                ret = (ret + (x - 1) * Pow(9, n - i - 1) % Mod) % Mod;
                if (i == n - 1) ret++;
            }
        }
    }
    for (int i = 0; i < n - 1; i++){
        ret += Pow(9, n - i - 1);
        ret %= Mod;
    }
    return ret % Mod;
}

int convert(string s){
    int ret = 0;
    for (char ch: s) ret = ret * 10 + ch - '0';
    return ret;
}

void Solve(){
    string L, R;
    cin >> L >> R;
    //cout << R << " " << Calc(R) << endl;
    //cout << L << " " << Calc(L) << endl;
    //cout << Check(L) << endl;
    cout << (Calc(R) - Calc(L) + Mod * Mod + Check(L)) % Mod << endl;
    //cout << (Calc(R) - Calc(L) + Mod * Mod * 0 + Check(L)) % Mod << endl;
    lli ret = 0;
    //for (int i = convert(L); i <= convert(R); i++) ret += Check(to_string(i));
    //cout << ret << endl;
//    for (int i = 1; i <= 1e6; i++) {
//        string s = to_string(i);
//        ret = (ret + Check(s)) % Mod;
//        if (Calc(s) != ret) cout << i << endl;
//    }
}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    int testcase = 1;
    // cin >> testcase;
    while (testcase--){
        Solve();
    }

    return 0;
}

