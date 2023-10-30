#数据结构 #C 

# [16] 双链表
为什么引入双链表？  
单链表的结点中只有一个指向其后继的指针，使得单链表要访问某个结点的前驱结点时，只能从头开始遍历，访问后驱结点的复杂度为`O(1)`，访问前驱结点的复杂度为`O(N)`。为了克服上述缺点，引入了双链表。

![](img/02_linear_list/22%20单链表与双链表.JPG)

**对于单链表**：
一个结点，有储存数据的data，和next后驱结点(指针)。也就是这个单链表想要一些遍历的操作都得通过前结点索引到后结点。

**对于双链表**：
对于一个结点，有些和单链表一样有存储数据的data，指向后方的next（指针）。它拥有单链表的所有操作和内容。但是他还有一个前驱结点prior(指针)。

```cpp
// 声明
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinklist;
```

![](img/02_linear_list/23%20双链表结点.jpg)

## 1.初始化
双链表的初始化，一般默认带头结点：

![](img/02_linear_list/24%20双链表初始化%20带头结点的双链表.JPG)

```cpp
// 初始化双链表
bool InitDLinklist(Dlinklist &L)
{
    L = (DNode*)malloc(sizeof(DNode));
    if (L == NULL) {
        return false;
    }

    // 头结点的 prior 永远指向 NULL
    L->prior = NULL;
    L->next = NULL;
    return true;
}

void testDLinkList()
{
    DLinkList L;
    InitDLinkList(L);
    /* ...后续代码... */
}
```

如何对一个双链表判空？  
方法：由于头结点的 prior 永远指向 NULL，判断头结点的next结点是否是空就可以判断双链表为空。
```cpp
bool IsEmpty(DLinkList L)
{
    if (L->next == NULL) {
        return true;
    } else {
        return false;
    }
}
```

## 2.插入
先抽象出一个基本操作，对指定结点的后进行后插结点操作。  
当然，对这个场景需要考虑其后是否有后继结点，如果没有后继结点，那对应会省略一步。
![](img/02_linear_list/25%20双链表插入%201.JPG)

```cpp
// 在p结点后插入s结点，s已经分配好
bool InsertNextDNode(DNode *p, DNode *s)
{
    // 非法参数
    if (p == NULL || s == NULL){
        return false;
    }
    // 注意以下四个步骤的顺序
    s->next = p->next;
    // 判断如果p结点后有后继结点
    if (p->next != NULL) {
        p->next->prior = s;
    }
    s->prior = p;
    p->next = s;
    return true;
}
```

![](img/02_linear_list/26%20双链表插入%202.JPG)

封装函数：`InsertNextDNode(DNode *p, DNode *s)`，对双链表的插入场景分为：按位序插入和指定结点前插操作、指定结点后插，都是可以直接调用该基础操作。

1. 按位序插入，以头结点开始，找到一个位置i的前驱结点，对前驱结点进行后插操作；
```cpp
// 按位序插入, 在双链表L的sequence位置插入结点s
bool InsertBySequence(DLinkList L, int sequence, DNode *s)
{
    if (L == NULL || sequence < 1){
        return false;
    }
    DNode *p = L;
    int j = 0;

    while (p != NULL && j < i - 1) {      
        p = p->next;
        j++;
    }
    if (p == NULL) {            
        return false;
    }
    
    // 直接调用封装函数
    return InsertNextDNode(p, s);
}
```

2. 指定结点前插操作，对这个结点的前一位，进行后插操作。
```cpp
// 判断p结点是都是头结点
bool IsHeadNode(DNode *p)
{
    // 只有头结点的前驱指向空
    return p->prior == NULL;
}

// 在结点p前面插入结点s
bool InsertFrontDNode(DNode *p, DNode *s)
{
    // 如果p是头结点，那无法对p进行前插
    if (p == NULL || s == NULL || IsHeadNode(p)) {
        return false;
    }

    DNode *pre = p->prior;
    return InsertNextDNode(pre, s);
}
```

3. 指定结点后插操作，直接等价于基本操作。
可以说，基于**对指定结点的后插**这一基本操作的封装，可以完成对双链表的所有场景的插入操作。

## 3.删除
同样的，对于双链表的删除，也可以抽象出一个基础操作，即**删除指定结点的后继结点**（注意，这里不是删除这个指定结点）。

