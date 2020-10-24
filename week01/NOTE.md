

## 刷题笔记

### 两数之和

根据题意，一次遍历，用哈希表记录当前数值以及下标，若表中存在$target - nums[i]$，说明当前值与表中值之和等于 $target$ ，返回两数下标。

```c++
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
```



### 三数之和

解法一：双指针

1. 排序

2. 外层循环，遍历每个数，转化为两数之和等于$0-num[i]$问题

3. 内层循环，双指针 $l,r$ 夹逼遍历另外两个数：

   若$nums[l]+nums[r]$小于目标值，$l$往右找到更大值；

   若$nums[l]+nums[r]$小于目标值，$r$往左找到更小值；

   若等于，保存结果，并进行去重操作：由于已经排序，只需比较相邻元素。

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        // 外层循环，遍历每个数，内层循环用双指针夹逼遍历另外两个数
        for (int i = 0;i<nums.size();i++) {
            if(i > 0 && nums[i] == nums[i-1]) continue;
            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                int curSum = nums[l] + nums[r];
                if (curSum + nums[i] == 0) {
                    res.push_back(vector<int>{nums[i], nums[l], nums[r]});
                    while (l < r && nums[l] == nums[++l]);// 去重
                    while (l < r && nums[r] == nums[--r]);
                }else if (curSum + nums[i] < 0) l++;
                else r--;
            }
        }
        return res;
    }
};
```

### 环形链表

解法一：快慢指针

快慢指针遍历，fast指针每次走两步，slow指针走一步，若存在环两指针会相遇（相等），否则遍历到null值，说明不形成环。 

```c++
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) return true;
        }
        return false;
    }
};
```

### 删除排序数组中的重复项

解法一：双指针

快指针 $i$ 将数组遍历一次，把遇到的非重复元素放到数组前面，插入的下标用慢指针 $j$ 维护，保证 $j$ 之前的元素不含重复项，遍历完成后 $ j$ 即为结果数组的长度。

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int j = 0;
        for (int i = 0; i<nums.size(); i++) {
            if (i==0 || nums[i] != nums[i-1]) {
                nums[j++] = nums[i];
            }
        }
        return j;
    }   
};
```



### 移动零

解法一：双指针

第一遍遍历，将所有非零元素依次放到数组前面，用 $j$ 维护当前下标，第二遍遍历从最后的 $j$ 开始补零

```c++
void moveZeroes(vector<int>& nums) {
    int j = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[j++] = nums[i];
        }
    }
    for (int i = j; i < nums.size(); i++) {
        nums[i] = 0;
    }
}
```

解法二：双指针

慢指针 $j$ 之前的左右元素非零，当遇到零之后总是指向第一个零元素（最后一个非零元素之后），遍历过程中将非零元素与位于 $j $ 的元素交换，能保证 $i  j$ 之间都是零，一次遍历完成即实现**非零**元素与**零**元素**左右分隔**。

```c++
class Solution { 
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;
        for (int i = 0; i<nums.size(); i++) 
            if (nums[i] != 0) swap(nums[i], nums[j++]);
    }
};
```



### [66. 加一](https://leetcode-cn.com/problems/plus-one/)

给定一个由**整数**组成的**非空**数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储**单个**数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

**示例 1:**

```
输入: [1,2,3]
输出: [1,2,4]
解释: 输入数组表示数字 123。
```

**示例 2:**

```
输入: [4,3,2,1]
输出: [4,3,2,2]
解释: 输入数组表示数字 4321。
```



解法一：

根据题意，从数组末尾开始遍历，若 $digits[i] \% 10 = 0 $ 说明当前位的数值加一后等于10，进一；反之，说明加一后数值在 1~9范围内，无进位，因此返回。

特殊情况：若数组所有元素为9，数组需要扩容进一 [9,9,9] -> [1,0,0,0]

```c++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1; i >= 0; i--) {
            digits[i]++;
            digits[i] %= 10;
            if (digits[i] != 0) return digits;
        }
        digits.insert(digits.begin(),1);
        return digits;
    }
};
```

### [88. 合并两个有序数组](https://leetcode-cn.com/problems/merge-sorted-array/)

给你两个有序整数数组 *nums1* 和 *nums2*，请你将 *nums2* 合并到 *nums1* 中*，*使 *nums1* 成为一个有序数组。

 

**说明：**

- 初始化 *nums1* 和 *nums2* 的元素数量分别为 *m* 和 *n* 。
- 你可以假设 *nums1* 有足够的空间（空间大小大于或等于 *m + n*）来保存 *nums2* 中的元素。

 

**示例：**

```
输入：
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出：[1,2,2,3,5,6]
```

 

解法一：双指针

1. 使用倒序遍历，避免开辟新数组（空间↓）或增加交换次数（时间↓）
2. 初始化三个指针 $tail$ 指向合并后数组的尾部，$m$ 为数组1尾部，$n$ 为数组2尾部
3. $tail$遍历，将两个数组中的较大值插入合并数组（数组1后部），同时移动较大者对应下标

```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int tail = m + n -1;
        m--; n--;
        while (n >= 0 && tail >= 0) {
            nums1[tail--] = m >= 0 && nums1[m] > nums2[n]? nums1[m--]: nums2[n--]; 
        }
    }
};
```



### [21. 合并两个有序链表](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 



**示例：**

```
输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
```



解法一：双指针迭代

1. new一个新的链表，逐个节点尾插
2. 分别遍历两个链表，遇到较小值则插入新链表尾部，指向下个节点

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *p = new ListNode(0);
        ListNode *res = p;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val > l2->val) {
                p->next = new ListNode(l2->val); // 或 p->next = l2
                l2 = l2->next;
            }else {
                p->next = new ListNode(l1->val);// 或 p->next = l1
                l1 = l1->next;
            }
            p = p->next;
        }
        p->next = l1 != nullptr? l1: l2;
        return res->next;
    }
};
```



解法二：递归

1.  $l1[0]->merge(l1[1],l2),l1[0]>l2[0]$ 

    or $l2[0]->merge(l1,l2[1])$，otherwise

```c++
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) return l2;
        if (l2 == nullptr) return l1;
        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }else{
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};
```



### [189. 旋转数组](https://leetcode-cn.com/problems/rotate-array/)

给定一个数组，将数组中的元素向右移动 *k* 个位置，其中 *k* 是非负数。

**示例 1:**

```
输入: [1,2,3,4,5,6,7] 和 k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]
```



解法一：三次反转

```c++
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
```

