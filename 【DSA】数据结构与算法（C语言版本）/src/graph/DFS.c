#include <stdio.h>
#include <stdbool.h>

#include "adjacency_matrix.h"
#ifdef ADJACENCY_MATRIX_H
typedef MGraph Graph;

void visit(int v)
{
    /* ....code... */
}

// 图G中顶点x的第⼀个邻接点
int FirstNeighbor(Graph G, int v){
    /* ....code... */
}

// 返回除自身之外顶点w的下⼀个邻接点的顶点号
int NextNeighbor(Graph G, int v, int w){
    /* ....code... */
}

int w;

/**************** 实现DFS  *******************/
bool visited[MaxVertexNum];   // 访问标记数组

// 对图G进行深度优先遍历
void DFSTraverse(Graph G)
{
    // 初始化标记数组
    for (int i = 0; i < G.vexNum; i++) {
        visited[i] = false;
    }
    // 从起始点开始遍历
    for (int i = 0; i < G.vexNum; i++)
    {
        if (!visited[i]) {  // 对每一个连通分量调用一次DFS
            DFS(G, i);      // 防止出现隔离的顶点
        }
    }
}

void DFS(Graph G, int v)
{
    visit(v);               // 访问顶点v
    visited[v] = true;      // 更新标记数组

    // 检测v的下一个邻接顶点
    for (w = FirstNeighbor(G, v) ;w >= 0; w = NextNeighbor(G, v, w))
    {
        if (!visited[w])
        {
            DFS(G,w);
        }
    }
}



#endif