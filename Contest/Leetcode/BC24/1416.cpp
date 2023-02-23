class Solution {
public:
    string cur = "", ans = "";
    int K, cnt = 0, N;
    void Try(int i) {
        if (cnt >= K) return;
        if (i == N) {
            if (++cnt == K) {
                ans = cur;     
            }
            return;
        }
        for (char c = 'a'; c <= 'c'; c++)
            if (cur.empty() || cur[i - 1] != c) {
                cur.push_back(c);
                Try(i + 1);
                cur.pop_back();
            }
    }
    string getHappyString(int n, int k) {
        K = k;
        N = n;
        Try(0);
        return ans;
    }
};