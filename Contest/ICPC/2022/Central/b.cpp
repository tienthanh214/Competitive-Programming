#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10; 

int n; 
string str; 
int lps[N], arr[N]; 

vector<int> Zfunc() { 
    vector<int> z(n); 
    z[0] = n; 
    int l = 0, r = 0; 
    for (int i = 1; i < n; ++i) { 
        z[i] = (i <= r ? min(r - i + 1, z[i - l]) : 0); 
        while (i + z[i] < n && str[z[i]] == str[i + z[i]])
            ++z[i]; 
        if (i + z[i] - 1 > r) { 
            r = i + z[i] - 1; 
            l = i; 
        }
    }
    return z; 
}

int main() {
    ios_base::sync_with_stdio(0);  
    cin.tie(0); cout.tie(0);
    cin >> str; 
    n = str.size(); 
    vector<int> z = Zfunc(); 
    vector<int> arr(z.begin(), z.end()); 
    sort(arr.begin(), arr.end());  
    int q; 
    cin >> q; 
    while (q--) { 
        int x; 
        cin >> x; 
        int id = lower_bound(arr.begin(), arr.end(), x) - arr.begin(); 
        int cnt = n - id; 
        // cout << x << " " << z[n - x] << " " << cnt << endl; 
        if (z[n - x] == x && cnt >= 3) 
            cout << "YES " << cnt << endl; 
        else 
            cout << "NO" << endl; 
    }

    return 0; 
}