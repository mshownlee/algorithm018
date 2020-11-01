## 课堂笔记

### 1.树

链表linkedList 是特殊的树 tree ，tree是特殊的图grapth



**二叉搜索树：**

* 左子树上所有节点均小于它的根节点

* 右子树上所有节点均大于它的根节点

* 左右子树也为二叉搜索树

* 插入删除查询时间复杂度均为 O(logn)（最坏退还成链表O(n)）



**为什么树适合递归？**

树的定义不太好进行循环，递归写起来相对简单，某个节点的子树具有重复相似性，和递归的特性比较符合。



### 2.树的遍历

- [二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)
- [二叉树的前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)
- [N 叉树的后序遍历](https://leetcode-cn.com/problems/n-ary-tree-postorder-traversal/)
- [N 叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/description/)
- [N 叉树的层序遍历](https://leetcode-cn.com/problems/n-ary-tree-level-order-traversal/)



### 3.堆(优先队列priorityQueue)

* 可以迅速（O(1)）找到一堆数中最大或者最小值的数据结构

* 大顶堆/大根堆（小顶堆/小根堆），二叉堆，斐波那契堆

  

**二叉堆性质**

<img src="D:/工作/geek/学期笔记/image-20201028095828910.png" alt="image-20201028095828910" style="zoom:50%;" />

1. 完全二叉树实现（数组[110,100,90,40,80,20,60,10,30,50,70]）

2. 树中节点的值大于子节点

3. 索引：子节点 2i+1, 2i+2 ，根节点 （i-1）/2

   

**二叉堆的操作**

1. 最值 O(n)：返回根节点
2. 插入 O(logn)：新元素添加到堆尾，从尾部向上调整堆结构（heapifyup）
3. 删除 O(logn)：将堆尾替换删除顶部，从根部向下调整堆结构（heapifydown）

复习：[二叉堆的实现](https://shimo.im/docs/Lw86vJzOGOMpWZz2/)



#### c++中的优先队列

```c++
priority_queue<Type, Container, Functional>
//Type 数据类型  Container 容器类型  Functional 比较的方式
```

```c++
#include <queue>
priority_queue<int, vector<int>, less<int> > a; //大顶堆，默认
priority_queue<int, vector<int>, greater<int> > c;  //小顶堆
```



### 4.图

**属性：**

* Graph(V, E)  : 点和边组成

* V - vertex : 点
  1. 度 - 入度、出度
  2. 点与点连通与否
* E - edge ：边
  1. 有向、无向
  2. 权重（边长）

**存储：**

* 邻接矩阵
* 邻接链表

**算法：**

* dfs
* bfs

注：visited ，环路问题（与树最大区别）

**高级算法：**

拓扑排序、连接图个数、最小生成树



## 刷题笔记

### [242. 有效的字母异位词](https://leetcode-cn.com/problems/valid-anagram/)

* 异位词：各个字符出现的次数一样，顺序不一样的词
* 由于只有26个小写字母，用数组作为简化的哈希表
* 遍历单词，统计各个字符出现的次数
* 若满足题意，数组每个元素为 0 （各字符频率相等）
* 时间复杂度 O(n) 
* 空间复杂度 O(1)

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false; 
        int hash[26] = {0};
        for (int i = 0; i < s.size(); i++) {
            hash[s[i] - 'a']++; // 一增一减，可减少一个遍历
            hash[t[i] - 'a']--;
        }
        for (int j = 0; j < 26; j++) {
            if (hash[j] != 0) return false;
        }
        return true;
    }
};
```

### [49. 字母异位词分组](https://leetcode-cn.com/problems/group-anagrams/)

* 由于异位词排序后是相等的，建立一个哈希表，以排序后的单词作为key，可以用来分组存储异位词
* 时间复杂度 O(nklogk)，其中O(klogk)是对每个最大长度为k的字符串排序
* 空间复杂度 O(nk)

```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> hash;
        for (int i = 0; i < strs.size(); i++) {
            string str = strs[i];
            sort(str.begin(),str.end());
            hash[str].push_back(strs[i]);
        }
        vector<vector<string>> res;
        for (auto it = hash.begin(); it != hash.end(); it++) {
            res.push_back(it->second);
        }
        return res;
    }
};
```

### [589. N叉树的前序遍历](https://leetcode-cn.com/problems/n-ary-tree-preorder-traversal/)

* 模板递归
* 时间和空间复杂度为 O(n) ，n为节点数

```c++
class Solution {
public:
    vector<int> res;
    vector<int> preorder(Node* root) {
        dfs(root);
        return res;
    }
    void dfs(Node* node) {
        if (node == nullptr) return;
        res.push_back(node->val);
        for (int i = 0; i < node->children.size(); i++) {
            dfs(node->children[i]);
        }
    }
};
```

### [94. 二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)

```c++
class Solution {
public:
    vector<int> res;
    vector<int> inorderTraversal(TreeNode* root) {
        inoder(root);
        return res;
    }
    void inoder(TreeNode* root) {
        if (root == nullptr) return;
        inoder(root->left);
        res.push_back(root->val);
        inoder(root->right);
    }
};
```

### [144. 二叉树的前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)

```c++
class Solution {
public:
    vector<int> res;
    vector<int> preorderTraversal(TreeNode* root) {
        preorder(root);
        return res;
    }
    void preorder(TreeNode* root) {
        if (root == nullptr) return;
        res.push_back(root->val);
        preorder(root->left);
        preorder(root->right);
    }
};
```

### [剑指 Offer 49. 丑数](https://leetcode-cn.com/problems/chou-shu-lcof/)

模拟计算的过程：
1 为第一个丑数，取1x2，1x3，1x5中的最小值 1x2 = 2作为第二个丑数，
然后比较1x3，1x5，1x2x2中的最小值 1x3 作为第三个丑数...以此类推可列举：
1，1x2，1x3，1x2x2，1x5，1x2x3(1x3x2)，1x2x2x2...
计算过程有以下规律：
1. 丑数是由小到大排列
2. 下一个丑数由之前的（不一定是上一个）丑数乘以2,3,5求得
3. 保证每一个已经列出来的丑数都乘以2,3,5用作后面的比较（状态转移）

解法：
* 用一个数组记录第n个丑数
* 三指针：q2，q3，q5 ，分别指向已列出来的需要乘以2,3,5的丑数（下标）
* 当指向的值被列举出，下标加一，指向数组中下一个丑数
* 时间复杂度O(n)，只需一次遍历
* 空间复杂度O(n)

```c++
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> nums(n + 1);
        nums[0] = 1;
        int p2 = 0, p3 = 0, p5 = 0;
        for (int i = 1; i < n; i++) {
            nums[i] = min(nums[p2]*2, min(nums[p3]*3, nums[p5]*5));
            if (nums[i] == nums[p2]*2) p2++;
            if (nums[i] == nums[p3]*3) p3++;
            if (nums[i] == nums[p5]*5) p5++;
        }
        return nums[n-1];
    }
};
```

### [347. 前 K 个高频元素](https://leetcode-cn.com/problems/top-k-frequent-elements/)

解法一：哈希表+优先队列

* 用哈希表统计出现次数，一次遍历记录频率

* 维护一个大顶堆，将所有频率-数值pair存放到堆后，将前k个元素保存到结果res中
* 时间复杂度 O(nlogn)
* 空间复杂度 O(n)

```c++
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> map;
    for(int num : nums){
        map[num]++;
    }
    vector<int> res;
    priority_queue<pair<int, int>> pq; // 大顶堆
    for(auto it = map.begin(); it != map.end(); it++){
        pq.push(make_pair(it->second, it->first));
    }
    while (res.size() < k) {
        res.push_back(pq.top().second);
        pq.pop();
    }
    return res;
}
```

解法二：哈希表+调用排序函数

* 哈希表统计出现次数，遍历计数值
* 转存为数组，并对数组排序，输出前k项
* 时间复杂度 O(nlogn)
* 空间复杂度 O(n)

```c++
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hash;
        for (auto num: nums) {
            hash[num]++;
        }
        vector<pair<int, int>> data;
        vector<int> res;
        for (auto freq : hash) {
            data.push_back(make_pair(freq.second, freq.first));
        }
        sort(data.begin(), data.end());
        for (int i = data.size() - 1, count = 0; count < k; i--, count++) {
            res.push_back(data[i].second);
        }
        return res;
    }
};
```

