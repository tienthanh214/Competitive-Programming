#include <bits/stdc++.h>

using namespace std;

const int N = 100;

vector<int> create(int l, int num) {
    vector<int> ret;
    for (int i = 1; i <= num; ++i)
        ret.push_back(i + l - 1);
    return ret;
}

int main() {
    int n, k;
    cin >> n >> k;
    // for all posible number of component = m
    // that n - m >= k
    // and  n - max >= k
    // x1 + x2 + .. xm = n and x1 = max
    for (int m = 1; m <= n - k; ++m) {
        vector<vector<int>> adj;
        int maxNode = min(n - k, n - m + 1);
        adj.push_back(create(1, maxNode));
        int total = maxNode;
        bool flag = maxNode > 0;
        for (int i = 1; i < m; ++i) {
            maxNode = min(n - total - (m - i - 1), maxNode);
            adj.push_back(create(total + 1, maxNode));
            total += maxNode;
            flag &= maxNode > 0;
        }
        flag &= total == n;
        if (!flag) continue;
        puts("YES");
        int cnt = 0;
        for (vector<int> x : adj) {
            for (int i = 0; i < x.size() - 1; ++i) {
                cout << x[i] << " " << x[i + 1] << endl;
                if (++cnt == k) break;
            }
            if (cnt == k) break;
        }
        for (int i = 1; i < adj.size(); ++i) {
            for (int j = 0; j < adj[i].size(); ++j) {
                cout << adj[i - 1][j] << " " << adj[i][j] << endl;
                if (++cnt == 2 * k) break;
            }
            if (cnt == 2 * k) break;
        }
        return 0;
    }
    puts("NO");
    return 0;
}
