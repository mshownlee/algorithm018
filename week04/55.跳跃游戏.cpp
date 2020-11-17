// 傻递归，剪枝去重（最近递归做多了hh）
class Solution {
public:
    bool ans = false;
    bool canJump(vector<int>& nums) {
        jump(nums, 0);
        return ans;
    }

    void jump(vector<int>& nums, int i) {
        int len = nums[i];
        nums[i] = -1; // 访问过的节点标记为 -1
        if (len + i >= nums.size() - 1) {
            ans = true;
            return;
        }
        for (int j = len; j > 0; j--) {  
            // ans为正，或节点已被访问，直接返回
            if (ans || nums[i + j] == -1) return; 
            jump(nums, i + j);
        }
    }
};