/*
 * @lc app=leetcode.cn id=347 lang=cpp
 *
 * [347] 前 K 个高频元素
 */

// @lc code=start
class Solution {
public:
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
};
// @lc code=end

