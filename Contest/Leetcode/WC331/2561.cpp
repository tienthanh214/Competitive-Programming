class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, int> cnt1, cnt2, cnt;
        for (int x : basket1) ++cnt1[x], ++cnt[x];
        for (int x : basket2) ++cnt2[x], ++cnt[x];
        vector<pair<int, int>> pos, neg;
        int minVal = 1e9 + 10;
        for (auto val : cnt) {
            minVal = min(minVal, val.first);
            if (val.second & 1) return -1;
            cnt1[val.first] -= val.second / 2;
            cnt2[val.first] -= val.second / 2;
            int diff = cnt1[val.first];
            if (diff > 0) {
                pos.push_back({val.first, diff});            
            } else if (diff < 0) {
                neg.push_back({val.first, -diff});
            }
        }
        sort(neg.begin(), neg.end());
        sort(pos.begin(), pos.end());
        int i = 0, j = pos.size() - 1;
        long long ans = 0;
        while (i < neg.size() && j >= 0) {
            int val = min(neg[i].second, pos[j].second);
            neg[i].second -= val;
            pos[j].second -= val;
            ans += 1ll * min({1ll * neg[i].first, 1ll * pos[j].first, 2ll * minVal}) * val;
            if (neg[i].second == 0) i++;
            if (pos[j].second == 0) j--;
        }
        
        return ans;
    }
};