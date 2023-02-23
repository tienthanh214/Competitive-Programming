class Solution {
public:
    bool canConstruct(string s, int k) {
        int cnt[30] = {0};
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < s.size(); i++)
            cnt[s[i] - 'a']++;
        int dem = 0;
        for (int c = 'a'; c <= 'z'; c++)
            dem += cnt[c - 'a'] % 2;
        if (dem > k || k > s.size()) 
            return false;
        return true;
    }
};