![](img/02_linear_list/27%20双链表删除.JPG)
```c
// 删除p的后继结点q
bool DeleteNextDNode(DNode *p)
{
    // 判空校验
    if (p == NULL) {
        return false;
    }

    // 找到p的后继结点q，如果判空表示没有后继结点，删除失败
    DNode *q = p->next;
    if (q == NULL) {
        return false;
    }

    p->next = q->next;
    // 判断q结点是否最后一个结点
    if (q->next != NULL){
        q->next->prior = p;
    }
    free(p);
    return true;
}
```
同理，删除分为：
1. 按照位序删除结点；
```cpp
// 按位序删除, 删除双链表L的sequence位置结点
bool InsertBySequence(DLinkList L, int sequence)
{
    if (L == NULL || sequence < 1){
        return false;
    }
    DNode *p = L;
    int j = 0;

    while (p != NULL && j < i - 1) {      
        p = p->next;
        j++;
    }
    // p 指向了第 i-1 个结点了，它的后继结点必须存在，否则位序为i的结点不存在
    if (p == NULL || p->next == NULL) {            
        return false;
    }
    
    // 直接调用封装函数，删除第 i-1 位序的结点的后继结点
    return  DeleteNextDNode(p);
}
```

2. 删除指定结点； 
```cpp
bool DeleteDNode(DNode *p)
{
    // 头结点不用删除
    if (p == NULL || IsHeadNode(p)) {
        return false;
    }

    // 删除的这一个结点，恰好是其上一个结点的后驱结点
    return DeleteNextDNode(p->prior);
}
```
两类场景，都在对基础操作`bool DeleteNextDNode(DNode *p)`完成调用。

那么，如何销毁双链表？ 使用循环遍历，对头结点后的每个结点进行删除。  
这里优先使用`while`循环，因为不指定次数。
```c
void DestroyList(DLinkList &L)
{
    // 循环释放各个数据结点
    while(L->next != NULL)
    {
        DeleteNextNode(L);
    }
    free(L);        // 释放头指针
    L = NULL;       // 头指针指向NULL
}
```
## 4.遍历
对比单链表只有单向遍历的操作，双链表指针存在有前向遍历和后向遍历两种遍历方式。
```c
// 后向遍历
while (p != NULL)
{
    p = p->next;
    /*对结点进行处理，例如打印，取值等*/
}
```

```c
// 前向遍历
while (p != NULL)
{
    p = p->prior;
    /*对结点进行处理，例如打印，取值等*/
}
```

如果不针对头结点
```c
// 前向遍历,跳过头结点
while (!IsHeadNode(p))
{
    p = p->prior;
    /*对结点进行处理，例如打印，取值等*/
}
```
双链表不可随机存取，按位查找、按值查找操作都只能用遍历的方式实现，时间复杂度`O(N)`。

# [17] 循环链表
在单链表和双链表的基础上，产生一种新的链式存储表。相比普通的单链表的尾结点next为空，双链表头结点prior和尾结点next为空。  
循环链表的链呈现首位相连的状态，当然，按照基本结点的数据结构，分循环单链表和循环双链表：

![](img/02_linear_list/28%20循环单链表.JPG)

## 1.循环单链表
单链表（一般）：表尾结点的`next`指针指向 `NULL`  
循环单链表：表尾结点的`next`指针指向头结点
```c
// 声明
typedef struct LNode {          // 定义单链表结点类型
    ElemType data;              // 每个结点存放一个数据元素
    struct LNode *next;         // 指针指向下一个结点
} LNode, *LinkList;

// 初始化一个循环单链表
bool InitList(LinkList &L) 
{
    // 分配头结点
    L = (LNode*) malloc(sizeof(LNode));
    // 判断是否分配成功
    if (NULL == L){
        return false;
    }

    // 头结点next指向头结点自身
    L->next = L;
    return true;
}
```

![](img/02_linear_list/29%20循环单链表%20空表.jpg)

如何对一个循环单链表判空？头结点的`next`指针指向自己，那即为空。
```c
// 双链表判空
bool Empty(DLinkList L)
{
    if (L->next == L) {
        return true;
    } else {
        return false;
    }
}
```

如何判断结点是否为循环单链表的表尾？只需要判断它的`next`指针是否指向链表头。
```c
bool IsTail(LinkList L, LNode *p)
{
    if (p->next == L) {
        return true;
    } else {
        return false;
    }
}
```
总结特点：
- 单链表：从一个结点出发，只能找到后续的各个结点
- 循环单链表：从一个结点出发，可以找到其他任何一个结点

## 2.循环双链表
双链表（一般）：表头结点的 prior 指向 NULL；表尾结点的 next 指向 NULL。  
循环双链表：表头结点的 prior 指向表尾结点；表尾结点的 next 指向头结点。

![](img/02_linear_list/30%20循环双链表.JPG)
```c
// 声明
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinklist;

// 初始化空的双链表
bool InitDLinklist(Dlinklist &L)
{
    L = (DNode*)malloc(sizeof(DNode));
    if (L == NULL) {
        return false;
    }
    
    L->prior = L;       // 头结点的 prior 指向头结点
    L->next = L;        // 头结点的 next 指向头结点
    return true;
}

void testDLinkList()
{
    DLinkList L;
    InitDLinkList (L);
    /* 后续代码 */
}
```

