#include <bits/stdc++.h>

using namespace std;

#define long long long

long C2(long n) {
  return n * (n - 1) / 2;
}

int n;

unordered_map<int, int> cntX;
unordered_map<int, int> cntY;
map<pair<int, int>, int> cntXY;

const int N = 2e5 + 10;

pair<int, int> a[N];

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    int x, y; cin >> x >> y;
    a[i] = {x, y};
    cntX[x]++;
    cntY[y]++;
    cntXY[{x, y}]++;
  }
  long ans = 0;
  for (const auto &[coord, cnt] : cntX) {
    ans += C2(cnt);
  }
  for (const auto &[coord, cnt] : cntY) {
    ans += C2(cnt);
  }
  for (const auto &[coord, cnt] : cntXY) {
    ans -= C2(cnt);
  }
  cout << ans;

  return 0;
}