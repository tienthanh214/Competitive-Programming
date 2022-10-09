#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> ii;

const int N = 1e5 + 10;

int n;
string s;

void readInput() {
    cin >> s;
    n = s.size();
}

int solve() {
    int cnt[10] = {0};
    for (int i = n - 1; i >= 0; --i) {
        if (cnt[s[i] - '0']++) {
            return i + 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int TC; cin >> TC;
    while (TC--) {
        readInput();
        cout << solve() << '\n';
    }
    
    return 0;
}