class Solution {
public:
    int dp[505][505];
    int maxSatisfaction(vector<int>& satisfaction) {
        int n = satisfaction.size();
        sort(satisfaction.begin(), satisfaction.end());
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                dp[i][j] = -1e9;
        dp[0][0] = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= i; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j && dp[i - 1][j - 1] != -1e9)
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + satisfaction[i - 1] * j);
            }
        int ans = 0;
        for (int j = 0; j <= n; j++)
            ans = max(ans, dp[n][j]);
        return ans;
    }
};