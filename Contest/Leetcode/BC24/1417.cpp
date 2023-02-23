class Solution {
    static const int base = 1e9 + 7;
    static const int MAXN = 1e5 + 10;
public:

    int dp[MAXN];
    int numberOfArrays(string s, int k) {
        dp[0] = 1;
        for (int i = 1; i <= s.size(); i++) {
            dp[i] = 0;
            long long num = 0;
            for (int j = i; j >= max(1, i - 9); j--) {
                num = num + round(pow(10, i - j)) * (s[j - 1] - '0');
                if (s[j - 1] != '0' && 1 <= num && num <= k)
                    dp[i] = (dp[i] + dp[j - 1]) % base;
            }
            
        }
        return dp[s.size()];
    }
};