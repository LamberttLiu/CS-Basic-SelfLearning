#数据结构 

# [28] 队列的基本概念
队列（Queue）是**只允许在一端进行插入，在另一端删除**的线性表。  
重要术语：队头、队尾。

![](img/03_stack_queue/16%20队列.jpg)

**队尾**：允许插入的一端  
**队头**：允许 删除的一端  
队列的特点：**先进先出** First In First Out（**FIFO**）

队列的常用操作
```cpp
// 初始化队列，构造一个空队列Q。
InitQueue(&Q) 
// 销毁队列。销毁并释放队列Q所占用的内存空间。
DestroyQueue(&Q) 


// 入队，若队列Q未满，将x加入，使之成为新的队尾。
EnQueue(&Q, x) 
// 出队，若队列Q非空，删除队头元素，并用x返回。 
DeQueue(&Q, &x)

// 读队头元素，若队列Q非空，则将队头元素赋值给x。
GetHead(Q, &x)

// 其他常用操作 
// 判队列空，若队列Q为空返回true，否则返回false。
IsEmptySqQueue(Q)

// 判队列满，若队列Q为空返回true，否则返回false。
IsFullSqQueue(Q)
```

# [29] 列队的顺序存储结构
使用顺序表形式实现队列

![](img/03_stack_queue/17%20顺序存储队列.jpg)

## 1. 队列声明
```c
/******* 队列声明 ******/
#define MaxSize 10          // 定义队列中元素最大个数
typedef struct {
    Elemtype data[MaxSize]; // 静态数组存放队列元素
    int front, rear;         // 队头指针和队尾指针
} SqQueue;

void testQueue()
{
    SqQueue Q;              // 声明队列(顺序存储)
    /* 后续操作 */
}
```

**注意**：在该声明的队列中，  
- `front`指的是第一个队头的位序`-1`，
- `rear`指的是队尾元素的**位序**，
- `rear-front`即代表队列中元素个数。

![](img/03_stack_queue/18%20顺序队列初始化和判空.jpg)

## 2. 队列初始化
初始化保证头和尾均指向0的位置。
```cpp
/* ......(队列声明）....  */
void InitQueue(SqQueue &Q)
{
    // 初始化时 队头、队尾指针指向0
    Q.rear = 0, Q.front = 0;
}

void testQueue()
{
    SqQueue Q;              // 声明队列(顺序存储)
    InitQueue(Q);
    /* 后续操作 */
}
```

## 3. 队列判空
队尾指针和队头指针指向同一个地方，表示当前队列是个空队列。
```cpp
bool IsEmptySqQueueQueue(SqQueue Q)
{
    if (Q.rear == Q.front) { // 队空的条件
        return true;
    } else {
        return false;
    }
}
```

## 4. 入队操作
方法：
1. 首先对队列是否已经满进行判断校验；
2. 将队尾元素添加到队列中（数组存储队列，队尾的下标，即队尾元素的位序，用表示新的元素的索引）；
3. 队尾指针自增后移。

![](img/03_stack_queue/19%20入队.jpg)
```cpp
/* ......(队列声明）....  */
// 入队
bool EnQueue(SqQueue &Q, ElemType x)
{
    if (bool(IsFullSqQueue)) {   //判定队列是否已满
        return false;
    }
    Q.data[Q.rear] == x;        // 将x插入队尾
    Q.rear++;                   // 队尾指针后移
}
```

### 思考：  
对于条件判断中的`bool(IsFullSqQueue)`, 如何对队列已满进行判断？是否是`Q.rear == MaxSize`?   是否一定要满足`Q.rear > Q.front`?
### 回答：  
不是。  
队列出队，队头`front`也会发生自增加。留下空余的存储空间，队列入队的时候可以再次覆盖未使用内存。在这种情况下，队列的队尾值`Q.rear`可能小于 `Q.front`对头的值。

