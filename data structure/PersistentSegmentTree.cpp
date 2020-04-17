#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

const int N = 1E5 + 10;
const int INF = 1E9 + 7;

struct Node {
    int left, right, key;
    Node (int x = 0, int y = 0, int z = 0) {
        key = x; left = y; right = z;
    }
} It[N * 4];

int n, nver = 0, id = 0;
int ver[N];

int Update(int l, int r, int i, int val, int pre) {
    int cur = ++id;
    if (l == r) {
        It[id] = Node(val, 0, 0);
        return cur;
    }
    int mid = (l + r) >> 1;
    if (i <= mid) {
        It[cur].left = Update(l, mid, i, val, It[pre].left);
        It[cur].right = It[pre].right;
    } else {
        It[cur].left = It[pre].left;
        It[cur].right = Update(mid + 1, r, i, val, It[pre].right);
    }
    It[cur].key = max(It[It[cur].left].key, It[It[cur].right].key);
    return cur;
}

int Query(int l, int r, int u, int v, int verid) {
    if (v < l || r < u || l > r) return -1;
    if (u <= l && r <= v) return It[verid].key;
    int mid = (l + r) >> 1;
    return max(Query(l, mid, u, v, It[verid].left),
               Query(mid + 1, r, u ,v, It[verid].right));
}

int main() {
    scanf("%d", &n);
    FOR(i, 1, n) {
        int x; scanf("%d" ,&x);
        ver[++nver] = Update(1, n, i, x, ver[nver - 1]);
    }
    int l, r, v;
    while (cin >> l >> r >> v) cout << Query(1, n, l, r, ver[v]) << endl;
    return 0;
}
