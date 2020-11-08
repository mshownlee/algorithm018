## 课堂笔记

### 递归recursion

代码模板

```c++
// C/C++
void recursion(int level, int param) { 
  // recursion terminator 递归终止条件
  if (level > MAX_LEVEL) { 
    // process result 
    return ; 
  }

  // process current logic  处理当前层的逻辑
  process(level, param);

  // drill down   下探到下一层
  recursion(level + 1, param);

  // reverse the current level status if needed  清理当前层
}
```

解题思维

1. 不要人肉递归
2. 找到最近重复子问题
3. 数学归纳法

### 实战题目

[爬楼梯](https://leetcode-cn.com/problems/climbing-stairs/)

* 傻递归时间复杂度为 $O(2^n)$ 

```c++
int climbStairs(int n) {
    if(n<2) return 1;
    return climbStairs(n-1)+climbStairs(n-2);
}
```

* 使用一个数组记录已经计算过的状态

```c++
int climbStairs(int n) {
    vector<int> memo(n+1, -1);
    return recur(n,memo);
}
int recur(int n, vector<int>& memo) {
    if (n < 2) return 1;
    if (memo[n] != -1) return memo[n];
    memo[n] = recur(n-1, memo) + recur(n-2, memo);
    return memo[n];
}
```



[括号生成](https://leetcode-cn.com/problems/generate-parentheses/)

* n 对括号 ，转化为 2*n个空位填左括号或者右括号问题
* 若不考虑括号的有效性，暴力递归即可

```c++
vector<string> res;
vector<string> generateParenthesis(int n) {
    generate(n, "");
    return res;
}
void generate(int n, string cur) {
    if (2*n == cur.size()) {
        res.push_back(cur);
        return;
    }
    generate(n, cur + "(");
    generate(n, cur + ")");
}
```

* 有效括号满足两个条件：1.填右括号之前必须要有足够多的左括号（left < right）2.左/右括号不超过n
* 因此，可以在递归的过程中生成有效括号，增加相应的条件判断和参数即可（实质是剪枝的操作）

```c++
vector<string> res;
vector<string> generateParenthesis(int n) {
    generate(n, "", 0, 0);
    return res;
}
void generate(int n, string cur, int left, int right) {
    if (2*n == cur.size()) {
        res.push_back(cur);
        return;
    }
    if (left < n) generate(n, cur + "(", left + 1, right);
    if (right < left) generate(n, cur + ")", left, right + 1);
}
```



### 分治、回溯

分治模板

```c++
int divide_conquer(Problem *problem, int params) {
  // recursion terminator
  if (problem == nullptr) {
    process_result
    return return_result;
  } 

  // process current problem
  subproblems = split_problem(problem, data)
  subresult1 = divide_conquer(subproblem[0], p1)
  subresult2 = divide_conquer(subproblem[1], p1)
  subresult3 = divide_conquer(subproblem[2], p1)
  ...

  // merge
  result = process_result(subresult1, subresult2, subresult3)
  // revert the current level status
 
  return 0;
}
```



## 习题笔记

### [从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal)

* 模拟用前序序列和中序序列构建二叉树的过程：
* <img src="./无标题的笔记本 2.png" alt="无标题的笔记本 2" style="zoom: 33%;" />
* 左子树、右子树的构建为子问题，因此可用递归解决
* root1，root2为下标，分别指向构建当前子树的子序列起始位置，并用len记录其长度
* 每一层的处理逻辑： 前序遍历序列首个元素为当前子树的根节点，并在中序遍历序列找到根/中节点，以此二分为左右子树构建的递归
* 时间和空间复杂度为 O(n)

```c++
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.size() != inorder.size()) return NULL;
    return build(preorder, inorder, 0, 0, preorder.size());
}

TreeNode* build(vector<int>& preorder, vector<int>& inorder, int root1, int root2, int len) {
    // 终止条件
    if (root1 >= preorder.size() || root2 >= inorder.size() || len == 0) return NULL;
    // 前序遍历序列首个元素为根/中节点
    int rootVal = preorder[root1];
    TreeNode* node = new TreeNode(rootVal);
    // 在中序遍历序列找到根/中节点
    int i = root2;
    for (; i < inorder.size(); i++) {
        if (preorder[root1] == inorder[i]) break;
    }
    // 计算左右子树的长度，往下一层
    int leftLen = i - root2;
    int rightLen = len - leftLen - 1;
    node->left = build(preorder, inorder, root1 + 1, root2, leftLen);
    node->right = build(preorder, inorder, root1 + 1 + leftLen, root2 + leftLen + 1, rightLen);
    // 返回当前节点
    return node;
}
```

* 优化：将前序遍历的根节点在中序遍历序列中的位置用一个哈希表记录下来，减少的查找时间

```c++
unordered_map<int, int> hash; // 构建哈希表，减少查找时间
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    if (preorder.size() != inorder.size()) return NULL;
    for (int i = 0; i < inorder.size(); i++) {
        hash[inorder[i]] = i;
    }
    return build(preorder, inorder, 0, 0, preorder.size());
}
TreeNode* build(vector<int>& preorder, vector<int>& inorder, int root1, int root2, int len) {
    // 终止条件
    if (root1 >= preorder.size() || root2 >= inorder.size() || len == 0) return NULL;
    // 前序遍历序列首个元素为根/中节点
    int rootVal = preorder[root1];
    TreeNode* node = new TreeNode(rootVal);
    // 在中序遍历序列找到根/中节点
    int i = hash[rootVal];
    // 计算左右子树的长度，往下一层
    int leftLen = i - root2;
    int rightLen = len - leftLen - 1;
    node->left = build(preorder, inorder, root1 + 1, root2, leftLen);
    node->right = build(preorder, inorder, root1 + 1 + leftLen, root2 + leftLen + 1, rightLen);
    // 返回当前节点
    return node;
}
```



### [组合](https://leetcode-cn.com/problems/combinations/)

* 套用回溯法模板

```c++
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
```

* 另一种写法

```c++
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
    if (index > n) return;  // 终止条件
    path.push_back(index);
    backtrack(n, k, path, index+1); // 取当前元素，调用下层
    path.pop_back();
    backtrack(n, k, path, index+1); // 不取当前元素，调用下层
}
```





### [全排列](https://leetcode-cn.com/problems/permutations/)

* 标准回溯法
* 使用visited数组记录某位置已被选取（true），在回溯时刷新状态（false）
* 时间复杂度：O(n x n!)
* 空间复杂度：O(n)

```c++
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
```



### [全排列 II ](https://leetcode-cn.com/problems/permutations-ii/)

* 思路同上题，关键的处理是加入了两行去重的代码

* 排序以方便去重

* 去重条件判断（剪枝） [参考解释](https://leetcode-cn.com/problems/permutations-ii/solution/hui-su-suan-fa-python-dai-ma-java-dai-ma-by-liwe-2/) ，若当前元素与数组中前元素一致时，若前一个元素visited为false（由于同一层是顺序遍历，第一个重复元素已经开出了分支，visited是回溯成的false）

  <img src="https://pic.leetcode-cn.com/1600386643-uhkGmW-image.png" alt="image.png" style="zoom:50%;" />

```c++
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
```



### [二叉树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)

* 使用后序遍历，将状态（是否包含给定目标节点）往上递归，满足条件的节点记录为最近公共祖先

```c++
TreeNode* ans;
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    dfs(root, p, q);
    return ans;
}
bool dfs(TreeNode* root, TreeNode * p, TreeNode* q) {
    if (root == NULL) return false;
    bool lson = dfs(root->left, p, q);
    bool rson = dfs(root->right, p, q);
    if (lson && rson || (root == p || root == q)) ans = root; 
    return lson || rson || (root == p || root == q); 	 // 状态传递
}
```

