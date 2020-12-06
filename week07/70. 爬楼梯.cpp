class Solution {
public:
    int recur(int n, vector<int>& memo) { // 采用记忆化搜索、剪枝
        if (n < 2) return 1;
        if (memo[n] != -1) return memo[n];
        memo[n] = recur(n-1, memo) + recur(n-2, memo);
        return memo[n];
    }
    int climbStairs(int n) {
        vector<int> memo(n+1, -1);
        return recur(n,memo);
    }
};