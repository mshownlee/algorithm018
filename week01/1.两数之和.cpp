/*
 * @lc app=leetcode.cn id=1 lang=cpp
 *
 * [1] 两数之和
 */

// @lc code=start
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> hash;
        for (int i = 0; i < nums.size(); i++) {
            int numToFind = target - nums[i];
            if (hash.count(numToFind)) {
                return vector<int> {i, hash[numToFind]};
            }
            hash[nums[i]] = i;
        }    
        return vector<int>();
    }
};
// @lc code=end

