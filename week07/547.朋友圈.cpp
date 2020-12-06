class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        vector<bool> visited(M.size());
        int count = 0;
        for (int i = 0; i < M.size(); i++) {
            if (!visited[i]) {
                dfs(M, visited, i);
                count++;
            }
        }
        return count;
    }
    void dfs(vector<vector<int>>& M, vector<bool>& visited, int i) {
        for (int j = 0; j < M.size(); j++) {
            if (M[i][j] == 1 && !visited[j]) {
                visited[j] = true;
                dfs(M, visited, j);
            }
        }
    }
};