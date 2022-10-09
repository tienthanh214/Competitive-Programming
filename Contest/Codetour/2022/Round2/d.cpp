#include <bits/stdc++.h>

using namespace std;

long long dp[66][122][122];
int n;
long long k;

long long F(int position, int minimum, int current, const int initValue) {
    if (position >= n) {
        if (minimum >= 0 && current + initValue == 0)
            return false;
        else
            return true;
    } else {
        if (dp[position][minimum + 61][current + 61] >= 0)
            return dp[position][minimum + 61][current + 61];
        dp[position][minimum + 61][current + 61] = F(position + 1, minimum, current - 1, initValue); 
        dp[position][minimum + 61][current + 61] += F(position + 1, min(minimum, current - 1), current + 1, initValue);
        return dp[position][minimum + 61][current + 61]; 
    }
}

void go() {
    int minimum = 0, current = 0;
    int initValue = 0;
    if (n >= 61) {
        initValue = n - 60;
        n = 60;
    }
    for (int i = 1; i <= initValue; ++i)
        cout << '(';
  	
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        if (k <= F(i, min(current + 1, minimum), current + 1, initValue)) {
            current += 1;
         minimum = min(minimum, current);
            cout << '(';
        } else {
            k -= F(i, min(current + 1, minimum), current + 1, initValue);
            current -= 1;
            minimum = min(minimum, current);
            cout << ')';
        }
    }
}


int main() {
    cin >> n >> k;
    go();
    
}