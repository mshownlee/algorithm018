/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除排序数组中的重复项
 */

// @lc code=start
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int length = 0;
        for (int i = 0; i<nums.size(); i++) {
            if (i==0 || nums[i] != nums[i-1]) {
                nums[length++] = nums[i];
            }
        }
        return length;
    }   
};
// @lc code=end

