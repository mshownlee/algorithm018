/*
 * @lc app=leetcode.cn id=242 lang=cpp
 *
 * [242] 有效的字母异位词
 */

// @lc code=start
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;
        int hash[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            hash[s[i] - 'a']++;
            hash[t[i] - 'a']--;
        }
        for (int j = 0; j < 26; j++) {
            if (hash[j] != 0) return false;
        }
        return true;
    }
};
// @lc code=end

