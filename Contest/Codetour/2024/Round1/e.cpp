#include <vector>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int TC; cin >> TC;
    while (TC--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (long long &x : a) cin >> x;
        bool ok = false;
        for (int i = 0; i < n; ++i) {
            if (a[i] != 1) continue;
            int j = i;
            long long curSum = 1;
            while (j < n && curSum >= a[j]) {
                curSum += a[j++];
            }
            if (j >= n) {
                // đã tìm được vị trí i thoả mãn đánh được đến hết
                // thực hiện đánh từ i - 1 về đầu xem có thể thắng được hết không
                int j = i - 1;
                while (j >= 0 && curSum >= a[j]) {
                    curSum += a[j--];
                }
                ok = j < 0;
                break;
            } else {
                // nếu từ i không thể đánh được đến hết thì từ i + 1 đến j cũng không thể đánh được đến hết
                // -> nhảy đến j + 1 luôn => dpt tổng là O(n)
                i = j;
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}