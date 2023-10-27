#数据结构 #C
# [45] 二叉树的先中后序遍历
遍历：按照某种次序把所有结点都访问一遍。
- 层次遍历：基于树的层次特性确定的次序规则。
- 前/ 中 / 后序遍历：基于树的递归特性确定的次序规则。

![](img/05_tree_part_1/19%20空树和非空树.jpg)

- **先序遍历**：根-->左-->右（N-L-R）；
- **中序遍历**：左-->根-->右（L-N-R）；
- **后序遍历**：左-->右-->根（L-R-N）。 

以如下的二叉树为例子，三种遍历的方式顺序为下：

![](img/05_tree_part_1/20%20三种遍历.jpg)

- 先序遍历： A -> B -> D -> E -> C -> F -> G
- 中序遍历： D -> B -> E -> A -> F -> C -> G
- 后序遍历： D -> E -> B -> F -> G -> C -> A

## 1. 前序遍历
前序遍历（PreOrder），又叫先序遍历，的操作过程如下：
1. 若二叉树为空，则什么也不做；
2. 若二叉树非空：
    - 1.**访问根结点**；
    - 2.先序遍历左子树；
    - 3.先序遍历右子树。

```c
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 先序遍历
void PreOrder(BiTree T) {
    if (T != NULL) {
        visit(T);               // 访问根结点
        PreOrder(T->lchild);    // 递归遍历左子树
        PreOrder(T->rchild);    // 递归遍历右子树
    }
}
```

![](img/05_tree_part_1/21%20前序遍历.jpg)

具体例子：
针对某一个二叉树的BiTree，将其所有的数据元素使用先序遍历，存储在数组Array中，并预设数组大小足够不会发生越界。
程序实现：
```c
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
```

## 2. 中序遍历
中序遍历（InOrder）的操作过程如下：
1. 若二叉树为空，则什么也不做；
2. 若二叉树非空：
    - 1.中序遍历左子树；
    - 2.**访问根结点**；
    - 3.中序遍历右子树。

```c
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 中序遍历
void InOrder(BiTree T) {
    if (T != NULL) {
        InOrder(T->lchild);     // 递归遍历左子树
        visit(T);               // 访问根结点
        InOrder(T->rchild);     // 递归遍历右子树
    }
}
```

![](img/05_tree_part_1/22%20中序遍历.jpg)

## 3. 后序遍历
后序遍历（PostOrder）的操作过程如下：
1. 若二叉树为空，则什么也不做；
2. 若二叉树非空：
    - 1.后序遍历左子树；
    - 2.后序遍历右子树。
    - 3.**访问根结点**；

```c
typedef struct BiTNode {
    int data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 中序遍历
void PostOrder(BiTree T) {
    if (T != NULL) {
        PostOrder(T->lchild);    // 递归遍历左子树
        PostOrder(T->rchild);    // 递归遍历右子树
        visit(T);                // 访问根结点
    }
}
```

![](img/05_tree_part_1/23%20后序遍历.jpg)

前、中、后序遍历皆属于「**深度优先遍历** （Depth-First Traversal）」，其体现着一种“先走到尽头，再回头继续”的回溯遍历方式。

## 4. 遍历算法的应用举例
求树的深度
```c
int GetTreeDepth(BiTree T){
    if(T == NULL){
        return 0;
    } else {
        int l = GetTreeDepth(T->lchild);
        int r = GetTreeDepth(T->rchild);
        // 树的深度是左子树深度和右子树的深度的最大值 + 1
        // 典型后序遍历
        return l > s ? (l + 1) : (s + 1);
    }
}
```

# [46] 二叉树的层序遍历
**算法**：
1. 初始化一个辅助队列
2. 根结点入队
3. 若队列非空，则队头结点出队，访问该结点，并将其左、右孩子插入队尾（如果有的话）
4. 重复第3步直至队列为空

![](img/05_tree_part_1/24%20层序遍历.jpg)

层序遍历本质上是「**广度优先搜索** (Breadth-First Traversal)」，其体现着一种“一圈一圈向外”的层进遍历方式。

```c
// 二叉树结点 链式存储
typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 辅助链式队列结点
typedef struct LinkNode {
    BiTNode *data;          // 存指针而非结点
    struct LinkNode *next;
} LinkNode;

typedef struct {
    LinkNode *front, *rear;    // 队头队尾
} LinkQueue;

// 层序遍历
void LevelOrder(BiTree T) {
    LinkQueue Q;
    InitQueue Q;                // 初始化辅助队列
    BiTree p;
    EnQueue(Q, T);              // 根结点入队
    while (!IsEmpty(Q)) {       // 队列不空则循环
        // 队列尾部结点依次出队
        p = GetRear(Q);
        DeQueue(Q, p);    
        visit(p);

        // 将尾部结点的子结点，依次插入队列中
        if (p->lchild != NULL) {
            EnQueue(Q, p->lchild);    // 左孩子入队
        }  
        if (p->rchild != NULL) {
            EnQueue(Q, p->rchild);    // 右孩子入队
        }  
    }
}
```

# [47] 由遍历序列构造二叉树
上述是已知二叉树，求遍历序列，本部分依据已有的二叉序列构造二叉树。