### 解决方式：  
可以用模运算将无限的整数域映射到有限的整数集合 $\{0, 1, 2, …, MaxSize-1\}$ 上，在空余的位置继续存储元素。

> 由于队列的状态具有循环特点，模运算将存储空间在逻辑上变成了“环状”。

![](img/03_stack_queue/20%20循环队列.jpg)

在这个前提下，需要对原有代码中的队尾指针移动改写取余操作（mod）:
```cpp
/* ......(队列声明）....  */

// 入队
bool EnQueue(SqQueue &Q, ElemType x)
{
    if (bool(IsFullSqQueue)){  // 判定队列是否已满
        return false;
    }
    Q.data[Q.rear] == x;       // 将x插入队尾
    // 队尾指针后移1位，取模
    Q.rear = (Q.rear + 1) % MaxSize;              
}
```

上图中，`Q.rear = 0`,`Q.front = 6`。元素个数 : `(0 - 6)mod 10 = 4`。
引入取余运算，使得线状的队列结构，逻辑上变成了环状的**循环队列**。
在此种情况下，对队列已满的条件，定义成 —— 队尾指针的再下一个位置是队头，即：

![](img/03_stack_queue/21%20满队列.jpg)

```c
//判定队列已满
bool IsFullSqQueue(SqQueue Q)
{
    // 在这一程序中，在队列已满的情况下有一个单元未存储数据
    return (Q.rear + 1) % MaxSize == Q.front;
}
```

## 5. 出队操作
方法：
1. 首先对队列是否已经为空进行判断校验（**入队验满，出队验空**）；
2. 直接取原队头的元素中（数组存储队列，队头的下标，即队头元素的位序 - 1，用表示之前的元素的索引）；
3. 队头指针前移，由于循环队列需要进行取余（mod）操作。

![](img/03_stack_queue/22%20出队.jpg)

```cpp
// 出队（删除一个队头元素，并用x返回）
bool DeQueue(SqQueue &Q,ElemType &x)
{
    // 对队列判空操作
    if (Q.rear == Q.front) {
        return false;
    }
    x = Q.data[Q.front];
    // 队头往前移1，空出来
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}
```

## 6. 获得队头的值——查找
直接获取队头元素，对队头和队尾指针均不做操作。
```cpp
bool GetHead(SqQueue Q, ElemType &x)
{
    // 队列判空
    if (Q.rear == Q.front){
        return false;
    }
    x = Q.data[Q.front];
    return true;
}
```

## 7. 对于判断队列已满和已空校验方法
由于队列初始化的时候，指定为队头和队尾指向一个地方，即为空队列，那么为了保证不会出现二义性定义，对于队列已经满的场景必须做出具体的定义，且不能和空队列的定义重合。

### 方法一：使用一个闲置位，利用队头和队尾的查值区分
```cpp
// 判定队列已满条件：
bool IsFullSqQueue(SqQueue Q) 
{
    // 队尾指针的下一个位置是队头
    return (Q.rear + 1) % MaxSize == Q.front;
}

// 此队满时元素的个数：
Q.num = (Q.rear - Q.front + MaxSize) % MaxSize;

bool IsEmptySqQueue(SqQueue Q) 
{
    return Q.front == Q.rear;
}
```
缺点：至少有一个空间无法存放数据，因为如果存满元素，那将跟判空队列混淆。

### 方法二：在队列中定义一个变量`size`
需要在队列声明的时候 添加 `size`变量，在入队时、出队时，对`size`操作, 如果`size`值达到`MaxSize`表示已满。
```cpp
/******* 队列声明 ******/
#define MaxSize 10          // 定义队列中元素最大个数
typedef struct {
    Elemtype data[MaxSize]; // 静态数组存放队列元素
    int front, rear;        // 队头指针和队尾指针
    int size;               // 队列的当前长度
} SqQueue;

bool EnQueue(SqQueue &Q, ElemType x)
{
    /* ... 原本入队操作... */
    Q.size++;
}

bool DeQueue(SqQueue &Q, ElemType &x)
{
    /* ... 原本出队操作... */
    Q.size--;
}

bool IsFullSqQueue(SqQueue Q) 
{
    return Q.size == MaxSize;
}

bool IsEmptySqQueue(SqQueue Q) 
{
    return Q.size == 0;
}
```

