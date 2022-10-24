#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }

    int n;
    cin >> n;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    int Pow = 1;
    for (int i = 1; i < 10; ++i)
        Pow *= i;
    vector<int> res;
    for (int j = 9; j > 0; --j) {
        for (int i = 0; i < n / Pow; ++i) {
            res.push_back(j);
        }
        n %= Pow;
        Pow /= j;
    }
    sort(res.begin(), res.end());
    if (res.size() > 1 && !res[1])
        swap(res[0], res[1]);
    for (int x: res)
        cout << x;

    return 0;
}
