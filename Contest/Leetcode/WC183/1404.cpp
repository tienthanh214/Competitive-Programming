class Solution {
public:
   
    int numSteps(string s) {
        int ans = 0;
        while (s.size() > 1) {
            while (s.size() && s.back() == '0') {
                s.pop_back();
                ans++;
            }
            if (s.size() == 1) return ans;
            ans++;
            while (s.size() && s.back() == '1') {
                s.pop_back();
                ans++;
            }
            if (s.size()) s.back() = '1';
        }
        if (s.size()) ans += s.back() == '0';
        return ans;
    }
};