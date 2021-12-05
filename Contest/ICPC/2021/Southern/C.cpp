#include <bits/stdc++.h>

using namespace std;

#define long long long

string s;

int len;

int main() {
  cin >> s;
  cin >> len;
  string ans;
  int minChar = *min_element(s.begin(), s.end());
  vector<int> start;
  for (int i = 0; i < s.size(); ++i) if (s[i] == minChar) start.push_back(i);
    
  for (int l = 1; l <= len; ++l) {
    // cout << "step: "  << l << '\n';
    // for (int x: start) cout << x << " ";
    // cout << '\n';
    ans += char(minChar);

    // calculate next
    vector<int> canNext;
    int minNextChar = (int)1e9;
    for (int i : start) {
      if (i - 1 >= 0) {
        canNext.push_back(i - 1);
        minNextChar = min(minNextChar, (int)s[i - 1]);
      }
      if (i + 1 < s.size()) {
        canNext.push_back(i + 1);
        minNextChar = min(minNextChar, (int)s[i + 1]);
      }
    }
    // cout << "min next char: " << (char)minNextChar << '\n';
    // for (int x: canNext) cout << x << " "; cout << '\n';
    start.clear();
    for (int i : canNext) if ((int)s[i] == minNextChar) {
      start.push_back(i);
    }
    minChar = minNextChar;
  } 
  cout << ans;
  return 0;
}