#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FOD(i, a, b) for (int i = a; i >= b; i--)
#define REP(i, a, b) for (int i = a; i < b; i++)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl;}

typedef long long LL;
const int N = 8010;
const int M = 810;
const LL INF = 1E18;

int L, G;
int a[N];
LL S[N];
LL f[M][N];
int R[M][N];

void Read_Input() {
    scanf("%d %d", &L, &G);
    FOR(i, 1, L) scanf("%d", &a[i]);
    FOR(i, 1, L) S[i] = S[i - 1] + a[i];
}

LL Cost(int i, int j) {
    return (S[j] - S[i - 1]) * (j - i + 1);
}

/// cal R(g, l..r) and F(g, l..r)
/// Know R(g, l..r) in [i..j]
/// R(g, i) <= R(g, i + 1) .... <= R(g, n) so divide and conquer
void Solve(int g, int l, int r, int i, int j) {
    if (l > r) return;
    int mid = (l + r) >> 1;
    f[g][mid] = INF;
    FOR(k, i, min(j, mid)) if (f[g][mid] > f[g - 1][k] + Cost(k + 1, mid)) {
        f[g][mid] = f[g - 1][k] + Cost(k + 1, mid);
        R[g][mid] = k;
    }
    Solve(g, l, mid - 1, i, R[g][mid]);
    Solve(g, mid + 1, r, R[g][mid], j);
}

void Optimize() {
    FOR(i, 1, L) f[0][i] = INF;
    FOR(g, 1, G) Solve(g, 0, L, 0, L);
    printf("%lld", f[G][L]);
}

int main() {
    Read_Input();
    Optimize();
    return 0;
}
