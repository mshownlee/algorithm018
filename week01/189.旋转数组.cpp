/*
 * @lc app=leetcode.cn id=189 lang=cpp
 *
 * [189] 旋转数组
 */

// @lc code=start
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int index = k % nums.size();
        if (index == 0) return;
        reverse(nums, 0, nums.size() - 1);
        reverse(nums, 0, index - 1);
        reverse(nums, index, nums.size() - 1);
    }
    void reverse(vector<int>& nums, int begin, int end) {
        while (begin < end) {
            swap(nums[begin++],nums[end--]);
        }
    }
};
// @lc code=end

