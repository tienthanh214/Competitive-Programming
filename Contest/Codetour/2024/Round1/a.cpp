/**
 * Solution:
    Thật ra bài này chỉ cần tính căn bậc 3 của C, vì K >= 3 và p_i >= 10^6, trong khi X <= 10^6, do đó N lớn hơn C => C % N = C
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;
    long long C; cin >> C;
    for (int x = 0; 1ll * x * x * x <= C; ++x) {
        long long val = C - 1ll * x * x * x;
        bool flag = true;
        for (int x : a) if (val % x) {
            flag = false;
            break;
        }
        if (flag) return !(cout << x);
    }

    return 0;
}