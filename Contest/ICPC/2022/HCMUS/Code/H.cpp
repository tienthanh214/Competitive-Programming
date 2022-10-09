// TLE -> should use persistent segment tree to reduce O(nlogn)

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef long long lli;

const int N = 3e5 + 10;
const lli MOD = 1e9 + 7;

int n, a[N], fval[N];
int fact[N];

void init() {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fact[i] = 1ll * fact[i - 1] * i % MOD;
    }
    for (int i = 1; i <= n; i++){
        fval[a[i]] = fact[n - i];
    }
}

int readInt() {
    char ch;
    int ret = 0;
    for (ch = getchar(); !isdigit(ch); ch = getchar());
    ret = ch - '0';
    for (ch = getchar();  isdigit(ch); ch = getchar())
        ret = ret * 10 + ch - '0';
    return ret;
}

void printInt(int x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x > 9) printInt(x / 10);
    putchar(x % 10 + '0');
}

void Add(int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
}

void Sub(int &x, int y) {
    x -= y;
    if (x < 0) x += MOD;
}



struct SegmentTree {
    vector<int> value[N * 4];
    vector<int> sum[N * 4];

    pair<vector<int>, vector<int>> Merge(int id, int leftId, int rightId) {
        int i = 0, j = 0;
        vector<int> resVal;
        vector<int> resSum;

        while (i < value[leftId].size() && j < value[rightId].size()) {
            if (value[leftId][i] < value[rightId][j]) {
                resVal.push_back(value[leftId][i]);
                ++i;
            } else {
                resVal.push_back(value[rightId][j]);
                ++j;
            }
        }
        while (i < value[leftId].size()) {
            resVal.push_back(value[leftId][i++]);
        }
        while (j < value[rightId].size()) {
            resVal.push_back(value[rightId][j++]);
        }
        resSum.resize(resVal.size());
        for (int i = 0; i < resSum.size(); ++i) {
            if (i > 0) {
                resSum[i] = (resSum[i - 1] + fval[resVal[i]]) % MOD;
            } else {
                resSum[i] = fval[resVal[i]];
            }
        }
        return {resVal, resSum};
    }

    void Build(int id, int l, int r) {
        for (int i = 1; i <= n; ++i)
            update2(1, 1, n, i, a[i]);
        sortAll();
    }

    void update2(int id, int l, int r, int pos, int vv) {
        if (r < pos || pos < l)
            return;
        if (l <= pos && pos <= r)
            value[id].push_back(vv);
        if (l == r)
            return;
        int mid = l + r >> 1;
        update2(id << 1, l, mid, pos, vv);
        update2(id << 1 | 1, mid + 1, r, pos, vv);
    }

    void sortAll() {
        for (int i = 1; i < N * 4; ++i){
            sort(value[i].begin(), value[i].end());
            sum[i].resize(value[i].size());
            for (int j = 0; j < sum[i].size(); ++j) {
                if (j > 0) {
                    sum[i][j] = sum[i][j - 1];
                    Add(sum[i][j], fval[value[i][j]]);
                } else {
                    sum[i][j] = fval[value[i][j]];
                }
        }
        }
    }

    int getIndex(int id, int val) {
        int idx = upper_bound(value[id].begin(), value[id].end(), val) - (value[id].begin() + 1);
        return idx;
    }

    int countLess(int id, int l, int r, int u, int v, int val) {
        if (v < l || r < u || l > r) return 0;
        if (u <= l && r <= v) {
            return getIndex(id, val) + 1;
        }
        int mid = l + r >> 1;
        return countLess(id << 1, l, mid, u, v, val) + countLess(id << 1 | 1, mid + 1, r, u, v, val);
    }

    int sumLess(int id, int l, int r, int u, int v, int val) {
        if (v < l || r < u || l > r) return 0;
        if (u <= l && r <= v) {
            int pos = getIndex(id, val);
            return pos > 0 ? sum[id][pos] : 0;
        }
        int mid = l + r >> 1;
        lli ret = (sumLess(id << 1, l, mid, u, v, val) + sumLess(id << 1 | 1, mid + 1, r, u, v, val));
        if (ret >= MOD) ret -= MOD;
        return ret;
    }

    int sumMore(int id, int l, int r, int u, int v, int val) {
        if (v < l || r < u || l > r) return 0;
        if (u <= l && r <= v) {
            int pos = getIndex(id, val);
            if (pos >= 0) {
                int res = sum[id].back();
                Sub(res, sum[id][pos]);
                return res;
            }
            return sum[id].back();
        }
        int mid = l + r >> 1;
        lli ret = (sumMore(id << 1, l, mid, u, v, val) + sumMore(id << 1 | 1, mid + 1, r, u, v, val));
        if (ret >= MOD) ret -= MOD;
        return ret;

    }

    int sumLess(int u, int v, int val) {
        return sumLess(1, 1, n, u, v, val);
    }

    int sumMore(int u, int v, int val) {
        return sumMore(1, 1, n, u, v, val);
    }

    int countLess(int u, int v, int val) {
        return countLess(1, 1, n, u, v, val);
    }


} ST;

int q;

void readInput() {
    n = readInt();
    q = readInt();
    for (int i = 1; i <= n; ++i)
        a[i] = readInt();
}


int findPermutation() {
    int res = 0;
    for (int i = 1; i <= n; ++i) {
        Add(res, 1ll * fact[n - i] * ST.countLess(i + 1, n, a[i]) % MOD);
    }
    return res + 1;
}

void Solve(){
    ST.Build(1, 1, n);
    int origin = findPermutation();
    while (q--) {
        int i, j;
        i = readInt();
        j = readInt();
        if (i > j) swap(i, j);
        if (i == j) {
            printInt(origin);
            putchar('\n');
            continue;
        }
        int res = origin;
        int cntI = ST.countLess(i + 1, n, a[i]);
        int cntJ = ST.countLess(j + 1, n, a[j]);

        Sub(res, 1ll * cntI * fact[n - i] % MOD);
        Sub(res, 1ll * cntJ * fact[n - j] % MOD);
        Add(res, 1ll * (cntJ + ST.countLess(i, j - 1, a[j])) * fact[n - i] % MOD);
        Add(res, 1ll * (cntI - ST.countLess(i + 1, j, a[i])) * fact[n - j] % MOD);

        Sub(res, ST.sumMore(i + 1, j - 1, a[j]));
        Add(res, ST.sumMore(i + 1, j - 1, a[i]));

        printInt(res);
        putchar('\n');
    }

}

int main() {
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int testcase = 1;
    // cin >> testcase;
    while (testcase--){
        readInput();
        init();
        Solve();
    }

    return 0;
}

