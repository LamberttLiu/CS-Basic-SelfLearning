#ifndef ADJACENCY_MULTI_LIST_H
#define ADJACENCY_MULTI_LIST_H

#include <stdio.h>
#include <limits.h>

#define  MaxVertexNum 100   // 图中顶点的最大数量

typedef char VertexType;    // 图中顶点的数据类型
typedef float InfoType;      // 表示弧额外信息的数据类型

// 边标志域
typedef enum { 
    unvisited  = 0, 
    visited
} VisitIf;

// 表示链表中的各个结点
typedef struct EBox {
    VisitIf mark;                   // 标志域
    int ivex, jvex;                 // 边两边顶点在顺序表中的位置下标
    struct EBox* ilink, * jlink;    // 分别指向与ivex、jvex相关的下一个边结点
    InfoType* info;                 // 边的其它信息
} EBox;

// 存储图中的各个顶点
typedef struct VexBox {
    VertexType data;                // 顶点数据域
    EBox* firstedge;                // 指向当前顶点对应的链表
} VexBox;

// 表示邻接多重表结构
typedef struct {
    VexBox adjmulist[MaxVertexNum]; // 存储图中顶点的顺序表
    int vexnum, edgenum;            // 记录图中的顶点数量和边数量
} AMLGraph;

#endif // ADJACENCY_MULTI_LIST_H