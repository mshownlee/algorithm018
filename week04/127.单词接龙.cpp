/*
 * @lc app=leetcode.cn id=127 lang=cpp
 *
 * [127] 单词接龙
 */

// @lc code=start
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 将字典中的单词存入set，方便查找
        unordered_set<string> list;
        for (int i = 0; i < wordList.size(); i++) {
            list.insert(wordList[i]);
        }
        // 维护一个队列，每个元素为中间词及其层数
        queue<pair<string, int>> q;
        q.push(make_pair(beginWord, 1));
        while (!q.empty()) {
            pair<string, int> cur = q.front();
            q.pop();
            string word = cur.first;
            int level = cur.second;
            if (word == endWord) { // 满足条件即返回
                return level;
            }
            for (int i = 0; i < word.size(); i++) {
                for (char j = 'a'; j <= 'z'; j++) { 
                    string newWord = word;
                    newWord[i] = j; // 将当前单词任一位置替换
                    if (list.count(newWord)) { // 若替换后的单词存在于字典中
                        q.push(make_pair(newWord, level + 1)); // 作为下一层的词入列
                        list.erase(newWord); // 从字典删除当前中间单词，防止反复
                    }
                }
            }
        }
        return 0;
    }
};
// @lc code=end

