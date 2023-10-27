#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree pre = NULL;          // 记录每一轮的当前指针
BiTree finalNode = NULL;    // 记录最后找的结果

// 这里使用全局变量的方法，也可以使用的是二阶指针，会比较难懂
bool CheckMatching(BiTree tmp, int target)
{
    // 必须首先检查pre是否为空，排除首次匹配直接读取空指针
    // 只有在第一次匹配完成后，才知道后继是谁
    if (pre == NULL || pre->data != target) 
    {
        pre = tmp;
        return false;
    }
    // 与上一个结点匹配，那么当前结点就是要找的后继
    else
    {
        finalNode = tmp;
    /* 这里，一定要补上，清空pre结点
       否则，pre保存了之前的数据，下一个结点在匹配的时候，判断是true，
       就会更新改写finalNode，导致寻找后继结点失效 */
        pre = NULL;    
        return true;
    }
}

/*  中序遍历 */
void InOrderTraversal(BiTree tmp, int target)
{
    if (tmp == NULL) {
        return;
    }

    InOrderTraversal(tmp->lchild, target);
    printf("Node data = [%d], target = [%d] \n", tmp->data, target);
    if (CheckMatching(tmp, target) == true) {
        printf("--- Matching!!! ---\n", target);
        return;
    }
    InOrderTraversal(tmp->rchild, target);
    return;
}

// 返回后继是否存在和后继的值
bool GetSuccessor(BiTree root, int *successor)
{
    if (root == NULL || successor == NULL) {
        return false;
    }

    int target = *successor;            // 结点数据target

    InOrderTraversal(root, target);
    if (finalNode == NULL) {            // 后继并不存在
        return false;
    }

    *successor = finalNode->data;
    return true;
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
    tree = (BiTNode *)malloc(sizeof(BiTNode));
    tree->data = 1;

    // 2、3
    BiTree tree_2 = (BiTNode *)malloc(sizeof(BiTNode));
    tree_2->data = 2;
    BiTree tree_3 = (BiTNode *)malloc(sizeof(BiTNode));
    tree_3->data = 3;
    tree->lchild = tree_2, tree->rchild = tree_3;
    tree_3->rchild = NULL;

    // 4、5
    BiTree tree_4 = (BiTNode *)malloc(sizeof(BiTNode));
    tree_4->data = 4;
    BiTree tree_5 = (BiTNode *)malloc(sizeof(BiTNode));
    tree_5->data = 5;
    tree_2->lchild = tree_4, tree_2->rchild = tree_5;

    tree_4->rchild = NULL;
    tree_5->lchild = NULL, tree_5->rchild = NULL;

    // 6
    BiTree tree_6 = (BiTNode *)malloc(sizeof(BiTNode));
    tree_6->data = 6;
    tree_3->lchild = tree_6;

    tree_6->lchild = NULL, tree_6->rchild = NULL;

    // 7
    BiTree tree_7 = (BiTNode *)malloc(sizeof(BiTNode));
    tree_7->data = 7;

    tree_4->lchild = tree_7;
    tree_7->lchild = NULL, tree_7->rchild = NULL;

    return tree;
}

int main()
{
    // 中序遍历: 7 4 2 5 1 6 3
    BiTree tree = CreateBiTree();
    int successor, data = 5;
    int array[] = { 7,4,2,5,1,6,3 }; 
    
    for (int i = 0; i < 7; i++) {
        successor = data = array[i];

        if (GetSuccessor(tree, &successor) == true) {
            printf("The Successor of data [%d] is [%d]\n\n", data, successor);
        } else {
            printf("The Successor of data [%d] does not exist\n\n", data);
        }
        pre = NULL, finalNode = NULL;       // 清除每次的数据
    }

    return 0;
}