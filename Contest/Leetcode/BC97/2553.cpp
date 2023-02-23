class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) {
        vector<int> res;
        for (int x : nums) {
            vector<int> cur;
            while (x > 0) {
                cur.push_back(x % 10);
                x /= 10;
            }
            reverse(cur.begin(), cur.end());
            for (int c : cur) res.push_back(c);
        }
        return res;
    }
};