### 方法三：需要在队列声明的时候 添加`tag`变量
在插入操作成功时，`tag = 1`; 在删除操作成功时，`tag = 0`。  
由于只有删除操作才能导致队空；只有删除才能导致队满，所以：  
- 判断队满的条件 `front == rear && tag == 1`;
- 判断队空的条件 `front == rear && tag == 0`;

```cpp
/******* 队列声明 ******/
#define MaxSize 10          // 定义队列中元素最大个数
typedef struct{
    Elemtype data[MaxSize]; // 静态数组存放队列元素
    int front, rear;        // 队头指针和队尾指针
    int tag;                // 当前进行的操作是删除 或 插入
} SqQueue;

bool EnQueue(SqQueue &Q, ElemType x)
{
    /* ... 原本入队操作... */
    Q.tag == 1;     // 上一步完成插入操作
}

bool DeQueue(SqQueue &Q, ElemType &x)
{
    /* ... 原本出队操作... */
    Q.tag == 0;     // 上一步完成删除操作
}

// 刚刚完成插入操作
bool IsFullSqQueue(SqQueue Q) 
{
    return Q.front == Q.rear && Q.tag == 1;
}

// 刚刚完成删除操作
bool IsEmptySqQueue(SqQueue Q) 
{
    return Q.front == Q.rear && Q.tag == 0;
}
```

# [30] 队列的链式存储结构
队列是一种特殊的线性表，与单链表一样，可以进行链式实现.
## 1. 链式队列声明
```c
/* 链式队列结点 */
typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode;

/* 链式队列 */
typedef struct LinkQueue {
    /* 队列队头和队尾指针 */
    LinkNode *front, *rear; 
} LinkQueue;
```
队列的链式实现需要声明两个指针，一个指向头，一个指向尾。这样在头尾进行操作的时候，可以直接对现有的指针所指对象进行操作，时间复杂度是 $O(1)$。  
如果仅有一个指针的话，在对队尾进行操作时，需要遍历链表，时间复杂度 $O(N)$。
![](img/03_stack_queue/23%20链式队列.jpg)
## 2. 链式队列的初始化
由于链表分为带头结点和不带头结点两种类型，因此，按照链表类型的不同，队列的数据结构也可以分为两种。 

![](img/03_stack_queue/24%20链式队列初始化.jpg)
- **带头结点**的链表形式
```c
typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode;

// 链式队列是一个结构体，内部包含着两个结构体的指针
typedef struct LinkQueue {
    LinkNode *front, *rear; 
} LinkQueue;

void InitQueue(LinkQueue &Q)
{
    // 初始时，front,rear都指向头结点 -- 空结点
    Q.front = Q.rear = (LinkNode*)malloc(sizeof(linkNode));
    Q.front->next = NULL;
}

void testLinkQueue()
{
    LinkQueue Q;
    InitQueue (Q);
    /* 后续代码 */
}
```

- **不带头结点**的链表形式
```c
void InitQueue(LinkQueue &Q)
{
    // 初始时，front,rear 都为 NULL    
    Q.front = Q.next = NULL;
}
```

## 3. 链式队列的判空
- **带头结点**的链表形式
```c
bool IsEmptySqQueue(LinkQueue Q)
{
    if (Q.front == Q.rear) {
        return true;
    } else {
        return false;
    }
}
```

- **不带头结点**的链表形式
```c
bool IsEmptySqQueue(LinkQueue Q)
{
    if (Q.front == NULL) {
        return true;
    } else {
        return false;
    }
}
```

