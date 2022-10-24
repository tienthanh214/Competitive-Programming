#include <bits/stdc++.h>

using namespace std;

const int N = 105;
const int Mod = 1e9 + 321;

int n, a[N], f[N];
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    memset(f, 0, sizeof(f));
    f[0] = 1;
    for (int i = 1; i <= n; i++){
        if (a[i] > 0){
            int x = i - a[i] + 1;
            if (x <= 0) continue;
            bool ok = true;
            for (int j = x; j <= i; j++) if (a[j] != 0 && a[j] != a[i]) ok = false;
            if (ok) f[i] = f[x - 1];
        }
        else{
            for (int k = 1; k <= i; k++){
                int x = i - k + 1;
                bool ok = true;
                for (int j = x; j <= i; j++) if (a[j] != 0 && a[j] != k) ok = false;
                if (ok) f[i] = (f[i] + f[x - 1]) % Mod;
            }
        }
    }
    //cout << f[n] << endl;
    if (f[n] == 1) cout << "YES\n";
    else cout << "NO\n";
    //for (int i = 1; i <= n; i++) cout << f[i] << " ";
}
