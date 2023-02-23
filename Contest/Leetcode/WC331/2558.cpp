class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        while (k--) {
            int maxId = max_element(gifts.begin(), gifts.end()) - gifts.begin();
            gifts[maxId] = sqrt(gifts[maxId]);
        }
        long long sum = 0;
        for (int x : gifts) sum += x;
        return sum;
    }
};