#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e5 + 10;
const int base = 998244353;

int pow10[MAXN];
int n;

struct Node {
    int res;
    char opL, opR;
    int numL, numR;  //num from lead -> left most operator, num from right most operator -> trail
    int lenL, lenR; //left most operator, right most operator
    Node(int _res = 0, char _opL = 0, char _opR = 0, int _numL = 0, int _numR = 0, int _lenL = 0, int _lenR = 0) {
        res = _res;
        opL = _opL; opR = _opR;
        numL = _numL; numR = _numR;
        lenL = _lenL; lenR = _lenR;
    }
};

int concat(int x, int y, int len) {
    return (1ll * x * pow10[len] % base + y) % base;
}

int calc(int x, int y, char op) {
    if (op == '-')
        return (x - y + base) % base;
    else
        return (x + y) % base;
}

struct SegmentTree {
    #define mid (l + r) / 2
    Node st[MAXN << 2];
    Node mergeNode(Node X, Node Y) {
        Node Z;
        if (!isdigit(X.opL)) { //left branch have a operator
            Z.opL = X.opL;
            Z.lenL = X.lenL;
            Z.numL = X.numL;
        } else {
            Z.opL = Y.opL;
            Z.lenL = X.lenL + Y.lenL;
            Z.numL = concat(X.numL, Y.numL, Y.lenL);
        }

        if (!isdigit(Y.opR)) { //left branch have a operator
            Z.opR = Y.opR;
            Z.lenR = Y.lenR;
            Z.numR = Y.numR;
        } else {
            Z.opR = X.opR;
            Z.lenR = Y.lenR + X.lenR;
            Z.numR = concat(X.numR, Y.numR, Y.lenR);
        }
        // res =  X.resL <op[i]> cal(i + 1, j - 1) <op[j]> Y.resR
        // dung toan de tinh X.resL dua tren X.numR chuyen ve doi dau
        // the same as Y.resR
        int numMid = concat(X.numR, Y.numL, Y.lenL);
        int sumLeft = (X.res - X.numR + base) % base;
        int sumRight = (Y.res - Y.numL + base) % base;
        if (X.opR == '-')
            sumLeft = (X.res + X.numR) % base;
        if (Y.opL == '-')
            sumRight = (base - sumRight) % base;
        Z.res = calc(sumLeft, numMid, X.opR);
        Z.res = calc(Z.res, sumRight, Y.opL);

        return Z;
    }
    void build(int id, int l, int r, char a[]) {
        if (l == r) {
            st[id] = Node((a[l] - '0') * (isdigit(a[l])),
                          a[l], a[r],
                          (a[l] - '0') * (isdigit(a[l])), (a[r] - '0') * (isdigit(a[r])),
                          isdigit(a[l]), isdigit(a[r]));

            return;
        }
        build(id << 1, l, mid, a);
        build(id << 1 | 1, mid + 1, r, a);
        st[id] = mergeNode(st[id << 1], st[id << 1 | 1]);
    }

    void update(int id, int l, int r, int pos, char val) {
        if (pos < l || r < pos || l > r) return;
        if (l == r) {
            st[id] = Node((val - '0') * (isdigit(val)),
                          val, val,
                          (val - '0') * (isdigit(val)), (val - '0') * (isdigit(val)),
                          isdigit(val), isdigit(val));
            return;
        }
        update(id << 1, l, mid , pos, val);
        update(id << 1 | 1, mid + 1, r, pos, val);
        st[id] = mergeNode(st[id << 1], st[id << 1 | 1]);
    }

    Node query(int id, int l, int r, int u, int v) {
        if (v < l || r < u || l > r)
            return Node();
        if (u <= l && r <= v)
            return st[id];
        return mergeNode(query(id << 1, l, mid, u, v),
                         query(id << 1 | 1, mid + 1, r, u, v));
    }

    void update(int pos, char val) {
        update(1, 1, n, pos, val);
    }
    Node query(int u, int v) {
        return query(1, 1, n, u, v);
    }
    #undef mid
} ST;


char a[MAXN];

void init() {
    pow10[0] = 1;
    for (int i = 1; i <= n; ++i)
        pow10[i] = 10ll * pow10[i - 1] % base;
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    scanf("%s", a + 1);
    n = strlen(a + 1);
    init();
    ST.build(1, 1, n, a);


    int q; scanf(" %d", &q);
    while (q--) {
        char type;
        scanf(" %c", &type);
        
        if (type == '?') {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", ST.query(l, r).res);
        } else {
            int x;
            char c;
            scanf("%d %c", &x, &c);
            ST.update(x, c);
        }
    }
    return 0;
}
