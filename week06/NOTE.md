# 动态规划

和递归、分治没有本质区别，

共性：找重复子问题

差异：动规有最优子结构，中途淘汰次优解



思考：动态规划的代码一般比较简洁，关键是如何将问题转化为动态规划，找到状态转移关系，状态数组，

### [62. 不同路径](https://leetcode-cn.com/problems/unique-paths/)

重复子问题：每次移动到某个位置，即一个从该点出发到终点的子问题

状态数组：dp[i] [j] 到达（i,j）的路径数

最优子结构：某个位置只能由上方或者左方到达，根据题意需要考虑所有可能路径，所以将状态累加

$dp[i][j] = dp[i - 1][j] + dp[i][j - 1]$

初值：由于只能往下或者往右走，沿第一行或第一列各为一种走法，这些位置的状态值为1

```c++
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // 赋予第一行，第一列初值
    for (int i = 0; i < n; i++) dp[0][i] = 1;
    for (int j = 0; j < m; j++) dp[j][0] = 1;
    // 遍历迭代
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}
```

空间压缩：由于当前状态由上一行以及当前行的左边得，只需要存储一行状态值即可

```c++
int uniquePaths(int m, int n) {
    vector<int> dp(n, 1); // 初始化“第一行”为 1
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[j] += dp[j - 1];
        }
    }
    return dp[n - 1];
}
```



### [63. 不同路径 II](https://leetcode-cn.com/problems/unique-paths-ii/)

思路同上，需要判断是否为障碍物

```c++
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size();
    if (m == 0 || obstacleGrid[0][0]) return 0;// 出门即障碍物，无路可走
    int n = obstacleGrid[0].size();
    vector <int> dp(n); // 空间压缩为一维
    dp[0] = 1; // 初始化，若只有一格，则计为1
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (obstacleGrid[i][j] == 1) dp[j] = 0; // 当前为障碍物，状态置 0 
            else if (j > 0) dp[j] += dp[j - 1];
        }
    }
    return dp[n - 1];
}
```



这周由于个人原因，时间没有合理安排，动态规划这一章节仅用了周末一点时间把视频看完，再动手做了几道题。视频一遍过完觉得超哥讲得非常深入浅出，几乎是手把手教从易到难。虽然这期学习没有好好完成，相信后续多过几遍、多加练习能把这块内容补上来，不能浪费这么好的课程，加油吧。