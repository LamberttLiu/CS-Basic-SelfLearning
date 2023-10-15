#C #算法 

# [82] uthash库的哈希实现
散列表（哈希表、HashTable）是一种常用的数据结构，在使用`C++`的时候STL库中的`unordered_map`也就是哈希表，使用`python`时使用字典来进行数据检索。这些数据结构都可以通过`key`值来进行唯一检索需要的`value`。  
那么，在C语言中，我们应该如何实现哈希表呢？当哈希表中元素比较简单时，我们可以直接构造一个数组，把下标看作`key`值，`value`值就是该下标对应得元素值。但是当我们需要使用很多复杂操作时，还是希望能找到一个类似于内置函数的东西去实现对于哈希表的各种操作。  

于是，`uthash`就出现了！

`uthash` 是C的比较优秀的开源代码，它实现了常见的hash操作函数，例如查找、插入、删除等。该套开源代码采用宏的方式实现hash函数的相关功能，支持C语言的任意数据结构作为key值（可以是自定义的struct或基本数据类型），甚至可以采用多个值作为key，需要注意的是对于不同类型的key值，hash函数声明略有不同。
`uthash`相当于为我们提供了一个专门用于处理哈希表的函数库，在学会它里面基本函数的用法后，就可以应用在自己的程序中了。

![](img/07_search/21%20Hashmap.jpg)


**鉴于网上有很多关于**`uthash`**的教程，但是对新手都不友好，这里作者自绘插图，更方便表示哈希的**`uthash`**常用操作**。

## 1.hash预定义
### 添加头文件
由于`uthash`是以宏的方式定义了对哈希表的操作函数，因此想在代码中使用`hash`函数时，一定要在自己程序的初始添加`uthash`头文件。当然还得先下载源代码。
```c
#include "uthash.h"
```
### 创建键-值对结构
`uthash`中定义的哈希表中每个键值对都是一个实例化的结构体，这里以key是int变量，value是一个字符串为例，结构体定义如下：
```c
// 这里使用重定义结构，在以后命名中将省略struct词
typedef struct {
    int ikey;                  /* key */
    char name[10];             /* value */
    UT_hash_handle hh;         /* makes this structure hashable */
} HashtableNormal;
```
在结构体定义中：
key的数据类型可以是**整型、字符、指针**等，
value的类型也是**自定义**的，并且value是不一定存在的。

![](img/07_search/22%20Key-Value%20Pair.jpg)

我们可以在结构体中只定义key值，这样哈希表就只关注表中有没有某个key，而不关心它对应的value值；这样构造出的哈希表可以看作是`C++`中的`set`，可以保证内部无重复的元素（因为哈希表的key不能有重复）：
集合`set`的数据结构：
```c
typedef struct {
    int ikey;                  /* key */
    UT_hash_handle hh;         /* makes this structure hashable */
} HashtableOnlyKey;
```
结构体中key的定义一定要有，`UT_hash_handle hh` 也不能去掉。
hh是内部使用的hash处理句柄，在使用过程中，只需要在结构体中定义一个`UT_hash_handle`类型的变量即可，**不需要为该句柄变量赋值**，但必须在该结构体中定义该变量。

## 2.初始化哈希表
可以想到哈希表就是上面这种键-值对的数组，因此我们定义一个指向struct类型的指针就可以表示哈希表 (数组和指针的关系)，可以对它进行增删改查操作。

![](img/07_search/23%20HashTbl逻辑结构.jpg)

初始化一个哈希表：
```c
typedef struct {
    int ikey;                  /* key */
    char name[10];             /* value */
    UT_hash_handle hh;         /* makes this structure hashable */
} Hashtable;

HashTable *pHash = NULL;       /* 在使用之前一定要赋空 */
```
这里注意一定要初始化为NULL，不然会报错！

## 3.查找元素 HASH_FIND_INT
函数定义：
```c
/* pDstHash: output pointer */
HASH_FIND_INT(Hashtable* pHashFind, int* key, Hashtable* pDstHash);
```
**参数含义**：
- `pHashFind`：待查询的hash表，可以理解为整个HashTable的头指针，以指针形式入参；
- `key`：指向想查询的key，对原int值取地址；
- `pDstHash`： 表示该函数的输出值，即我们根据key查到的键值对，它是一个指向哈希表HashTable中该键值对的指针。
因此在调用该函数前，要先定义pDstHash，完整用法如下：

![](img/07_search/24%20HashTbl查找.jpg)

