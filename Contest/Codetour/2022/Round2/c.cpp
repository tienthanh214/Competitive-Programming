#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

typedef long long LL;

int n, q;
int a[N];
typedef pair<int, int> ii;
vector<ii> query[N];

struct RMQ {
    int M[N][18];
    void Build() {
        for (int i = 1; i <= n; i++)
            M[i][0] = a[i];
        for (int j = 1; 1 << j <= n; j++)
            for (int i = 1; i + (1 << j) - 1 <= n; i++)
                M[i][j] = __gcd(M[i][j - 1], M[i + (1 << (j - 1))][j - 1]);
    }
    int getGCD(int l, int r) {
        int k = trunc(log2(r - l + 1));
        return __gcd(M[l][k], M[r - (1 << k) + 1][k]);
    }
} RMQ;


void readInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int l, r;
        cin >> l >> r;
        query[r].push_back({l, i});
    }
}

LL cntGCD[N];

void prepareGCD() {
    for (int i = 1; i <= n; ++i) {
        int curGCD = a[i];
        int curPos = i;
        while (curPos <= n) {
            int l = curPos, h = n;
            int pos = n + 1;
            while (l <= h) {
                int mid = l + h >> 1;
                if (RMQ.getGCD(i, mid) != curGCD) {
                    pos = mid;
                    h = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            // [i, pos - 1] same gcd
            cntGCD[curGCD] += pos - curPos;
            if (pos > n) break;
            curGCD = RMQ.getGCD(i, pos);
            curPos = pos;
        }
    }
}


class FenwickTree { 
/// represents Fenwick tree (Binary index tree)
/// manager sum, get 1 -> pos.
private:
    int _size;
    vector<LL> ft;
public:
    FenwickTree(int __size = 0) {
        _size = __size;
        ft.resize(_size + 1);
        fill(ft.begin(), ft.end(), 0);
    }
    ~FenwickTree() {ft.clear();};

    void update(int pos, LL val) {
        if (pos <= 0) return;
        for (int i = pos; i <= _size; i += i & -i)
            ft[i] += val;
    }

    LL get(int pos) {
        LL ret = 0;
        for (int i = pos; i > 0; i -= i & -i)
            ret += ft[i];
        return ret;
    }
};

vector<int> divisors[N];
LL answer[N];

void solve() { 
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
    }
    FenwickTree FT(N);
    for (int r = 1; r < N; ++r) {
        for (int x : divisors[r]) {
            // cout << x << ' ' << r << ' ' << r - x << ' ' << cntGCD[x] << endl;
            FT.update(r - x, -cntGCD[x]);
            FT.update(r, cntGCD[x]);
        }
        if (query[r].empty()) continue;
        for (ii x : query[r]) {
            answer[x.second] = FT.get(r) - FT.get(x.first - 1);
        }
    }
    for (int i = 1; i <= q; ++i) {
        cout << answer[i] << '\n';
    }

}

int main() {
    readInput();
    RMQ.Build();
    prepareGCD();
    solve();
    return 0;
}