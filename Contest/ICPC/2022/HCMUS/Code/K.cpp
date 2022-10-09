
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long lli;

int n, k;
vector<string> a;

void readInput() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        string s; cin >> s;
        a.push_back(s);
    }
}

int findGrade(string ans) {
    int ret = 1e9;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < k; ++j) {
            cnt += ans[j] == a[i][j];
        }
        ret = min(ret, cnt);
    }
    return ret;
}

void Solve(){
    int ans = 0;
    for (int mask = 0; mask < (1 << k); ++mask) {
        string curAns;
        for (int i = 0; i < k; ++i)
            curAns.push_back((mask >> i & 1) ? 'F' : 'T');
        ans = max(ans, findGrade(curAns));
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

    // cin >> testcase;
    while (testcase--){
        readInput();
        Solve();
    }

    return 0;
}

