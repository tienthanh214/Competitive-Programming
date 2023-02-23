class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        unordered_set<int> S;
        for (int x : banned) S.insert(x);
        int curSum = 0;
        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (S.count(i)) continue;
            if (curSum + i <= maxSum) {
                curSum += i;
                ++cnt;
            }
            else break;
        }
        return cnt;
    }
};