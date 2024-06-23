#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <unordered_map>
#include <map>

using namespace std;

typedef long long ll;

const int N = 1e6 + 10;
const int K = 21;

int P[N][K];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    vector<ll> sum(n + 1);
    sum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        sum[i] = sum[i - 1] + x;
    }
    // from naive solution 
    // for each i, find next smallest j > i and j <= r such that sum[j] == sum[i] -> count + 1
    // from x find next smallest i that will ha smallest j such that sum[j] - sum[i] == x
    // so from x can fast jump to next j
    unordered_map<ll, int> lastPos;
    int nearestRight = n + 1;
    for (int i = n; i >= 0; --i) {
        if (lastPos.count(sum[i])) {
            nearestRight = min(nearestRight, lastPos[sum[i]]);
        }
        P[i][0] = nearestRight;
        lastPos[sum[i]] = i;
    }
    
    for (int j = 1; (1 << j) <= n; ++j) {
        for (int i = n; i >= 0; --i) {
            P[i][j] = P[i][j - 1] <= n ? P[P[i][j - 1]][j - 1] : n + 1;
        }
    }
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        int ans = 0;
        int k = log2(n - l + 1);
        for (int j = k; j >= 0; --j) {
            if (P[l][j] <= r) {
                ans += 1 << j;
                l = P[l][j];
            }
        }
        cout << ans << '\n';
    }

    return 0;
}