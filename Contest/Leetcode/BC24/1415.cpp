class Solution {
public:
    int minStartValue(vector<int>& nums) {
        int sum = 0;
        int ans = 1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (sum < 1) {
                ans = max(ans, -sum + 1);
            }
        }
        return ans;
    }
};