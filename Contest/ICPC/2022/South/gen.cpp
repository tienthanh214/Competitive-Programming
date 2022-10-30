#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

int main() { 
    freopen("input.txt", "w", stdout);
    int n = 1e4;
    int m = 100 * 100;
    cout << n << ' ' << m << endl;
    vector<int> a;
    for (int i = 1; i <= n; ++i) a.push_back(i);
    random_shuffle(a.begin(), a.end());
    for (int i = 1; i <= n; i += 1) {
        cout << a[i - 1] << " ";
    }
    cout << endl;
    srand(time(NULL));
    for (int i = 1; i <= m; ++i) {
        int x = min(1ll * n, 1ll * rand() * rand() * rand() % n + 1);
        int y = min(1ll * n, 1ll * rand() * rand() * rand() % n + 1);
        cout << x << ' ' << y << endl;
    }
    system("a < input.txt > output.txt");
    return 0; 
}