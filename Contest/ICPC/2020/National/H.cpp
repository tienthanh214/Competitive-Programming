#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int base = 1e9 + 7;
const int N = 5e5 + 10;

int n, m;
int w[N];
string st[N];
int cnt[55][30];
vector<string> keys;

void readInput() {
    keys.clear();
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> w[i];
    cin >> m;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= m; ++i) {
        cin >> st[i];
        if (st[i].size() > 50) continue;
        ++cnt[st[i].size()][st[i].front() - '0'];
        //cout << st[i].front() << " " << st[i].size() << " " << cnt[st[i].size()][st[i].front() - '0'] << endl;
        if (st[i].size() == n)
            keys.push_back(st[i]);
    }
}

void solve() {
    int total = 0;
    for (string S : keys) {
        int ans = 1;
        --cnt[n][S.front() - '0'];

        for (int i = 0; i < S.size(); ++i) {
           // cout << S[i] << " " << w[i] << " " << cnt[w[i]][S[i] - '0'] << endl;
            ans = 1ll * ans * cnt[w[i]][S[i] - '0'] % base;
            --cnt[w[i]][S[i] - '0'];
        } //cout << endl;
        for (int i = 0; i < S.size(); ++i) {
            ++cnt[w[i]][S[i] - '0'];
        }
        ++cnt[n][S.front() - '0'];
        total = (ans + total) % base;
    }
    cout << total << '\n';
}

int main() {
    #ifdef LOCAL
    freopen("a.inp", "r", stdin);
    freopen("a.out", "w", stdout);
    #endif // LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int TC; cin >> TC;
    while (TC--) {
        readInput();
        solve();
    }
    return 0;
}