## 4. 入队操作
- **带头结点**的链表形式
![](img/03_stack_queue/25%20入队链式队列.jpg)
```c
void Enqueue(LinkQueue &Q, ElemType x)
{
    /* 由于队列的入列在链表末尾添加，不需要判定入参值 */
    LinkNode *s = (LinkNode *)malloc(sizeof(linkNode));
    /* 操作：赋值，建链，断链，移动指针 */
    s->data = x;
    s->next = NULL;         // 队尾的next指针要赋空
    Q.rear->next = s;       // 新结点插到原rear后面
    Q.rear = s;             // rear前进1位，变成真正的rear
}
```

- **不带头结点**的链表形式
注意第一个元素入队，需要做例外情况判断。
```c
void Enqueue(LinkQueue &Q, ElemType x){
    LinkNode *s = (LinkNode*)malloc(sizeof(linkNode));
    s->data = x;
    s->next = NULL;
    if (Q.front == NULL){
        Q.front = s;        // 在空队列中插入第一个元素
        Q.rear = s;         // 修改队头队尾指针
    } else {
        Q.rear->next = s;   // 新结点插到原rear后面
        Q.rear = s;         // rear前进1位，变成真正的rear
    }
}
```

## 5. 出队操作
- **带头结点**的链表形式
注意最后一个元素出队的特殊场景。

![](img/03_stack_queue/26%20出队链式队列.jpg)
```c
bool DeQueue(LinkQueue &Q, Elemtype &x){
    if (Q.rear = Q.front){
        return false;           // 空队列直接判否
    }
    LinkNode *p = Q.front->next;
    x = p->data;                // 用变量x返回队头元素
    Q.front->next = p->next;    // 修改头结点的next指针
    if (Q.rear == p) {          // 此次最后一个结点出队
        Q.rear = Q.front;       // 修改 rear 指针
    }
    free(p);
    return true;
}
```

- **不带头结点**的链表形式
```c
bool DeQueue(LinkQueue &Q, Elemtype &x){
    if (Q.rear = Q.front){
        return false;           // 空队列直接判否
    }
    LinkNode *p = Q.front;      // p指向此次出队的结点
    x = p->data;                // 用变量x返回队头元素
    Q.front->next = p->next;    // 修改头结点的next指针
    if(Q.rear == p){            // 此次最后一个结点出队
        Q.front = NULL;         // front变空
        Q.rear = NULL;          // rear变空
    }
    free(p);
    return true;
}
```

灵魂发问：对于链式队列，什么时候会变满？
- 顺序存储——预分配的空间耗尽时队满
- 链式存储——一般不会队满，除非内存不足

# [31] 双端队列
在栈和队列的基础上，衍生出另一种数据类型——双端队列。
- 栈：只能从一端插入和删除的线性表；  
- 队列：只允许从一端插入、另一端删除的线性表；  
- 双端队列，只允许从两端插入、两端删除的线性表。

![](img/03_stack_queue/27%20双端队列.jpg)

双端队列可以进行进一步的拓展扩充：
1. **输入受限**的双端队列：只允许从一端插入、两端删除的线性表；
2. **输出受限**的双端队列：只允许从两端插入、一端删除的线性表。

双端队列的一端如果被封闭的话，那么双端队列是栈的一种高级方式，所有栈的特点，双端队列都可以实现。

# [32] 队列的应用

队列会用于树的层次遍历、树的广度优先遍历。

队列在操作系统的应用：
- 在多进程并发使用有限系统资源时，FCFS（Fist Come First Service）是使用一种常有策略。
- 数据缓冲区。 
- 消息队列。  

应用场景：去学校打印店打印论文，多个同学用同一台打印机打印，打印的先后顺序安排（用“队列”组织打印数据），可缓解主机与打印机速度不匹配的问题。

# [33] 特殊矩阵的压缩存储
（待补充）
