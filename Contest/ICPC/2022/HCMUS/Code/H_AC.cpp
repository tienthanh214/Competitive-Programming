// TLE -> should use persistent segment tree to reduce O(nlogn)

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long lli;

const int N = 3e5 + 10;
const int MOD = 1e9 + 7;

int n, a[N];
int fact[N];

void Add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

void Sub(int &x, int y) {
    x -= y;
    if (x < 0) x += MOD;
}


struct Node {
    int left, right, key, sum;
    Node (int _key = 0, int _sum = 0, int _left = 0, int _right = 0) {
        this->key = _key; this->sum = _sum;
        this->left = _left; this->right = _right;
    }
};

struct SegmentTree {
    int id;
    int ver[N];
    Node It[N * 21];

    SegmentTree() {
        this->id = 0;
        ver[0] = 0;
    }

    int Update(int l, int r, int i, int val, int sum, int pre) {
        int cur = ++id;
        if (l == r) {
            It[id] = Node(val, sum, 0, 0);
            return cur;
        }
        int mid = (l + r) >> 1;
        if (i <= mid) {
            It[cur].left = Update(l, mid, i, val, sum, It[pre].left);
            It[cur].right = It[pre].right;
        } else {
            It[cur].left = It[pre].left;
            It[cur].right = Update(mid + 1, r, i, val, sum, It[pre].right);
        }
        It[cur].key = It[It[cur].left].key + It[It[cur].right].key;

        It[cur].sum = It[It[cur].left].sum;
        Add(It[cur].sum,  It[It[cur].right].sum);
        return cur;
    }

    int countLess(int l, int r, int val, int pre, int cur) {
        if (l > r || val <= l) return 0;
        if (r < val) {
            int cnt = It[cur].key - It[pre].key;
            return cnt;
        }
        int mid = (l + r) >> 1;
        return countLess(l, mid, val, It[pre].left, It[cur].left)
                + countLess(mid + 1, r, val, It[pre].right, It[cur].right);
    }

    int sumMore(int l, int r, int val, int pre, int cur) {
        if (l > r || r <= val) return 0;
        if (val < l) {
            int sum = It[cur].sum; Sub(sum, It[pre].sum);
            return sum;
        }
        int mid = (l + r) >> 1;
        int result = sumMore(l, mid, val, It[pre].left, It[cur].left);
        Add(result, sumMore(mid + 1, r, val, It[pre].right, It[cur].right));
        return result;
    }

    int sumMore(int l, int r, int val) {
        if (l > r) return 0;
        return sumMore(1, n, val, ver[l - 1], ver[r]);
    }

    int countLess(int l, int r, int val) {
        if (l > r) return 0;
        return countLess(1, n, val, ver[l - 1], ver[r]);
    }

} PST;

int q;

void readInput() {
    cin >> n >> q;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

}

int cnt[N];

void init() {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }
}

int findPermutation() {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        cnt[i] = PST.countLess(i + 1, n, a[i]);
        Add(res, 1ll * fact[n - i] * cnt[i] % MOD);
    }
    return res + 1;
}

void Solve(){
    for (int i = 1; i <= n; ++i) {
        PST.ver[i] = PST.Update(1, n, a[i], 1, fact[n - i], PST.ver[i - 1]);
    }
    
    int origin = findPermutation();
    while (q--) {
        int i, j;
        cin >> i >> j;

        if (i > j) swap(i, j);
        if (i == j) {
            cout << origin << '\n';
            continue;
        }
        int res = origin;
        // int cntI = PST.countLess(i + 1, n, a[i]);
        // int cntJ = PST.countLess(j + 1, n, a[j]);
        int cntI = cnt[i];
        int cntJ = cnt[j];

        Sub(res, 1ll * cntI * fact[n - i] % MOD);
        Sub(res, 1ll * cntJ * fact[n - j] % MOD);
        Add(res, 1ll * (cntJ + PST.countLess(i, j - 1, a[j])) * fact[n - i] % MOD);
        Add(res, 1ll * (cntI - PST.countLess(i + 1, j, a[i])) * fact[n - j] % MOD);

        Sub(res, PST.sumMore(i + 1, j - 1, a[j]));
        Add(res, PST.sumMore(i + 1, j - 1, a[i]));

        cout << res << '\n';
    }

}

int main() {
    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int testcase = 1;
    // cin >> testcase;
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    while (testcase--){
        readInput();
        init();
        Solve();
    }
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::cerr << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count() / 1e6 << "[s]" << std::endl;
    return 0;
}

