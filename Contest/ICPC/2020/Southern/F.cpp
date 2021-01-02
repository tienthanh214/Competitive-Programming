#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int N = 1e6 + 10;

int n;
string a, b;
string diff;

void readInput() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    cin >> n;
    string temp;
    while (a.size() < n) {
        getline(cin, temp);
        a += temp;
    }

    while (b.size() < n) {
        getline(cin, temp);
        b += temp;
    }
}

void init() {
    for (int i = 0; i < n; ++i) {
        if (!isalpha(a[i])) continue;
        char x = (b[i] + 26);
        diff += x;
    }
}

vector<int> Z_algorithm(const string &s) {
   vector<int> z;
   n = (int)s.size();
   z.resize(n, 0);
   z[0] = 0;
   for (int i = 1, l = 0, r = 0; i < n; i++) {
      if (r >= i) {
         z[i] = min(z[i - l], r - i + 1);
      }
      while (z[i] + i < n && s[z[i] + i] == s[z[i]]) z[i]++;
      if (i + z[i] - 1 > r) {
         l = i;
         r = i + z[i] - 1;
      }
   }
   return z;
}

const int base = 1e9 + 7;

LL hashT[N << 1];
LL Pow[N << 1];

int getHash(int i, int j) {
    return (hashT[j] - hashT[i - 1] * Pow[j - i + 1] + 1ll * base * base) % base;
}

bool check(int x, int y, int len, string &s) {
    x++; y++;
    int l = 1, h = len;
    int ret = 0;
    while (l <= h) {
        int mid = l + h >> 1;
        if (getHash(x, x + mid - 1) == getHash(y, y + mid - 1)) {
            ret = mid;
            l = mid + 1;
        } else {
            h = mid - 1;
        }
    }
    if (ret == len) return 0;
    return s[x + ret - 1] > s[y + ret - 1];
}

int findSmallest(string s) {
    s += s;
    Pow[0] = 1; hashT[0] = 0;
    for (int i = 1; i <= s.size(); ++i)
        Pow[i] = Pow[i - 1] * 31ll % base;
    for (int i = 1; i <= s.size(); ++i)
        hashT[i] = (hashT[i - 1] * 31ll + (s[i - 1] - 'a')) % base;
    int pos = 0;
    for (int i = 1; i < s.size() / 2; ++i) {
        if (check(pos, i, (int)s.size() / 2, s))
            pos = i;
    }
    return pos;
}

void solve() {
    if (diff.empty()) {
        cout << "";
        return;
    }
    vector<int> z = Z_algorithm(diff);
    int len = z.size();
    for (int i = 0; i < z.size(); ++i)
        if (z[i] == z.size() - i) {
            len = i;
            break;
        }
    string key = diff.substr(0, len);
    //cout << diff << endl;
    //cout << key << endl;

    int pos = findSmallest(key);
    for (int i = pos; i < len; ++i)
        putchar(key[i]);
    for (int i = 0; i < pos; ++i)
        putchar(key[i]);
}

int main() {
    //gen();
    readInput();
    init();
    solve();
    return 0;
}
