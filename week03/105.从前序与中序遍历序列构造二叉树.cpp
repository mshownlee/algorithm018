/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
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
};
// @lc code=end

