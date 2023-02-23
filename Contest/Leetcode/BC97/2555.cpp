class Solution {
public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int n = (int)prizePositions.size();
        vector<int> maxR(n + 1, 0);
        int j = n - 1;
        for (int i = n - 1; i >= 0; --i) {
            while (j >= i && prizePositions[j] - prizePositions[i] > k) {
                --j;
            }
            maxR[i] = max(maxR[i + 1], j - i + 1);
        }
        j = 0;
        int answer = 0;
        int maxCur = 0;
        for (int i = 0; i < n; ++i) {
            while (j <= i && prizePositions[i] - prizePositions[j] > k) {
                ++j;
            }
            maxCur = max(maxCur, i - j + 1);
            answer = max(answer, maxCur + maxR[i + 1]);
        }
        return answer;
    }
};