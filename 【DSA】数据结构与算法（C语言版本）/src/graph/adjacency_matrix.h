#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include <stdio.h>
#include <limits.h>

#define MaxVertexNum 100     // 顶点数目最大值

// 邻接矩阵定义
typedef struct 
{   // 顶点表，数据类型可变，可以存放更复杂信息
    char vex[MaxVertexNum];
    // 邻接矩阵，边表，可以使用bool类型或者枚举类型
    int edge[MaxVertexNum][MaxVertexNum];
    // 图当前的顶点数和边数/弧数
    int vexNum, arcNum;                     
} MGraph;


#define INFINITY  INT_MAX    // 表示无穷

typedef char VertexType;    // 顶点数据类型，可以按照需要重定义
typedef int  EdgeType;      // 带权图上边上权值数据类型，可以按照需要重定义
typedef struct 
{
    // 顶点
    VertexType vex[MaxVertexNum];
    // 边的权              
    EdgeType EdgeType[MaxVertexNum][MaxVertexNum];   
    // 图当前的顶点数和边数/弧数
    int vexNum, arcNum;                             
} MGraph_Weight;

#endif // ADJACENCY_MATRIX_H
