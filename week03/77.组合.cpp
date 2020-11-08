/*
 * @lc app=leetcode.cn id=77 lang=cpp
 *
 * [77] 组合
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> combine(int n, int k) {
        vector<int> path;
        backtrack(n, k, path, 1);
        return res;
    }
    void backtrack(int n ,int k, vector<int>& path, int index) {
        if (path.size() == k) { 
            res.push_back(path);
            return;
        }
        for (int i = index; i <= n; i++) {
            path.push_back(i);
            backtrack(n, k, path, i+1);
            path.pop_back();
        }
    }
};
// @lc code=end

