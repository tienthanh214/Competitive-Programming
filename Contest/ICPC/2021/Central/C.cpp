
// AC in practice
/* optimal value of [l, r] is mean(a[l..r])
    -> merge until mean(a[l1..r1]) < mean(a[r1 + 1, i])
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAX_N = 1e6 + 10;

#define sqr(x) (x) * (x)

struct Segment {
    int l, r;
    double value;
    Segment(int _l = 0, int _r = 0, double value = 0): l(_l), r(_r), value(value) {}
    bool operator > (const Segment &other) {
        return value * (other.r - other.l + 1) > other.value * (r - l + 1);
    }
    inline double getValue() {
        return (double)value / (r - l + 1);  
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    double* sum = new double[n];
    double* a = new double[n];
    auto getSum = [sum](int l, int r) {
        return l == 0 ? sum[r] : sum[r] - sum[l - 1];
    };
    stack<Segment> S; 
    for (int i = 0; i < n; ++i) {
        double x; cin >> x; a[i] = x;
        sum[i] = i == 0 ? x : sum[i - 1] + x;
        Segment cur(i, i, x);
        while (S.size() && S.top() > cur) {
            // merge two segment
            cur.l = S.top().l;
            cur.value = getSum(cur.l, cur.r);
            S.pop();
        }
        S.push(cur);
    }
    double ans = 0;
    while (S.size()) {
        int l = S.top().l, r = S.top().r;
        for (int i = l; i <= r; ++i)
            ans += sqr(S.top().getValue() - a[i]);
        S.pop();
    }
    cout << fixed << setprecision(8) << sqrt(ans);  
    delete[] a; 
    delete[] sum;
    return 0;
}