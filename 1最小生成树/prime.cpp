#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#define VEX_COUNT 6

using namespace std;

char vertex[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

// 邻接表结构：更节省空间，适合稀疏图
vector<vector<pair<int, int>>> buildAdjList() {
    vector<vector<pair<int, int>>> adj(VEX_COUNT);
    // 填充边权（无向图）
    adj[0].push_back({1, 6}); adj[0].push_back({2, 1}); adj[0].push_back({3, 5});
    adj[1].push_back({0, 6}); adj[1].push_back({2, 5}); adj[1].push_back({4, 3});
    adj[2].push_back({0, 1}); adj[2].push_back({1, 5}); adj[2].push_back({3, 5});
    adj[2].push_back({4, 6}); adj[2].push_back({5, 4});
    adj[3].push_back({0, 5}); adj[3].push_back({2, 5}); adj[3].push_back({5, 2});
    adj[4].push_back({1, 3}); adj[4].push_back({2, 6}); adj[4].push_back({5, 6});
    adj[5].push_back({2, 4}); adj[5].push_back({3, 2}); adj[5].push_back({4, 6});
    return adj;
}

void primOptimal(vector<vector<pair<int, int>>>& adj, int start) {
    vector<int> key(VEX_COUNT, INT_MAX);  // key[i]表示顶点i到生成树的最小边权
    vector<int> parent(VEX_COUNT, -1);    // parent[i]记录顶点i在生成树中的父节点
    vector<bool> inMST(VEX_COUNT, false); // 标记顶点是否已加入生成树

    // 优先队列：存储格式为 (key值, 顶点索引)，最小堆优先取key最小的顶点
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[start] = 0;       // 起始点key设为0
    pq.push({0, start});  // 初始将起始点入队

    while (!pq.empty()) {
        int u = pq.top().second; // 取出当前key最小的顶点u
        pq.pop();

        if (inMST[u]) continue; // 已处理的顶点直接跳过
        inMST[u] = true;        // 标记u已加入生成树

        // 输出生成树的边（排除起始点）
        if (parent[u] != -1) {
            cout << vertex[parent[u]] << " -> " << vertex[u] 
                 << " (cost: " << key[u] << ")" << endl;
        }

        // 遍历u的所有邻接顶点v
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            // 若v未在生成树中，且当前边权更小
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;     // 更新v的key值
                parent[v] = u;       // 设置v的父节点为u
                pq.push({key[v], v});// 将新key值入队（允许重复，旧值会被跳过）
            }
        }
    }
}

int main() {
    auto adj = buildAdjList(); // 构建邻接表
    cout << "Optimized Prim with Priority Queue:\n";
    primOptimal(adj, 0);      // 从A（下标0）开始
    return 0;
}
