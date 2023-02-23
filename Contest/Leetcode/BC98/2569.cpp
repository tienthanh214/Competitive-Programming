class Solution {
public:
  
    // implement SegmentTree
    const static int N = 1e5 + 10;
    
    int n;
    int val[N * 4];
    bool lazy[N * 4];
      
    void down(int id, int l, int r){
      if (!lazy[id]) return;
      lazy[id << 1] = !lazy[id << 1];
      lazy[id << 1 | 1] = !lazy[id << 1 | 1];
      int mid = l + r >> 1;
      val[id << 1] = (mid - l + 1) - val[id << 1];
      val[id << 1 | 1] = (r - mid) - val[id << 1 | 1];
      lazy[id] = false;
    }
  
    void update(int id, int l, int r, int u, int v) {
      if (v < l || r < u || l > r) return;
      if (u <= l && r <= v) {
        lazy[id] = !lazy[id];
        val[id] = (r - l + 1) - val[id];
        return;
      }
      int mid = l + r >> 1;
      down(id, l, r);
      update(id << 1, l, mid, u, v);
      update(id << 1 | 1, mid + 1 ,r ,u, v);
      val[id] = val[id << 1] + val[id << 1 | 1];
      
    }
  
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
      n = nums1.size();
      memset(val, 0, sizeof(val));
      memset(lazy, false, sizeof(lazy));
      long long curSum = 0;

      for (int i = 0; i < nums1.size(); ++i) {
        if (nums1[i] == 1) 
          update(1, 1, n, i + 1, i + 1);
        curSum += nums2[i];
      }
      vector<long long> answer;
      for (int i = 0; i < queries.size(); ++i) {
        if (queries[i][0] == 1) {
          int l = queries[i][1] + 1;
          int r = queries[i][2] + 1;
          update(1, 1, n, l, r);
        } else if (queries[i][0] == 2) {
          int p = queries[i][1];
          int cnt1 = val[1];
          curSum += 1ll * p * cnt1;
        } else {
          answer.push_back(curSum);
        }
      }
      return answer;
    }
};