class Solution {
public:
    int sumDigit(int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }
    int countLargestGroup(int n) {
        vector<int> S[50];
        for (int i = 1; i <= n; i++) {
            S[sumDigit(i)].push_back(i);
        }
        int tmax = 0, cnt = 0;
        for (int i = 0; i < 50; i++)
            if (S[i].size() > tmax) {
                tmax = S[i].size();
                cnt = 1;
            } else if (S[i].size() == tmax) cnt++;
        return cnt;
    }
};