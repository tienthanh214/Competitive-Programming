#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
typedef pair <int, int> ii;
int n, q; 
int a[N];
int ver[N];

struct Node {
    int l, r, val;
    Node(int _val = 0, int _l = 0, int _r = 0) {
        l = _l; r = _r; val = _val;
    }
};

struct PersistentSegmentTree {
    Node It[N * 70];
    int cntNode;
    int n;

    PersistentSegmentTree() {
        cntNode = 0;
    }

    int Update(int id, int l, int r, int pos) {
        int cur = ++cntNode;
        if (l == r) {
            It[cur] = Node(1, 0, 0);
            It[cur].val = It[id].val + 1;
            return cur;
        }
        int mid = l + r >> 1;
        if (pos <= mid) {
            It[cur].l = Update(It[id].l, l, mid, pos);
            It[cur].r = It[id].r;
        } else {
            It[cur].l = It[id].l;
            It[cur].r = Update(It[id].r, mid + 1, r, pos);
        }
        It[cur].val = It[It[cur].l].val + It[It[cur].r].val;
        return cur;
    }

    int getKValue(int l, int r, int k, int prev, int cur) {
        if (l == r) return l;
        int mid = l + r >> 1;
        int diff = It[It[cur].l].val - It[It[prev].l].val;
        // cout << l << ' ' << r << ' ' << mid << ' ' << diff << " " << k << endl;
        if (diff >= k) {
            return getKValue(l, mid, k, It[prev].l, It[cur].l);
        } else {
            return getKValue(mid + 1, r, k - diff, It[prev].r, It[cur].r);
        }
    }
} PST;

vector<int> rar;

void readInput() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
}

ii b[N];

void compress() {
    for (int i = 1; i <= n; ++i) {
        rar.push_back(a[i]);
    }
    sort(rar.begin(), rar.end());
    for (int i = 1; i <= n; ++i) {
        a[i] = lower_bound(rar.begin(), rar.end(), a[i]) - rar.begin() + 1;
    }
}

void solve() {
    ver[0] = 0;
    for (int i = 1; i <= n; ++i) {
        ver[i] = PST.Update(ver[i - 1], 1, 1e5, a[i]);
    }
    
    while (q--) {
        int l, r; cin >> l >> r;
        int idx = PST.getKValue(1, 1e5, (r - l + 2) / 2, ver[l - 1], ver[r]);
        cout << idx << '\n';
    }
}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    readInput();
    // compress();
    solve();


    return 0; 
}