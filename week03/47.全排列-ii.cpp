/*
 * @lc app=leetcode.cn id=47 lang=cpp
 *
 * [47] 全排列 II
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> path;
        vector<bool> visited(nums.size(), false);
        sort(nums.begin(), nums.end()); // 排序以方便去重
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
            if (i > 0 && !visited[i - 1] && nums[i] == nums[i - 1]) continue;// 去重条件判断
            visited[i] = true;
            path.push_back(nums[i]);
            backtrack(nums, visited, path);
            visited[i] = false;
            path.pop_back();
        }
    }
};
// @lc code=end

