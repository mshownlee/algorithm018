/*
 * @lc app=leetcode.cn id=46 lang=cpp
 *
 * [46] 全排列
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> path;
        vector<bool> visited(nums.size(), false);
        backtrack(nums, visited, path);
        return res;
    }
    void backtrack(vector<int>& nums, vector<bool>& visited, vector<int>& path) {
        if (path.size() == nums.size()) {
            res.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) continue;
            visited[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, visited, path);
            visited[i] = false;
            path.pop_back();
        }
    }
};
// @lc code=end