## 1. 不同二叉树的遍历序列
**中序遍历**：递归遍历左子树 ---> 根结点 ---> 递归遍历右子树。

> 对于一个中序遍历序列，可能对应多种二叉树形态

![](img/05_tree_part_1/25%20中序遍历构建二叉树.jpg)

**前序遍历**：根结点 ---> 递归遍历左子树 ---> 递归遍历右子树

> 对于一个前序遍历序列，可能对应多种二叉树形态

![](img/05_tree_part_1/26%20前序遍历构建二叉树.jpg)

**后序遍历**：递归遍历左子树 ---> 递归遍历右子树 ---> 根结点

> 一个后序遍历序列，可能对应多种二叉树形态。

![](img/05_tree_part_1/27%20后序遍历构建二叉树.jpg)

**层序遍历**：

> 一个层序遍历序列，可能对应多种二叉树形态。

![](img/05_tree_part_1/28%20层序遍历构建二叉树.jpg)

> **结论：若只给出一棵二叉树的 前/中/后/层序遍历序列中的一种，不能唯一确定一棵二叉树**。  
> 但是，给出中序 + X 两种，就可以根据遍历序列构造唯一的二叉树。

## 2. 前序 + 中序遍历序列
- **前序遍历**：根结点            →   前序遍历左子树   →   前序遍历右子树
- **中序遍历**：中序遍历左子树    →    根结点          →   中序遍历右子树

![](img/05_tree_part_1/29%20前序+中序%20框架.jpg)

【例子】给出前序遍历`ADBCE`，中序遍历`BDCAE`，求出二叉树的结构。
1. 根据对应关系，前序遍历的第一个结点即根结点，找到根结点；
2. 根结点在中序遍历的左右部分各为根结点的左右子树；
3. 根据前序遍历首个结点是根结点，找到左右子树的根结点；
4. 找到子树的左右孩子结点。
![](img/05_tree_part_1/30%20前序+中序%20还原%201.jpg)
![](img/05_tree_part_1/31%20前序+中序%20还原%202.jpg)
![](img/05_tree_part_1/32%20前序+中序%20还原%203.jpg)
![](img/05_tree_part_1/33%20前序+中序%20还原%204.jpg)

## 3. 后序 + 中序遍历序列
-   **后序遍历**：后序遍历左子树   →   后序遍历右子树   →  根结点
-   **中序遍历**：中序遍历左子树   →    根结点     →     中序遍历右子树

![](img/05_tree_part_1/34%20后序+中序%20框架.jpg)

【例子】给出后序遍历`EFAHCIGBD`，中序遍历`EAFDHCBGI`，求出二叉树的结构。
1. 根据对应关系，后序遍历的最后一个结点即根结点，找到根结点；
2. 根结点在中序遍历的左右部分各为根结点的左右子树；
3. 根据后序遍历最后一个结点是根结点，找到左右子树的根结点；
4. 找到子树的左右孩子结点，直到每个结点都确定有自己的位置为止。

![](img/05_tree_part_1/35%20后序+中序%20还原%201.jpg)
![](img/05_tree_part_1/36%20后序+中序%20还原%202.jpg)
![](img/05_tree_part_1/37%20后序+中序%20还原%203.jpg)
![](img/05_tree_part_1/38%20后序+中序%20还原%204.jpg)
![](img/05_tree_part_1/39%20后序+中序%20还原%205.jpg)

## 4. 层序 + 中序遍历序列
-   **层序遍历**：根结点     →     左子树的根     →     右子树的跟
-   **中序遍历**：中序遍历左子树    →    根结点     →     中序遍历右子树

![](img/05_tree_part_1/40%20层序+中序%20框架.jpg)

【例子】给出层序遍历`DABEFCGHI`，中序遍历`EAFDHCBGI`，求出二叉树的结构。
1. 根据对应关系，层序遍历的第一个结点即根结点，找到根结点；
2. 根结点在中序遍历的左右部分各为根结点的左右子树；
3. 根据层序遍历的顺序，确定左右子树的根结点；
4. 找到子树的左右孩子结点，直到每个结点都确定有自己的位置为止。

![](img/05_tree_part_1/41%20层序+中序%20还原%201.jpg)
![](img/05_tree_part_1/42%20层序+中序%20还原%202.jpg)
![](img/05_tree_part_1/43%20层序+中序%20还原%203.jpg)
![](img/05_tree_part_1/44%20层序+中序%20还原%204.jpg)
![](img/05_tree_part_1/45%20层序+中序%20还原%205.jpg)
![](img/05_tree_part_1/46%20层序+中序%20还原%206.jpg)

由二叉树遍历序列构造二叉树，通常有三种方式：
1. 前序 + 中序 遍历序列；
2. 后序 + 中序 遍历序列；
3. 层序 + 中序 遍历序列。

其中关键的做法是：**找到树的根结点，并根据中序序列划分左右子树，再找到左右子树根结点**。

![](img/05_tree_part_1/47%20两种遍历构造唯一二叉树.jpg)

问：能够对前序、后序、层序进行两两组合构建出二叉树。
可以以 前序`AB`，后序`BA`，层序`AB`, 构建出两种二叉树。

![](img/05_tree_part_1/48%20无法确定二叉树结构.jpg)

因此前序、后序、层序序列的两两组合无法唯一确定一个二叉树。
