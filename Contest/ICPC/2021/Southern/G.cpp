/* Wrong Answer in Contest :< */

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10; 

int n, m; 
string park, vehicle; 

bool check(int x) { 
    string a = park; 
    int car = 0, motor = 0; 
    for (int i = 0; i < x; ++i) { 
        car += vehicle[i] == 'C'; 
        motor += vehicle[i] == 'M'; 
    }
    for (int i = 0; i < n; ++i) if (a[i] == '.') {
      int j = i;
      while (j < n && a[j] == '.') ++j;

      // segment [i, j - 1]
      // using car
      int len = j - i;
      // cout << "before: length segment: " << len << " motor: " << motor << " car: " << car << '\n';
      if (len == 1) {
        // no-op
      } else if (len == 2) {
        // using one motor 
        if (motor > 0) {
          --motor;
        } else {
          // force to use car
          if (car > 0) {
            --car;
          } else {
            return true;
          }
        }
      } else {
        // .CC.CC.CC.CC...
        bool used_car = false;
        while (len > 5 && car > 0) {
          len -= 3;
          --car;
          used_car = true;
        }
        if (car == 0) {
          // no car left
          if (used_car) {
            if (len % 2 == 0) {
              ++car;
              len += 3;
              motor -= len / 2;
              if (motor < 0) {
                --car;
                ++motor;
              }
              if (motor < 0) return true;
            } else {
              motor -= len / 2;
              if (motor < 0) return true;
            }
          } else {
            motor -= len / 2; // force to use motor
            if (motor < 0) return true;
          }
        } else {
          // len >= 3 && len <= 5
          assert(len >= 3 && len <= 5);
          if (len == 3) {
            if (motor > 0) --motor;
            else {
              if (car > 0) --car;
              else {
                return true;
              }
            }
          } else if (len == 4) {
            if (car > 0) --car;
            else {
              motor -= 2;
              if (motor < 0) return true;
            }
          } else if (len == 5) {
            if (motor >= 2) motor -= 2;
            else {
              if (motor >= 1) {
                motor -= 1;
                car -= 1;
                if (car < 0) return true;
              } else {
                car -= 2;
                if (car < 0) return true;
              }
            }
          }
        }
      }
      // cout << "after: length segment: " << len << " motor: " << motor << " car: " << car << '\n';
      
      i = j;
    }
    return false;
}

void solve() { 
    cin >> park >> vehicle; 
    n = park.size(); 
    m = vehicle.size(); 
    bool check0 = false; 
    for (int i = 0; i < n - 1; ++i) 
        if (park[i] == '.' && park[i + 1] == '.') { 
            check0 = true; 
            break; 
        }
    if (!check0) { 
        for (int i = 0; i <= m; ++i) 
            cout << "N"; 
        cout << '\n'; 
        return; 
    }
    int l = 1, r = m; 
    while (l <= r) { 
        int mid = l + r >> 1; 
        if (check(mid)) 
            l = mid + 1; 
        else 
            r = mid - 1; 
    }
    cout << "Y"; 
    for (int i = 1; i < l; ++i) 
        cout << "Y"; 
    for (int i = l; i <= m; ++i) 
        cout << "N"; 
    cout << '\n'; 
}

int main() { 
  if (fopen("input.txt", "r")) {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc; 
    cin >> tc; 
    while (tc--) { 
        solve(); 
    }

    return 0; 
}