#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BiTNode
{
    int data;                           // 数据域
    struct BiTNode *lchild, *rchild;    // 左右孩子指针
} BiTNode, *BiTree;

// 初始化队头和队尾指针开始时都为0
int front = 0, rear = 0;



// 入队函数
void EnQueue(BiTree *a, BiTree node)
{
    a[rear++] = node;
}

// 出队函数
BiTNode *DeQueue(BiTree *a)
{
    return a[front++];
}

// 输出函数
void OutputNode(BiTree node)
{
    printf("%d ", node->data);
}

/**********************
    测试代码框架
    二叉树结构：
        1
       /  \
      2    3 
     / \   / 
    4   5 6
   /
  7
**********************/ 

// 程序执行即结束，free
BiTree CreateBiTree()
{
    // 1
    BiTree tree = NULL;
    tree = (BiTNode*)malloc(sizeof(BiTNode));
    tree->data = 1;

    // 2、3
    BiTree tree_2 = (BiTNode*)malloc(sizeof(BiTNode));
    tree_2->data = 2;
    BiTree tree_3 = (BiTNode*)malloc(sizeof(BiTNode));
    tree_3->data = 3;
    tree->lchild = tree_2, tree->rchild = tree_3;
    tree_3->rchild = NULL;

    // 4、5
    BiTree tree_4 = (BiTNode*)malloc(sizeof(BiTNode));
    tree_4->data = 4;
    BiTree tree_5 = (BiTNode*)malloc(sizeof(BiTNode));
    tree_5->data = 5;
    tree_2->lchild = tree_4, tree_2->rchild = tree_5;

    tree_4->rchild = NULL;
    tree_5->lchild = NULL, tree_5->rchild = NULL;

    // 6
    BiTree tree_6 = (BiTNode*)malloc(sizeof(BiTNode));
    tree_6->data = 6;
    tree_3->lchild = tree_6;

    tree_6->lchild = NULL, tree_6->rchild = NULL;

    // 7
    BiTree tree_7 = (BiTNode*)malloc(sizeof(BiTNode));
    tree_7->data = 7;
    tree_4->lchild = tree_7;
    tree_7->lchild = NULL, tree_7->rchild = NULL;
    
    return tree;
}

// 预期输出： 1 2 3 4 5 6 7  ---> 层序遍历
int main()
{
    BiTree tree = CreateBiTree();

    BiTNode *p;
    BiTree a[20];           // 采用顺序队列，初始化创建队列数组
    EnQueue(a, tree);       // 根结点入队
    while (front < rear)    // 当队头和队尾相等时，表示队列为空
    {   
        p = DeQueue(a);     // 队头结点出队
        OutputNode(p);      // 将队头结点的左右孩子依次入队
        
        if (p->lchild != NULL)
        {
            EnQueue(a, p->lchild);
        }
        if (p->rchild != NULL)
        {
            EnQueue(a, p->rchild);
        }
    }
    return 0;
}