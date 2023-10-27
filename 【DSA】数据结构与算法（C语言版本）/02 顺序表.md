#数据结构 #C 

# [7] 线性表的定义和基本操作
## 1. 基本定义
线性表是具有相同数据类型的 `n(n≥0)` 个**数据元素**的**有限序列**，其中`n`为**表长**。  
当 `n = 0` 时，线性表是一个**空表**。

![](img/02_linear_list/01%20线性表.jpg)

若用`L`命名线性表，则其一般表示为:
> $L = (a_1, a_2, …, a_i, a_{i+1},…,a_n)$.

## 2. 线性表的特点
1. 线性表内的数据元素的数据类型是相同的，因此每个数据元素所占的空间一样大
2. 线性表内的数据元素有序列之分
3. 线性表内的数据元素有限

## 3. 线性表几个概念
- 位序：指线性表中的数据元素顺序。  
- 表头元素： $a_1$ ，表尾元素： $a_n$ .  
- 除第一个元素外，每个元素有且仅有一个直接**前驱**；
- 除最后一个元素外，每个元素有且仅有一个直接**后继**。

> 注意，位序是从1开始，与数组的下标不同。
 
## 4. 线性表的基本操作
```c
// 初始化表。构造一个空的线性表L, 分配内存空间。
InitList(&L);

// 销毁操作。销毁线性表，并释放线性表 L 所占用的内存空间。
DestroyList(&L);

// 此两项操作实现了线性表从无到有到从有到无的操作。

// 插入操作。在表L中的第i个位置上插入指定元素e。
ListInsert(&L, i, e);
// 删除操作。删除表L中第i个位置的元素，并用e返回删除元素的值。
ListDelete(&L, i, &e);


// 按值查找操作。在表L中查找具有给定关键字值的元素。
LocateElem(L, e);
// 按位查找操作。获取表L中第i个位置的元素的值。
GetElem(L, i);

// 其他常用操作：
// 求表长。返回线性表L的长度，即L中数据元素的个数。
Length(L);
// 输出操作。按前后顺序输出线性表L的所有元素值。
PrintList(L);
// 判空操作。若L为空表，则返回true，否则返回false。
Empty(L);
```

**Tips：**
1. 对数据的操作 —— 创、销、增、删、改、查
2.  C语言函数的定义 —— <返回值类型> 函数名 (<参数1类型> 参数1，<参数2类型> 参数2，……)
3.  实际开发中，可根据实际需求定义其他的基本操作
4.  函数名和参数的形式、命名都可改变（Reference：严蔚敏版《数据结构》）
5.  什么时候要传入引用`&` —— 对参数的修改结果需要"**带回来**"

## 引用的意思
例如：以C++中的引用符号`&`为例，
```c
//没有使用引用"&"
#include <iostream>
using namespace std;
void test(int x)
{
    x = 1024;
    cout << "test 函数内部 x  = " << x << endl;
}

int main()
{
    int x = 1;
    cout << "调用test前 x = " << x << endl;
    test(x);
    cout << "调用test后 x = " << x << endl;
    return 0;
}
```

```txt
输出：
    调用test前 x = 1
    test 函数内部 x  = 1024
    调用test后 x = 1
```

局部变量在代码块执行结束后即销毁。
```cpp
//使用引用"&"
#include <iostream>
using namespace std;
void test(int &x)
{
    x = 1024;
    cout << "test 函数内部 x  = " << x << endl;
}
int main()
{
    int x = 1;
    cout << "调用test前 x = " << x << endl;
    test(x);
    cout << "调用test后 x = " << x << endl;
    return 0;
}
```

```txt
输出：
    调用test前 x = 1
    test 函数内部 x  = 1024
    调用test后 x = 1024
```

`&`引用类型是C++对C的补充，是C++的一种重要的数据类型，在C 的编译环境不支持。  
在该数据结构课程内容中，借用C++中的引用类型，表示对数据的传参补充。  
具体区别可以见下图：

![](img/02_linear_list/02%20是否传引用&的区别.jpg)

# [8] 顺序表的定义
顺序表是使用顺序存储的方式实现线性表存储。  
把逻辑上相邻的元素存储在物理位置上也相邻的存储单元中，元素之间的关系由存储单元的邻接关系来体现。 
设线性表的第一个元素的位置存放位置是`LOC(L)` 
这里的LOC代表 location。  
在C中，`sizeof(ElemType)`可以显示除顺序表中存放的数据类型。  

## 1. 静态分配
```c
// 给各个数据元素分配连续的存储空间，大小为MaxSize*sizeof(ElemType)
#define MaxSize 10              // 定义最大长度
typedef struct
{
    ElemType data[MaxSize];     // 用静态的"数组"存放数据元素
    int length;                 // 顺序表的当前长度
}
SqList;                         // 顺序表的类型定义（静态分配方式）
```

