#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<LL, int> ii;

const int N = 3e5 + 10;

int n;
vector<vector<ii>> adj;
LL depth[N];
LL longest[N];
LL minDiff;

void readInput() {
    adj.assign(n + 1, vector<ii>());
    for (int i = 2; i <= n; ++i) {
        int p, l;
        scanf("%d%d", &p, &l);
        adj[p].push_back({l, i});
    }
    for (int i = 1; i <= n; ++i) {
        depth[i] = 0;
        longest[i] = 0;
    }
}

void DFS(int u) {
    LL max1 = 0, max2 = 0;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i].second;
        int w = adj[u][i].first;
        DFS(v);
        if (depth[v] + w > max1) {
            max2 = max1;
            max1 = depth[v] + w;
        } else if (depth[v] + w > max2) {
            max2 = depth[v] + w;
        }
        depth[u] = max(depth[u], depth[v] + w);
        longest[u] = max(longest[u], longest[v]);
    }
    longest[u] = max(longest[u], max1 + max2);
    //cout << u << " " << longest[u] << endl;
}

void reDFS(int u, LL longest_from_root, LL longest_path) { //now re-root tree to u
    // cout << "u = " << u << " " << longest_from_root << " " << longest_path << endl;
    vector<ii> cur, cur_longest;
    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i].second;
        int w = adj[u][i].first;
        cur.push_back({depth[v] + w, v});
        cur_longest.push_back({longest[v], v});
    }
    cur.push_back({longest_from_root, -1});
    cur_longest.push_back({longest_path, -1});
    sort(cur.rbegin(), cur.rend());
    sort(cur_longest.rbegin(), cur_longest.rend());
    while (cur.size() > 3) cur.pop_back();
    while (cur_longest.size() > 3) cur_longest.pop_back();

    for (int i = 0; i < adj[u].size(); ++i) {
        int v = adj[u][i].second;
        int w = adj[u][i].first;
        LL cur_longest_from_root = longest_from_root;

        bool seenV = false;
        for (ii x : cur) if (x.second != v) {
            cur_longest_from_root = max(cur_longest_from_root, x.first);
            cur_longest_path += x.first;

        } else {
            seenV = true;
        }
        if (!seenV && (int)cur.size() == 3)
            cur_longest_path -= cur.back().first;

        for (ii x : cur_longest) if (x.second != v)
            cur_longest_path = max(cur_longest_path, x.first);
        // cout << cur_longest_path << " - " << longest[v] << endl;
        minDiff = min(minDiff, abs(cur_longest_path - longest[v]));
        // cout << "minDiff = " << minDiff << endl;
        reDFS(v, cur_longest_from_root + w, cur_longest_path);
    }

}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    while (scanf("%d", &n) == 1) {
        if (n == 0) break;
        readInput();
        DFS(1);
        minDiff = 1e18;
        reDFS(1, 0, 0);
        printf("%lld\n", minDiff);
    }
    return 0;
}
