#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

string S, T;

int n;
int cntT[26];
int f[N][26], nxt[N][26];

bool Check(int p, int fc, const vector<int> &cnt) {
  int np = nxt[p][fc];
  for (int c = 0; c < 26; ++c)
    if (f[np + 1][c] < cnt[c] - (c == fc)) {
      return false;
    }
  return true;
}

int main() {
  cin >> S >> T;
  n = S.size();
  for (int c = 0; c < 26; ++c) nxt[n + 1][c] = n + 1;
  for (int i = n; i >= 1; --i) {
    for (int c = 0; c < 26; ++c) {
      f[i][c] = f[i + 1][c];
      nxt[i][c] = nxt[i + 1][c];
    }
    f[i][S[i - 1] - 'a']++;
    nxt[i][S[i - 1] - 'a'] = i;
  }
  vector<int> cnt(26);
  for (char c: T) cnt[c - 'a']++;
  string ans;
  int ptr = 1;
  for (int i = 0; i < T.size(); ++i) {
    bool found = false;
    for (char c = 0; c < 26; ++c) if (cnt[c] != 0 && Check(ptr, c, cnt)) {
      ptr = nxt[ptr][c];
      ans += (c + 'a');
      cnt[c]--;
      found = true;
      break;
    }
    ++ptr;
    if (found == false) {
      cout << "-1";
      return 0;
    } 
  }
  cout << ans;
  return 0;
}
