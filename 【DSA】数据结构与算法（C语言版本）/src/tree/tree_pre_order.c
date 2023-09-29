#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MAX_SIZE 100
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// pos作为指针传参，是需要将其值带出来
void PushBack(int* array, int* pos, int data)
{
    if (*pos >= ARRAY_MAX_SIZE) {
        return;
    }
    array[*pos] = data;
    (*pos)++;
}

// 测试输出Array
void OutPutArray(int* array, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("array[%d] = %d\n", i, array[i]);
    }
    return;
}

void PreOrderTraverse(BiTree binaryTree, int* array, int* pos)
{
    if (binaryTree == NULL) {
        return;
    }

    PushBack(array, pos, binaryTree->data);
    PreOrderTraverse(binaryTree->lchild, array, pos);
    PreOrderTraverse(binaryTree->rchild, array, pos);

    return;
}

void BiTreeInsertToArray(BiTree binaryTree, int* array)
{
    int pos = 0;
    PreOrderTraverse(binaryTree, array, &pos);
    OutPutArray(array, pos);

    return;
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

int main()
{
    BiTree tree = CreateBiTree();
    int array[ARRAY_MAX_SIZE];

    // 预期输出： 1 2 4 7 5 3 6  ---> 前序遍历
    BiTreeInsertToArray(tree, array);
    
    return 0;
}