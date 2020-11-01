/*
 * @lc app=leetcode.cn id=49 lang=cpp
 *
 * [49] 字母异位词分组
 */

// @lc code=start
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> hash;
        for (int i = 0; i < strs.size(); i++) {
            string str = strs[i];
            sort(str.begin(),str.end());
            hash[str].push_back(strs[i]);
        }
        vector<vector<string>> res;
        for (auto it = hash.begin(); it != hash.end(); it++) {
            res.push_back(it->second);
        }
        return res;
    }
};
// @lc code=end