```c
typedef struct {
    int ikey;                  /* key */
    char name[10];             /* value */
    UT_hash_handle hh;         /* makes this structure hashable */
} Hashtable;

/* 获得key的键值对的函数，查找失败返回空 */
HashTable *FindHashbyKey(int key) 
{   
    Hashtable *pDstHash = NULL;            /* 定义 pDstHash */
    HASH_FIND_INT(pHash, &key, pDstHash);   /* pDstHash: output pointer */
    return pDstHash;
}

if (pDstHash != NULL) {
    char *output = pDstHash->name;          /* 获取value*/
}

```

## 4.插入元素 HASH_ADD_INT
由于要保持哈希表中的唯一性，在插入键值对之前，一定要先判断表中是否已经存在要插入的键，如果已存在，就直接修改键对应的value；如果没有存在，插入键值对。

![](img/07_search/25%20HashTbl插入.jpg)

函数定义：
```c
/* key: name of key field */
HASH_ADD_INT(Hashtable* pHashInserted, int *key, Hashtable* pKVPair);  
```
**参数含义**：
- `pHashInserted`：已经存在，待被插入的hash表；
- `key`：自定义的键值对结构体HashTable中，key域的变量名；即下面struct中的“ikey”。注意这里只把变量名输入即可，不需要带入值。
- `pKVPair`：需要插入的键值对结构体，是指针形式。它的key和value已经确定了。

完整用法：
```c
typedef struct {
    int ikey;                  /* key，这里使用ikey是做索引，区别key值 */
    char name[10];             /* value */
    UT_hash_handle hh;         /* makes this structure hashable */
} HashTable;

void InsertHashbyKey(int key, char *name)
{
    HashTable *pKVPair = NULL;

    /* 判断key值是否已经存在? */
    HASH_FIND_INT(pHashInserted, &key, pKVPair); 
    
    /* key值不存在 */
    if (pKVPair == NULL) {
      pKVPair = (HashTable *)malloc(sizeof(HashTable));
      pKVPair->ikey = key;
      /* key: name of key field */
      HASH_ADD_INT(pHashInserted, key, pKVPair);  
    }
    /* pKVPair的key存在，直接更新value值 */
    strcpy(pKVPair->name, name);   
}
```

## 5.统计元素个数 HASH_COUNT
函数定义：
```c
numsElement = HASH_COUNT(pHashTable);
```
**参数含义**：
- `pHashTable`：待统计元素个数的hash表
函数输出即为哈希表中存在的键值对个数。

## 6.循环表中元素 HASH_ITER
函数定义：
```c
HASH_ITER(hh, HashTable *pHashTable, HashTable *pKVPair, HashTable *pTmp)
{
	/* ... code ... */
}
```
**参数含义**：
- `hh`：表示hash句柄，不是个变量；
- `pHashTable`：待循环的hash表；
- `pKVPair`：表示每次循环时获得的那个键值对，在函数前直接定义，不用赋初值。在循环中，我们就对`pKVPair`进行操作。
- `pTmp`：临时变量。这个变量从表面上来看没有什么意义，但是会在这个函数内部被使用，所以一定要声明一个tmp结构体指针（不用赋值），并送入函数。

循环遍历哈希表
```c
typedef struct {
    int ikey;                  /* key，这里使用ikey是做索引，区别key值 */
    char name[10];             /* value */
    UT_hash_handle hh;         /* makes this structure hashable */
} HashTable;

HashTable *pKVPair, *pTmp;    // pTmp 类似于for循环的i值
HASH_ITER(hh, pHashTable, pKVPair, pTmp)
{
    /* 遍历操作 */
    printf("key [%d]: name [%s]\n", pKVPair->ikey, pKVPair->name);
}
```

## 7.删除表中元素 HASH_DEL
函数定义：
```c
HASH_DEL(HashTable *pHashTable, HashTable *pKVPair);
```
**参数含义**：
- `pHashTable`：需要删除的表，表内包含大量键值对；
- `pKVPair`：需要删除的一对键值对。

![](img/07_search/26%20HashTbl删除.jpg)

根据key值删去键值对结构，必须具有指向它的指针，所以在删除前需要先查找。
```c
void DeleteKey(HashTable* pHashTable, int key)
{
    HashTable *pKVPair = FindHashbyKey(key);
    // 查找不存在
    if (pKVPair == NULL) {
        return;
    }
    HASH_DEL(pHashTable, pKVPair);
    free(pKVPair);
}
```

## 关于其他函数使用：
```c
HASH_ADD_STR    // 表示添加的键的值为字符串类型
HASH_ADD_PTR    // 表示添加的键的值为指针类型
HASH_ADD        // 表示添加的键的值可以是任意类型
```
本文仅仅以int类型作为举例。

## 参考链接：
1. github下载链接：https://github.com/troydhanson/uthash
2. 博客园：https://www.cnblogs.com/dongxb/p/14212531.html