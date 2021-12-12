#include <bits/stdc++.h>

using namespace std;

string s;

void Add(int &a, int b) {
  a += b; if (a < 0) a += 26;
  if (a >= 26) a -= 26;
}

int main() {
  cin >> s;
  int n = s.size();
  vector<int> rot(n + 2);
  int m; cin >> m;
  for (int i = 1; i <= m; ++i) {
    int k, l, r; cin >> k >> l >> r;
    Add(rot[l], k);
    Add(rot[r + 1], -k);
  }
  for (int i = 1; i <= n; ++i) {
    Add(rot[i], rot[i - 1]);
  }
  for (int i = 1; i <= n; ++i) {
    s[i - 1] = (s[i - 1] - 'A' + rot[i]) % 26 + 'A';
  }
  cout << s;
  return 0;
}
