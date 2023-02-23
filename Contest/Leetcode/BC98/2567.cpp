class Solution {
public:
    int minimizeSum(vector<int>& nums) {
      int n = nums.size();
      sort(nums.begin(), nums.end());
      // case 1: 0, 1
      int ans = (nums.back() - nums[2]) + 0;
      // case 2: n - 1, n
      ans = min(ans, nums[n - 3] - nums[0]);
      // case 3: 0, n 
      ans = min(ans, nums[n - 2] - nums[1]);
      return ans;
    }
};