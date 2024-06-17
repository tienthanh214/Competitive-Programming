#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string S; cin >> S;
    S += S;
    // implement Z function
    vector <int> Z(S.size());
    int L = 0, R = 0;
    Z[0] = S.size();
    for (int i = 1; i < S.size(); i++) {
        if (R < i) {
            L = R = i;
            while (R < S.size() && S[R] == S[R - L]) R++;
            Z[i] = R - L; 
            R--;
        } else {
            int k = i - L;
            if (Z[k] < R - i + 1) {
                Z[i] = Z[k];
            } else {
                L = i;
                while (R < S.size() && S[R - L] == S[R]) R++;
                Z[i] = R - L;
                R--;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        if (Z[i] >= n) {
            int b = 0;
            int result = 0;
            for (int j = 0; j < i; ++j) {
                b += S[i + j] == '(' ? 1 : -1;
                if (b == 0) {
                    result++;
                }
            }
            cout << result;
            break;
        }
    }

    return 0;
}
