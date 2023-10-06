#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <stdio.h>
#include <limits.h>

#define MaxVertexNum 100    // 顶点数目最大值
typedef char VertexType;    // 顶点数据类型，可以按照需要重定义

// 边，弧
typedef struct ArcNode
{
    int adjVex;             // 边、弧指向哪个结点
    ArcNode *next;          // 指向下一条弧的指针
    // InfoType info;       // 边权值
} ArcNode;

// 顶点
typedef struct VNode {
    VertexType data;        // 顶点信息
    ArcNode *first;         // 第一条边/弧
} VNode, AdjList[MaxVertexNum];

// 用邻接表存储的图
typedef struct adjacency_list
{
    AdjList vertices;
    int vexNum, arcNum;
} ALGraph;      // Adjacency List Graph

#endif // ADJACENCY_LIST_H
