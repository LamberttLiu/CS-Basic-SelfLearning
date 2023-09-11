#C #算法 
# 一、`uthash`库
哈希散列表是一种常用的数据结构，在使用python时我们常常会使用字典来进行数据检索，这个字典实际就是哈希表，通过key值来进行唯一检索。

那么，在C语言中，我们应该如何实现哈希表呢？当哈希表中元素比较简单时，我们可以直接构造一个数组，把下标看作key值，value值就是该下标对应得元素值。但是当我们需要使用很多复杂操作时，还是希望能找到一个类似于内置函数的东西去实现对于哈希表的各种操作。

于是，`uthash`就出现了！
`uthash` 是C的比较优秀的开源代码，它实现了常见的hash操作函数，例如查找、插入、删除等。该套开源代码采用宏的方式实现hash函数的相关功能，支持C语言的任意数据结构作为key值（可以是自定义的struct或基本数据类型），甚至可以采用多个值作为key，需要注意的是对于不同类型的key值，hash函数声明略有不同。
`uthash`相当于为我们提供了一个专门用于处理哈希表的函数库，在学会它里面基本函数的用法后，就可以应用在自己的程序中了。
![[img/Sx 补充/uthash/01 Hash.jpg]]
**鉴于网上有很多关于**`uthash`**的教程，但是对新手都不友好，这里作者自绘插图，更方便表示哈希的**`uthash`**常用操作**。

# 二、hash预定义
## 1.添加头文件
由于uthash是以宏的方式定义了对哈希表的操作函数，因此想在代码中使用hash函数时，一定要在自己程序的初始添加uthash头文件。当然还得先下载源代码。
```c
#include "uthash.h"
```

## 2.创建键-值对结构
`uthash`中定义的哈希表中每个键值对都是一个实例化的结构体，结构体定义如下：
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
我们可以在结构体中只定义key值，这样哈希表就只关注表中有没有某个key，而不关心它对应的value值；这样构造出的哈希表可以看作是python中的set，可以保证内部无重复的元素（因为哈希表的key不能有重复）：
![[img/Sx 补充/uthash/02 key-Value.png]]

```c
typedef struct {
    int ikey;                  /* key */
    UT_hash_handle hh;         /* makes this structure hashable */
}HashtableOnlyKey;
```
结构体中key的定义一定要有，`UT_hash_handle` hh也不能去掉。
hh是内部使用的hash处理句柄，在使用过程中，只需要在结构体中定义一个`UT_hash_handle`类型的变量即可，**不需要为该句柄变量赋值**，但必须在该结构体中定义该变量。

# 三. 初始化哈希表
可以想到哈希表就是上面这种键-值对的数组，因此我们定义一个指向struct类型的指针就可以表示哈希表 (数组和指针的关系)，可以对它进行增删改查操作。
![[img/Sx 补充/uthash/03 Hashtable.png]]

初始化一个哈希表：
```c
typedef struct {
    int ikey;                  /* key */
    char name[10];             /* value */
    UT_hash_handle hh;         /* makes this structure hashable */
} Hashtable

HashTable *pHash = NULL;    /* 在使用之前一定要赋空 */
```
这里注意一定要初始化为NULL，不然会报错！

# 四. 查找元素 HASH_FIND_INT
函数举例
```c
HASH_FIND_INT(pFindHash, &key, pDstHash);    /* pDstHash: output pointer */
```
**参数含义**：
- `pFindHash`：待查询的hash表，指针形式入参；
- `&key`：     指向想查询的key的地址；
- `pDstHash`： 表示该函数的输出值，即我们根据key查到的键值对；它是一个指向哈希表HashTable中该键值对的指针。
因此在调用该函数前，要先定义pDstpHash，完整用法如下：
![[img/Sx 补充/uthash/04 Hashfind.png]]

```c
/* 获得key的键值对的函数 */
HashTable *FindHashbyKey(int key) {   
    Hashtable *pDstpHash;                   /* 定义 pDstHash */
    HASH_FIND_INT(pHash, &key, pDstHash);   /* pDstHash: output pointer */
    return pDstHash;
}
```