### 程序举例
```cpp
#include <stdio.h>
#define MAXSIZE 10
typedef struct{   
    int data[MAXSIZE];
    int length;
} SqList;

// 这里在gcc编译器中是无法通过编译的，因为C不支持引用类型
// 在这里必须使用g++编译器，使用C++语法编译

void InitList(SqList &L)
{
    for (int i = 0; i < MAXSIZE; i++)
        L.data[i] = 0;
    L.length = 0;
} 

int main()
{
    SqList L;
    InitList(L);
    for (int i = 0;i<MAXSIZE;i++)
        printf("data[%d]=%d\n", i, L.data[i]);
    return 0;
}
```

### 输出
```txt
data[0]=0
data[1]=0
data[2]=0
data[3]=0
data[4]=0
data[5]=0
data[6]=0
data[7]=0
data[8]=0
data[9]=0
```

Q：如果“数组”存满了怎么办？  
A：只能放弃治疗，顺序表的表长刚开始确定后就**无法更改**（存储空间是静态的）。

## 2. 动态分配
```cpp
#define InitSize 10     // 顺序表的初始长度
typedef struct {
    ElemType *data;     // 指示动态分配数组的指针
    int MaxSize;        // 顺序表的最大容量
    int length;         // 顺序表的当前长度
} SeqList;              // 顺序表的类型定义（动态分配方式）
```
Key : 动态申请和释放内存空间
在C中，动态申请使用 malloc、free函数
```c
L.data = (ElemType*) malloc (sizeof(ElemType) * InitSize);
```

C++ 使用 new、delete关键字  
`malloc` 函数返回一个指针，空间需要强制转型为你定义的数据元素类型指针，`malloc`函数的参数，指明要分配多大的连续内存空间。

### 程序举例
```cpp
#include <stdio.h>
#include <stdlib.h>
#define InitSize 10     // 默认最大长度
typedef struct{   
    int *data;          // 指示动态分配数组的指针
    int MaxSize;        // 顺序表的最大容量
    int length;         // 顺序表的当前长度
} SqList;

void InitList(SqList &L)
{   // 用malloc函数申请一片连续的存储空间
    L.data = (int *)malloc(InitSize * sizeof(int));
    L.length = 0;
    L.MaxSize = InitSize;
} 

// 表的大小不够了，需要重新增加表的尺寸
void IncreaseSize(SqList &L, int len)
{
    // 原始表的首元素地址赋值给p，临时变量存储
    int *p = L.data;
    
    // 重新分配了一片内存，并将新的首元素内存赋给了L.data,替换了原来的p
    L.data = (int *)malloc((L.MaxSize + len) * sizeof(int));
    
    // 这里的 L.length 在表被插入添加新元素的时候，也被刷新赋值了
    for (int i = 0; i < L.length; i++)
    {
        L.data[i] = p[i];
    }
    L.MaxSize = L.MaxSize + len;
    free(p);
}

int main()
{
    SqList L;
    InitList(L);
    // …… 往顺序表中随便插入几个元素 ……
    IncreaseSize(L, 5);
    return 0;
}
```

![](img/02_linear_list/03%20顺序表的动态扩充.jpg)

## 总结，顺序表的特点
1. **随机访问**，即可以在 `O(1)` 时间内找到第 `i` 个元素
2. 存储密度高，每个结点只存储数据元素
3. 拓展容量不方便（即便采用动态分配的方式实现，拓展长度的时间复杂度也比较高）
4. 插入、删除操作不方便，需要移动大量元素

# [9] 顺序表的插入删除
## 1. 插入
```c
// 插入操作。在表L中的第i个位置上插入指定元素e。
ListInsert(&L, i, e)，
```
### 程序举例
```cpp
#define MaxSize 10              // 顺序表的初始长度
{
    ElemType data[MaxSize];     // 用静态的"数组"存放数据元素
    int length;                 // 顺序表的当前长度
}
SqList; 
```
对于顺序表的插入，大致分为以下两个步骤：  
1. 将第`i`个元素之后的每个元素都往后移一位，从最末尾一位开始，到第`i`个结束；
2. 给第`i`个元素重新赋值，插入完成。

![](img/02_linear_list/04%20顺序表的增加数据.jpg)

### 初步思路
```cpp
void ListInsert(SqList &L, int i, int e)
{
    for (int j = L.length; j >= i; j--) {
    /* 把第i个元素以及以后的每个元素都后移，从最末尾的元素开始，直至第i个元素*/
        L.data[j] = L.data[j - 1];  
    }    
    L.data[i - 1] = e;
    L.length++;
}
```
这个代码有两个问题：
1. 如果插入的元素位次，超过了原先的L.Length，不合法；
2. 如果原来的表已经满了，无法继续插入；