如何对一个循环双链表判空？与循环单链表一样，头结点的`next`指针指向自己，那即为空。
![](img/02_linear_list/31%20循环双链表%20空表.jpg)
```c
// 双链表判空
bool Empty(DLinkList L)
{
    if (L->next == L) {
        return true;
    } else {
        return false;
    }
}
```

如何判断结点是否为循环双链表的表尾，只需要判断它的`next`指针是否指向链表头。
```c
// 双链表判尾结点
bool IsTail(DLinkList L, DNode *p)
{
    if (p->next == L) {
        return true;
    } else {
        return false;
    }
}
```

## 3.双链表的操作
### 插入
```c
// 双链表的插入，在p结点后插入s结点
bool InsertNextDNode(DNode *p, DNode *s)
{
    s->next = p->next;   // 把结点s 插到结点p 后面
    p->next->prior = s;  // 这句对比双链表，不需要条件判定了
    s->prior = p;
    p->next = s;
    return true;
}
```

### 删除
```cpp
// 双链表的删除，删除p结点后继q结点
bool DeleteNode(DNode *p) {
    DNode *q = p->next;
    p->next = q->next;
    
    // 不需要判空校验
    q->next->prior = p;
    free(q);
}
```

# [18] 静态链表
## 1.静态链表与单链表的区别

![](img/02_linear_list/32%20静态链表与单链表.JPG)

- 单链表：各个结点在内存中星罗棋布、散落天涯。
- 静态链表：分配一整片连续的内存空间，各个结点集中安置。  
  每个结点包含**数据元素**和**下一个结点的数组下标**(游标)，
  以int数据存储为例，每个数据元素 4B，每个游标 4B（每个结点共 8B）。  
  设起始地址为 addr，下一个的存放地址为 `addr + 8*2`

## 2.代码实现
```c
// 声明
#define MaxSize 10          // 静态链表最大长度
typedef struct {            // 静态链表结构类型定义
    ElemType data;          // 存储数据元素
    int next;               // 下一个元素的数组下标
} SLinkList[MaxSize];       // 静态链表

// 初始化
void testSlinkList()
{
    // a是一个静态链表,本质是一个结构体数组,sizeof(a) = 80;
    SLinkList a;            
    /* ...后续代码... */
}
```

- 静态链表实际上使用数组方式实现的链表。
优点： 增删 操作不需要大量移动元素
缺点： 不能随机存取，只能从头结点开始依次往后查找，容量固定不可变

- 适用场景：
1. 不知处指针的低级语言；
2. 数据元素数量固定不变的场景（如操作系统 文件分配表FAT）

由于这类数据结构使用场景较少，因此不做过多说明。

# [19] 顺序表和链表的特点总结比较
## 1.逻辑结构
都属于线性表，都是线性结构。

## 2.存储结构
![](img/02_linear_list/09%20顺序表%20Vs%20链表.jpg)
1. 顺序表  
   优点：支持随机存取、存储密度高  
   缺点：大片连续空间分配不方便，改变容量不方便

2. 线性表  
   优点：离散的小空间分配方便，改变容量方便
   缺点：不可随机存取，存储密度低

## 3.基本操作 -- 创、销、增、删、改、查
### 1. 创（Initialization）
- **顺序表**：需要预分配大片连续空间。若分配空间过小，则之后不方便拓展容量；若分配空间过大，则浪费内存资源  
    **静态分配**：静态数组；容量不可改变；
    **动态分配**：动态数组（`malloc()`、`free()`）；容量可改变，但需要移动大量元素，时间代价高。
- **链表**：只需分配一个头结点（也可以不要头结点，只声明一个头指针），之后方便拓展

### 2. 销（Destroy）
- **顺序表**：修改 Length = 0  
    **静态分配**：静态数组 系统自动回收空间
    **动态分配**：动态数组（malloc、free），需要手动 free
- **链表**：依次删除各个结点（free）

### 3. 增删（Insert & Deletation）
- **顺序表**：插入/删除元素要将后续元素都后移/前移，时间复杂度 `O(N)`，时间开销主要来自移动元素，若数据元素很大，则移动的时间代价很高
- **链表**：插入/删除元素只需修改指针即可，时间复杂度 `O(N)`，时间开销主要来自查找目标元素，查找元素的时间代价更低

### 4. 查（Query）
- **顺序表**：按位查找：`O(1)`，按值查找：`O(N)`
    若表内元素有序，可利用折半查找，在 $O(log_{2}{n})$ 时间内找到
- **链表**：按位查找：`O(N)`，按值查找：`O(N)`

改的实质上是查找，当查到到元素的时候，就会直接进行修改。

|                | 顺序表 | 链表 |
| -------------- |:------:|:----:|
| 弹性（可扩容） |   ×    |  ★   |
| 增删           |   ×    |  ★   |
| 查找           |   ★    |  ×   |  



**总结**：  
>表长难以预估、经常要增加/删除元素 ——> 链表  
>表长可预估、查询（搜索）操作较多，相对应较稳定 ——> 顺序表
