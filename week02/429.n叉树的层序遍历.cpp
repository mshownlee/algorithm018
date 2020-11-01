/*
 * @lc app=leetcode.cn id=429 lang=cpp
 *
 * [429] N叉树的层序遍历
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
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> res;
        queue<Node*> que;
        que.push(root);
        while (!que.empty() && root) {
            int size = que.size();
            vector<int> vals;
            while (size--) {
                Node *tmp = que.front();
                que.pop();
                vals.push_back(tmp->val);
                for (int i = 0; i < tmp->children.size(); i++) {
                    que.push(tmp->children[i]);
                }
            }
            res.push_back(vals);
        }
        return res;
    }
};


// @lc code=end

