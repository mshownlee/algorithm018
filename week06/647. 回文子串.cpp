class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;
        int len = s.length();
        vector<bool> dp(len,false);
        for (int j = 0; j < len; j++) {
            for (int i = 0; i <= j; i++) {
                if (j == i) {
                    dp[i] = true;
                    count++;
                } else if (j - i == 1 && s[i] == s[j]) {
                    dp[i] = true;
                    count++;
                } else if (j - i > 1 && s[i] == s[j] && dp[i + 1]) {
                    dp[i] = true;
                    count++;
                } else {
                    dp[i] = false;
                }
            }
        }
        return count;
    };
};