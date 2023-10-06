#include <stdio.h>
#include <stdbool.h>

#include "adjacency_matrix.h"
#ifdef ADJACENCY_MATRIX_H
typedef MGraph Graph;
typedef struct Queue
{
    int data[100];
    int rear, front;
} Queue;

void visit(int v)
{
    /* ....code... */
}

void Init(Queue q) {
    /* ....code... */
}

void EnQueue(Queue q, int val) {
    /* ....code... */
}

void DeQueue(Queue q, int val) {
    /* ....code... */
}

bool IsEmptyQue(Queue q) {
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

Queue Q;
int w;

/**************** 实现BFS  *******************/

bool visited[MaxVertexNum];   // 访问标记数组

// 对图G进行广度优先遍历
void BFSTraverse(Graph G)
{
    // 初始化标记数组
    for (int i = 0; i < G.vexNum; i++) {
        visited[i] = false;
    }

    Init(Q);
    // 从起始点开始遍历
    for (int i = 0; i < G.vexNum; i++)
    {
        if (!visited[i]) {  // 对每一个连通分量调用一次BFS
            BFS(G, i);      // 防止出现隔离的顶点
        }
    }
}

// 广度优先遍历
void BFS(Graph G, int v)
{
    visit(v);   // 从顶点出发开始遍历
    visited[v] = true;      // v已经被访问到
    EnQueue(Q, v);          // 将v压入队列Q
    while (!IsEmptyQue(Q)) {
        DeQueue(Q, v);      // v出队列Q
        
        // 检测v的所有邻接顶点
        for (w = FirstNeighbor(G, v) ;w >= 0; w = NextNeighbor(G, v, w))
        {
            if (!visited[w])    // w为未曾访问的顶点
            {
                visit(w);       // 访问
                visited[w] = true;
                EnQueue(Q, w);  // 再将w顶点压入队列中
            } 
        }
    }
}

#endif