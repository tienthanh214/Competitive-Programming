#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1e9 + 7;
const int N = 5e4 + 10;

int n, d;
int Pow[4];
string a[N];
map<int, int> cntAll[16];

int main() {
    Pow[0] = 1;
    for (int i = 1; i < 4; ++i)
        Pow[i] = Pow[i - 1] * 37;
    cin >> n >> d;
    d = 4 - d;
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        long long temp = 0;
        for (int mask = 0; mask < (1 << 4); ++mask) {
            if (__builtin_popcount(mask) == d)
            for (int mask2 = 0; mask2 < (1 << 4); ++mask2) {
                if ((mask2 & mask) != mask)
                    continue;
                int indx = 0, mapValue = 0;
                for (int j = 0; j < 4; ++j) {
                    if ((mask2 >> j & 1) == 0)
                        continue;
                    mapValue += ('0' <= a[i][j] && a[i][j] <= '9' ? a[i][j] - '0' : a[i][j] - 'a' + 10) * Pow[indx];
                    indx++;
                }
                if ((__builtin_popcount(mask2) - d) % 2) {
                    res -= cntAll[mask2][mapValue];
                    temp -= cntAll[mask2][mapValue];
                } else {
                    res += cntAll[mask2][mapValue];
                    temp += cntAll[mask2][mapValue];
                }
            }
        }
        for (int mask = 0; mask < (1 << 4); ++mask) {
            int indx = 0, mapValue = 0;
            for (int j = 0; j < 4; ++j) {
                if ((mask >> j & 1) == 0)
                    continue;
                mapValue += ('0' <= a[i][j] && a[i][j] <= '9' ? a[i][j] - '0' : a[i][j] - 'a' + 10) * Pow[indx];
                indx++;
            }
            cntAll[mask][mapValue]++;
        }
    }
    cout << res << endl;

    return 0;
}
