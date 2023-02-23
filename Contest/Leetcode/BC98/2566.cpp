class Solution {
public:
    int minMaxDifference(int num) {
        string str = to_string(num);
        int maxVal = 0;
        int minVal = 1e9;
      
        auto strToNum = [](string s) {
          int num = 0;
          for (char c : s) num = num * 10 + c - '0';
          return num;
        };
      
        for (char c = '0'; c <= '9'; ++c) {
          string newStr1 = str;
          string newStr2 = str;
          for (int i = 0; i < str.size(); ++i) {
            if (newStr1[i] == c) {
              newStr1[i] = '9';
            }
            if (newStr2[i] == c) {
              newStr2[i] = '0';
            }
            minVal = min(minVal, strToNum(newStr2));
            maxVal = max(maxVal, strToNum(newStr1));
          }
        }
      return maxVal - minVal;
    }
};