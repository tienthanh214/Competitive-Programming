#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;
const int N = 1e6 + 10;

vector<vector<ii>> Q;
vector<int> S;
vector<int> rem;

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int q; cin >> q;
    Q.push_back(vector<ii>());


    while (q--) {
        string type;
        cin >> type;

        if (type == "push") {
            int x; cin >> x;
            S.push_back(x);
            Q.back().push_back({1, x});
        } else if (type == "top") {
            int x; cin >> x;
            if ((int)S.size() - x - 1 < 0) {
                cout << "0\n";
            } else {
                cout << S[(int)S.size() - x - 1] << '\n';
            }
        } else if (type == "pop") {
            int x; cin >> x;
            x = min(x, (int)S.size());
            Q.back().push_back({3, x});
            for (int i = 0; i < x; ++i) {
                rem.push_back(S.back());
                S.pop_back();
            }
        } else if (type == "begin") {
            Q.push_back(vector<ii>());
        } else if (type == "rollback") {
            if (Q.size() == 1) {
                cout << "false\n";
                continue;
            }
            vector<ii> cur = Q.back();
            Q.pop_back();
            cout << "true\n";
            while (cur.size()) {
                ii temp = cur.back();
                cur.pop_back();
                if (temp.first == 1) { // push
                    S.pop_back();
                } else if (temp.first == 2) { // top
                    continue;
                } else { // pop
                    int cnt = temp.second;
                    for (int i = 0; i < cnt; ++i) {
                        S.push_back(rem.back());
                        rem.pop_back();
                    }
                }
            }

        } else { // commit
            if (Q.size() == 1) {
                cout << "false\n";
                continue;
            }
            vector<ii> cur = Q.back();
            Q.pop_back();
            cout << "true\n";

            for (int i = 0; i < cur.size(); ++i)
                Q.back().push_back(cur[i]);

        }
    }
    return 0;
}