![](img/02_linear_list/05%20顺序表插入例外情况.jpg)

### 修改优化
因此对原代码进行修改：
```cpp
// i指位序，不是数组下标
bool ListInsert(SqList &L, int i, int e)
{
    if(i < 1 || i > L.length + 1)
        return false;
    if(L.length >= MaxSize)
        return false;
    for(int j = L.length; j >= i; j--) {
    /* 把第i个元素以及以后的每个元素都后移，从最末尾的元素开始，直至第i个元素*/
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1]=e;
    L.length++;
    return true;
}
```

### 疑问
**问题**：在这段代码里，分支结构仅仅单独的`if……if……`，而没有有`if……else if……`判定，这两者有什么区别呢？ 
**回答**：使用 `if` 直接条件判断，等于是使用卫语句，减少条件分支。

### 算法评价
时间复杂度：
- 问题规模 `n = L.length` （表长）
1. 最好情况：新元素插入到表尾，不需要移动元素  
  `i = n + 1`，循环0次；最好时间复杂度 = `O(1)`
2. 最坏情况：新元素插入到表头，需要将原有的 n 个元素全都向后移动  
  `i = 1`，循环 n 次；最坏时间复杂度 = `O(N)`;
3. 平均情况：假设新元素插入到任何一个位置的概率相同，  
  即 `i = 1,2,3, … , length + 1` 的概率都是:   
  $p = \frac{1}{n+1}$。

    当 i = 1，循环 n 次；   
    当 i = 2 时，循环 n-1 次；  
    当 i = 3，循环 n-2 次；   
    ……  
    当i = n + 1 时，循环0次；
  平均循环次数：

> $$ AVG = np + (n-1)p + (n-2)p + …… + 1⋅p =\frac{n(n+1)}{2}×\frac{1}{n+2}=\frac{n}{2}$$ 

因此：平均时间复杂度 =  `O(N)`

## 2. 删除

```c
// 删除操作。删除表L中第i个位置的元素， 并用e返回删除元素的值。
ListDelete(&L, i, &e);
```

![](img/02_linear_list/06%20顺序表的删除数据.jpg)


```cpp
bool ListDelete(SqList &L,int i,int &e)
{
    if (i < 1 || i > L.length) {
        return false;
    }
    e = L.data[i - 1];
    // 这里把删除的元素赋给e
    for (int j = i; j < L.length; j++) {
        L.data[j-1] = L.data[j];
    }
    L.length--;
    
    return true;
}

int main()
{
    SqList L;
    InitList (L);
    /* 省略插入元素 */
    int e = -1;
    if (ListDelete(L, 3, e)) {
        printf("已经删除第三个元素，删除元素值为%d\n",e);
    } else {
        printf("位序i不合法，删除失败\n");
    }
        
    return 0;

}
```
时间复杂度推到过程和插入相同，推导过程省略，同为`O(N)`.


# [10]  顺序表的查找

![](img/02_linear_list/07%20顺序表查找.jpg)

## 1. 按位查找
```c
// 按位查找，获取表L中第i个位置的元素的值。
GetElem(L, i):
```

### 1. 静态数组：
```c
#define MaxSize 10
type struct {
    ElemType data[MaxSize];
    int length;
} Sqlist;

ElemType GetElem(Sqlist L,int i) 
{
    return L.data[i - 1];
}
```

### 2. 动态分配数组：
```c
#define InitSize 10
typedef struct {
    ElemType *data;     // 指示动态分配数组的指针
    int MaxSize;            
    int length;
} SeqList;

ElemType GetElem(Sqlist L,int i) 
{
    return L.data[i - 1]; // 以指针代替数组表示法
}
```
时间复杂度是`O(1)`, 因为没有循环，也没有递归

## 2. 按值查找
```c
// 按值查找操作，在表L中查找具有给定关键字值的元素。
LocateElem(L, e);
```

程序实现：
```cpp
#define InitSize 10
typedef struct {
    ElemType *data;
    int MaxSize;
    int length;
} SeqList;

// 在顺序表L中查找第一个元素值等于e的元素，并返回其位序
int LocateElem(SeqList L, ElemType e) 
{
    for (int i = 0; i < L.length; i++) {
       if (L.data[i] == e) {
           return i + 1;     // 返回的位序是数组下边+1
       }
    }
    return 0;
}
```
注意，对于结构体数据类型，不可以使用`a==b`这样的形式来判定的。

时间复杂度：`O(N)`.

