#include <iostream>
#define INF 0x7FFFFFFF   // 无穷大（不可达）
#define VEX_COUNT 6   // 顶点数量

char vertex[] = { 'A', 'B', 'C', 'D', 'E', 'F' }; // 顶点名称

// 邻接矩阵初始化（手动输入示例图的边权）
void initAdjMatrix(int adjMat[][VEX_COUNT]) {
    for (int i = 0; i < VEX_COUNT; i++)
        for (int j = 0; j < VEX_COUNT; j++)
            adjMat[i][j] = INF;

    // 填充实际边权（无向图对称赋值）
    adjMat[0][1] = 6; adjMat[0][2] = 1; adjMat[0][3] = 5;
    adjMat[1][0] = 6; adjMat[1][2] = 5; adjMat[1][4] = 3;
    adjMat[2][0] = 1; adjMat[2][1] = 5; adjMat[2][3] = 5; adjMat[2][4] = 6; adjMat[2][5] = 4;
    adjMat[3][0] = 5; adjMat[3][2] = 5; adjMat[3][5] = 2;
    adjMat[4][1] = 3; adjMat[4][2] = 6; adjMat[4][5] = 6;
    adjMat[5][2] = 4; adjMat[5][3] = 2; adjMat[5][4] = 6;
}

// Prim算法核心实现
void primMST(int adjMat[][VEX_COUNT], int start) {
    struct Node {
        int prev;     // 连接到生成树的哪个顶点
        int minCost;  // 到生成树的最小边权
    } closedge[VEX_COUNT]; // 关键结构：记录每个顶点的最小连接信息

    // 初始化所有顶点信息
    for (int i = 0; i < VEX_COUNT; i++) {
        closedge[i].minCost = INF;
        closedge[i].prev = -1;
    }
    closedge[start].minCost = 0; // 起点加入生成树

    // 初始化起点邻接边
    for (int i = 0; i < VEX_COUNT; i++) {
        if (i != start) {
            closedge[i].minCost = adjMat[start][i];
            closedge[i].prev = start;
        }
    }

    int totalCost = 0;

    // 主循环：每次加入一个新顶点
    for (int step = 0; step < VEX_COUNT - 1; step++) {
        // 选出当前最小边
        int minVal = INF, select = -1;
        for (int i = 0; i < VEX_COUNT; i++) {
            if (closedge[i].minCost != 0 && closedge[i].minCost < minVal) {
                minVal = closedge[i].minCost;
                select = i;
            }
        }

        // 输出选择的边
        if (select != -1) {
            std::cout << vertex[closedge[select].prev]
                      << " -> " << vertex[select]
                      << " (cost: " << minVal << ")\n";
            totalCost += minVal;
            closedge[select].minCost = 0; // 加入生成树
        }

        // 更新 closedge
        for (int neighbor = 0; neighbor < VEX_COUNT; neighbor++) {
            if (adjMat[select][neighbor] < closedge[neighbor].minCost) {
                closedge[neighbor].minCost = adjMat[select][neighbor];
                closedge[neighbor].prev = select;
            }
        }
    }

    std::cout << "Total Cost of MST: " << totalCost << "\n";
}

int main() {
    int adjMat[VEX_COUNT][VEX_COUNT];
    initAdjMatrix(adjMat);  // 初始化邻接矩阵

    std::cout << "Minimum Spanning Tree (Prim):\n";
    primMST(adjMat, 0); // 从顶点A（下标0）开始生成

    return 0;

}
