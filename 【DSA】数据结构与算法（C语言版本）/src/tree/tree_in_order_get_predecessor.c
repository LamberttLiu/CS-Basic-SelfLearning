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
    if (tmp->data == target) 
    {
        finalNode = pre;
        return true;
    }
    else 
    {
        pre = tmp;
        return false;
    }
}

/*  中序遍历：
    每个轮次的操作，都需要将当前结点的数据域与target作对比，检查是否匹配。
    而pre，记录是这次匹配结点的上一个结点 -- 即前驱。
    而上一个结点的匹配是在上一轮进行的，即调用本次函数的位置确定的，
    那么， 就需要将每一次匹配的结点，传到函数里面进行修改，
    因为本轮进行匹配的结点，就是下一轮的pre结点，
    在下一轮匹配完成后，又会再次使用下一个结点，更新pre结点。
    由于每次更新都会使得pre变化，因此，需要第三个变量 final来保存下最终的要求结点
*/
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

// 返回前驱是否存在和前驱的值
bool GetPredecessor(BiTree root, int *predecessor)
{
    if (root == NULL || predecessor == NULL) {
        return false;
    }

    int target = *predecessor;          // 结点数据target

    InOrderTraversal(root, target);
    if (finalNode == NULL) {            // 前驱并不存在
        return false;
    }

    *predecessor = finalNode->data;
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
    int predecessor, data = 5;
    int array[] = { 7,4,2,5,1,6,3 }; 
    
    for (int i = 0; i < 7; i++) {
        predecessor = data = array[i];

        if (GetPredecessor(tree, &predecessor) == true) {
            printf("The Predecessor of data [%d] is [%d]\n\n", data, predecessor);
        } else {
            printf("The Predecessor of data [%d] does not exist\n\n", data);
        }
        pre = NULL, finalNode = NULL;   // 清除每次的数据
    }

    return 0;
}