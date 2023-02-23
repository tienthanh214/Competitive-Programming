class Solution {
public:
    int minImpossibleOR(vector<int>& nums) {
        auto isPower2 = [](int x) {
          return __builtin_popcount(x) == 1;
        };
        int mask = 0;
        for (int x : nums) {
          if (isPower2(x)) {
            mask |= x;
          }    
        }
        for (int i = 0; i <= 30; ++i) {
          if (!(mask >> i & 1)) {
            return 1 << i;
          }
        }
        return -1;
    }
};