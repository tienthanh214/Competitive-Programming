class Solution {
public:
    int minCapability(vector<int>& nums, int k) {
        auto check = [&](int val) {
            int cur = 0;
            int ret = 0;
            for (int i = 0; i < nums.size(); ++i) {
                if (nums[i] <= val) {
                    ++cur;
                } else {
                    ret += (cur + 1) / 2;
                    cur = 0;
                }
            }
            ret += (cur + 1) / 2;
            return ret >= k;
        };
        
        int low = 0, high = 1e9 + 7;
        int ans = 0;
        while (low <= high) {
            int mid = low + high >> 1;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};