#ifndef ORTHOGONAL_LINKED_LIST
#define ORTHOGONAL_LINKED_LIST

#include <stdio.h>
#include <limits.h>

#define  MaxVertexNum 100   // 图中顶点的最大数量

typedef char VertexType;    // 图中顶点的数据类型
typedef float InfoType;      // 表示弧额外信息的数据类型

// 表示链表中存储弧的结点
typedef struct ArcBox {
    int tailvex, headvex;           // 弧尾、弧头对应顶点在顺序表中的位置下标
    struct ArcBox* hlik, * tlink;   // hlik 指向下一个以当前顶点为弧头的弧结点；
                                    // tlink 指向下一个以当前顶点为弧尾的弧结点；
    // InfoType info;               // 存储弧相关信息的指针,有向边的权
} ArcBox;

// 表示顺序表中的各个顶点
typedef struct VexNode {
    VertexType data;                // 顶点的数据域
    ArcBox* firstin, * firstout;    // 指向以该顶点为弧头和弧尾的链表首个结点
} VexNode;

// 表示十字链表存储结构
typedef struct {
    VexNode xlist[MaxVertexNum];    // 存储顶点的顺序表
    int vexnum, arcnum;             // 记录图的顶点数和弧数
} OLGraph;

#endif // ORTHOGONAL_LINKED_LIST