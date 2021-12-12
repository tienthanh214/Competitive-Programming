#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10; 
const int AL = 26; 

int n; 
string s; 
int nxt[AL][N]; 

void solve() { 
    memset(nxt, -1, sizeof(nxt)); 
    cin >> s; 
    n = (int)(s.size()); 
    for (int i = n - 1; i >= 0; --i) 
        for (int j = 0; j < AL; ++j) 
            nxt[j][i] = (j != s[i] - 'a' ? nxt[j][i + 1] : i); 
    long long res = 0; 
    for (int i = 0; i < n; ++i) { 
        vector<pair<int, int>> vi(0); 
        for (int j = 0; j < AL; ++j) { 
            if (nxt[j][i] != -1) { 
                vi.push_back({nxt[j][i], 1}); 
                if (nxt[j][nxt[j][i] + 1] != -1) 
                    vi.push_back({nxt[j][nxt[j][i] + 1], -1}); 
            }
        }
        vi.push_back({n, 0}); 
        sort(vi.begin(), vi.end()); 
        int currentSum = 0; 
        for (int j = 0; j < (int)(vi.size()) - 1; ++j) { 
            // cout << i << " " << j << " " << vi[j].first << " " << vi[j].second << endl; 
            currentSum += vi[j].second;
            res += 1ll * currentSum * (vi[j + 1].first - vi[j].first); 
        }
        // cout << i << ": " << res << endl; 
    }
    cout << res << endl; 
}

int main() { 
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0); 

    int tc; 
    cin >> tc; 
    while (tc--) { 
        solve(); 
    }

    return 0; 
}