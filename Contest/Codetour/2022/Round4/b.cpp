#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> ii;

const int N = 1e5 + 10;

int n;
int a[N];
unordered_map<int, int> cnt;

void readInput() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        ++cnt[a[i]];
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    readInput();
    for (int i = 1; i <= n; ++i) {
        cout << cnt[a[i]] << ' ';
    }
    
    
    return 0;
}