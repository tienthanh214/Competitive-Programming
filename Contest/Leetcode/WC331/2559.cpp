class Solution {
public:
    vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
        set<char> vowels;
        vowels.insert('u');
        vowels.insert('e');
        vowels.insert('o');
        vowels.insert('a');
        vowels.insert('i');
        
        vector<int> sum((int)words.size() + 1, 0);
        for (int i = 0; i < words.size(); ++i) {
            sum[i + 1] = sum[i] + (vowels.count(*words[i].begin()) && vowels.count(*words[i].rbegin()));
        }
        vector<int> ans;
        for (int i = 0; i < queries.size(); ++i) {
            int l = queries[i][0], r = queries[i][1];
            l++; r++;
            ans.push_back(sum[r] - sum[l - 1]);
        }
        return ans;
    }
};