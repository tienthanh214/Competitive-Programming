class Solution {
public:
    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> p;
        vector<int> ans;
        for (int i = 0; i < m; i++)
            p.push_back(i + 1);
        for (int i = 0; i < queries.size(); i++) {
            for (int j = 0; j < p.size(); j++)
                if (queries[i] == p[j]) ans.push_back(j);
            vector<int> temp;
            temp.push_back(queries[i]);
            for (int j = 0; j < p.size(); j++)
                if (queries[i] != p[j]) temp.push_back(p[j]);
            p = temp;
        }
        return ans;
    }
};