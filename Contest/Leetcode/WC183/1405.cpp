class Solution {
public:
    typedef pair<int, char> II;
    string longestDiverseString(int a, int b, int c) {
        string ans = "";
        II x[3];
        x[0] = {a, 'a'}; x[1] = {b, 'b'}; x[2] = {c, 'c'};
        sort(x, x + 3);
        while (x[2].first > 0) {
            if (ans.size() >= 2) {
                if (ans[ans.size() - 1] == ans[ans.size() - 2]) {
                    if (x[2].second == ans.back()) {
                        if (x[1].first == 0) break;
                        ans += x[1].second;
                        x[1].first--;
                        continue;
                    }
                }
            }
            ans += x[2].second;
            x[2].first--;
            sort(x, x + 3);
        }
        return ans;
    }
};