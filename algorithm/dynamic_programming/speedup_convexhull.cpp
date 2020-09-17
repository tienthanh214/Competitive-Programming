// NKLEAVES - spoj
#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) cout << #X << " = " << X << endl;
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

typedef long long ll;

const int N = (int) 1E5 + 10;
const int K = 15;
const ll INF = (ll) 1E15 + 7;

int n, k;
int a[N];
ll S[N], T[N];
ll dp[N][K];

struct Line {
    ll a, b;
    Line (ll _a = 0, ll _b = 0) : a(_a), b(_b) {}
};

struct Hull {
    Line p[N];
    int tail, head;


    void Init() {
        tail = 0; head = 1;
    }
    bool Check(Line l1, Line l2, Line l3) {
        return (l2.b - l1.b) * (l1.a - l3.a)
                < (l3.b - l1.b) * (l1.a - l2.a);
    }
    void Update(Line l) {
        while (tail > 1 && Check(p[tail - 1], p[tail], l))
            tail--;
        p[++tail] = l;
    }
    ll Query(ll x) {
        if (head > tail) head = tail;
        while (head < tail &&
               p[head].a * x + p[head].b > p[head + 1].a * x + p[head + 1].b)
                head++;
        //cout << head << " " << tail << " " << p[head].a << " " << p[head].b << " ";
        return p[head].a * x + p[head].b;
    }
} Hull[K];

void Read_Input() {
    scanf("%d%d", &n, &k);
    FOR(i, 1, n) scanf("%d", &a[i]);
}

void Init() {
    FOR(i, 1, n) {
        S[i] = S[i - 1] + a[i];
        T[i] = T[i - 1] + i * a[i];
    }
    FOR(i, 1, n) FOR(j, 0, k) dp[i][j] = INF;
    FOR(i, 1, k) Hull[i].Init();
}

void Optimize() {
    FOD(i, n, 1) FOR(j, 1, k) {
        Hull[j].Update(Line(-S[i], T[i] + dp[i + 1][j - 1]));
        dp[i][j] = Hull[j].Query(i) + S[i - 1] * i - T[i - 1];
    }
    printf("%lld", dp[1][k]);
}

int main() {
    Read_Input();
    Init();
    Optimize();

    return 0;
}