# 五. 插入元素 HASH_ADD_INT
由于要保持哈希表中的唯一性，在插入键值对之前，一定要先判断表中是否已经存在要插入的键，如果已存在，就直接修改键对应的value；如果没有存在，插入键值对。
![[img/Sx 补充/uthash/05 HashInsert.png]]

函数举例
```c
HASH_ADD_INT(pHashInserted, key, pKeyValuePair);  /* key: name of key field */
```
**参数含义**：
- `pHashInserted`：已经存在，待被插入的hash表；
- `key`：自定义的键值对结构体HashTable中，key域的变量名；即下面struct中的“id”；注意这里只把变量名输入即可，不需要带入值。
- `pKeyValuePair`：需要插入的键值对结构体，是指针形式。它的key和value已经确定了。
完整用法：
```c
typedef struct {
    int ikey;                  /* key，这里使用ikey是做索引，区别key值 */
    char name[10];             /* value */
    UT_hash_handle hh;         /* makes this structure hashable */
} HashTable;

void InsertHashbyKey(int key, char *name) {
    HashTable *pKeyValuePair;

    /* 判断key值是否已经存在? */
    HASH_FIND_INT(pHashInserted, &key, pKeyValuePair); 
    /* 判断key值是否不已经存在 */
    if (pKeyValuePair == NULL) {
      pKeyValuePair = (HashTable *)malloc(sizeof *HashTable);
      pKeyValuePair->ikey = key;
      /* key: name of key field */
      HASH_ADD_INT(pHashInserted, key, pKeyValuePair);  
    }
    /* pKeyValuePair的key存在，直接更新value值 */
    strcpy(pKeyValuePair->name, name);   
}
```

# 五.统计元素个数 HASH_COUNT
函数使用：
```c
numsElement = HASH_COUNT(pHashTable);
```
**参数含义**：
- `pHashTable`：待统计元素个数的hash表
函数输出即为哈希表中存在的键值对个数。

# 六.循环表中元素 HASH_ITER
循环遍历哈希表
```c
HashTable *pKeyValuePair, *pTmp;    // pTmp 类似于for循环的i值
HASH_ITER(hh, pHashTable, pKeyValuePair, pTmp){
    /* 遍历操作 */
    printf("key %d: name %s\n", pTmp->ikey, pTmp->name);
}
```
**参数含义**：
- `hh`：表示hash句柄，不是个变量；
- `pHashTable`：待循环的hash表；
- `pKeyValuePair`：表示每次循环时获得的那个键值对，在函数前直接定义，不用赋初值。在循环中，我们就对s进行操作。
- `pTmp`：临时变量。这个变量从表面上来看没有什么意义，但是会在这个函数内部被使用，所以一定要声明一个tmp结构体指针（不用赋值），并送入函数。

# 六.删除表中元素 HASH_DEL
根据key值删去键值对结构，必须具有指向它的指针
```c
void DeletebuKey(HashTable** pHashTable, int key){
    HashTable *pKeyValuePair = FindHashbyKey(key);
    HASH_DEL(*pHashTable, pKeyValuePair);
    free(pKeyValuePair);
}
```

# 关于其他函数使用：
```
HASH_ADD_INT    表示添加的键的值为int类型
HASH_ADD_STR    表示添加的键的值为字符串类型
HASH_ADD_PTR    表示添加的键的值为指针类型
HASH_ADD        表示添加的键的值可以是任意类型
```
本文仅仅以int类型作为举例。

## 参考链接：
1. github下载链接：https://github.com/troydhanson/uthash
2. 博客园：https://www.cnblogs.com/dongxb/p/14212531.html
3. [开源库uthash第一弹uthash.h_konishi5202的博客-CSDN博客_uthash.h](https://blog.csdn.net/a123441/article/details/89045293?utm_source=app&app_version=4.5.2)
4. [开源库uthash第二弹utlist.h_konishi5202的博客-CSDN博客](https://blog.csdn.net/a123441/article/details/90374650?spm=1001.2014.3001.5502)