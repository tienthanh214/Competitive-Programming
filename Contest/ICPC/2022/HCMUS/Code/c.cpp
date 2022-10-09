#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long lli;

const int N = 1e7 + 10;

bool p[N];
vector<int> prime;

void sieve(int n) {
    memset(p, true, sizeof(p));
    p[0] = p[1] = false;
    for (int i = 2; i <= n; ++i) {
        if (p[i] == true) {
            for (int j = 2 * i; j <= n; j += i) {
                p[j] = false;
            }
            prime.push_back(i);
        }
    }
}

bool hasDigit(string p, int num) {
    string x = to_string(num);
    if (x.find(p) != -1) return true;
    return false;
}

void Solve(){
    int l, h;
    string n;
    cin >> l >> h;
    cin >> n;
    l--; h--;
    if (l > h) swap(l, h);
    int ans = 0;
    for (int i = l; i <= h; ++i) {
        ans += hasDigit(n, prime[i]);
    }
    cout << ans;

}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int testcase = 1;
    sieve(1e7);
    // cin >> testcase;
    while (testcase--){
        Solve();
    }

    return 0;
}

