#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using namespace __gnu_pbds;
using namespace std;

typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    ordered_set S;
    int n; cin >> n;
    while (n--) {
        string type;
        int x;
        cin >> type;
        if (type[0] == 'I') {
            cin >> x;
            S.insert(x);
        } else if (type[0] == 'O') {
            cin >> x;
            S.erase(S.upper_bound(x));
        } else {
            long long val = *S.find_by_order(S.size() / 2);
            if (S.size() % 2 == 0) {
                val += *S.find_by_order(S.size() / 2 - 1);
                cout << val/2;
                if (val & 1) cout << ".5";
                cout <<'\n';

            } else {
                cout << val << '\n';
            }
        }
    }

    return 0;
}
