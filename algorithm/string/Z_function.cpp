#include <iostream>
#include <vector>

using namespace std;

vector <int> Z_algorithm(string S) {
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
    return Z;
}

int main() {
    string s = "ababbaba";
    string t = "ab";
    vector<int> Z = Z_algorithm(t + '?' + s);
    for (int i = t.size(); i <= t.size() + s.size(); i++)
        if (Z[i] == t.size()) printf("%d ", i - t.size());
    return 0;
}
