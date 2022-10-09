#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> ii;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q; 
    cin >> n >> q;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        ans ^= x;
    }
    for (int i = 1; i <= q; ++i) {
        int x; cin >> x;
        ans ^= x;
    }
    cout << ans;
    
    
    return 0;
}