/*
 * @lc app=leetcode.cn id=589 lang=cpp
 *
 * [589] N叉树的前序遍历
 */

// @lc code=start
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

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
// @lc code=end

