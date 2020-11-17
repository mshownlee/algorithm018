/*
 * @lc app=leetcode.cn id=322 lang=cpp
 *
 * [322] 零钱兑换
 */

// @lc code=start
class Solution {
public:
    int ans = INT_MAX;
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.rbegin(), coins.rend()); // 从大到小排序，优先选取大数
        dfs(coins, amount, 0, 0);
        return ans == INT_MAX ? -1 : ans;
    }
    void dfs(vector<int>& coins, int amount, int index, int count) {
        if (amount == 0) {  // 能够兑换的情况、取最小值
            ans = min(ans, count);
            return;
        }
        if (index == coins.size()) return;
        // 优先选取最大可能个数，注意ount + k < ans这个剪枝条件，若作为结束条件会超时（函数调用开销）
        for (int k = amount / coins[index]; k >= 0 && count + k < ans; k--){
            dfs(coins, amount - k * coins[index], index + 1, count + k);
        }
    }
};
// @lc code=end

