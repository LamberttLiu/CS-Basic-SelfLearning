#数据结构 
# [34] 串的定义和基本操作

## 基础定义
**串**，即**字符串**（String）是由零个或多个字符组成的有限序列。一般记为： 
$$S = 'a_1 a_2······a_n' (n ≥0)$$   
其中：
- `S`是串名，
- 单引号括起来的字符序列是串的值 ，
-  $a_i$  可以是字母、数字或其他字符。
- 串中字符的个数 $n$ 称为串的长度。
-  $n = 0$ 时的串称为空串（ 用`∅`表示 ）。

例:  
```c
S = "HelloWorld!";
```

```python
T = 'iPhone 11 Pro Max?';
```

![](img/04_string/01%20字符串.jpg)

注：对于字符串，有的语言用双引号（如Java、C），有的语言用单引号（如Python）。  

## 其他衍生
- **子串**：串中任意个连续的字符组成的子序列。  
    例如，`'iPhone'`，`'Pro M' `是串 `T` 的子串。

- **主串**：包含子串的串。  
    例如，`T` 是子串`'iPhone'`的主串。

- **字符在主串中的位置**：字符在串中的序号，非数组下标。   
    例如，`'1'` 在 `T` 中的位置是8（第一次出现）。 

- **子串在主串中的位置**：子串的第一个字符在主串中的位置。   
    例如，`'11 Pro'`在 `T` 中的位置为8

![](img/04_string/02%20主串和子串.jpg)

注意：位序从1开始,而不是从0开始。

- **空串** V.S **空格串**  
    `M=''`, `M` 是空串  
    `N='   '`, `N` 是由三个空格字符组成的空格串，每个空格字符占1B。

串是一种特殊的线性表，数据元素之间呈线性关系。  
串的数据对象**限定为字符集**（如中文字符、英文字符、数字字符、标点字符等）

## 串的基本操作
有**增、删、改、查**等，通常**以子串**为操作对象。

- `StrAssign(&T, chars)`  
  赋值操作。把串 `T` 赋值为 `chars` 。

- `StrCopy(&T, S)`   
  复制操作。由串`S`复制得到串`T`。 

- `StrEmpty(S)`  
  判空操作。若`S`为空串，则返回`TRUE`，否则返回`FALSE`。
- `StrLength(S)`  
  求串长。返回串`S`的元素个数。

- `ClearString(&S)`  
  清空操作。将`S`清为空串。
- `DestroyString(&S)`  
  销毁串。将串`S`销毁（回收存储空间）。

清空和销毁操作是有区别的，清空仅仅清空数据，销毁指内存归还给系统。

- `Concat(&T, S1, S2)`  
  串联接。用`T`返回由`S1`和`S2`联接而成的新串

- `SubString(&Sub, S, pos, len)`  
  求子串。用`Sub`返回串`S`的第`pos`个字符起长度为`len`的子串。

- `Index(S, T)`  
  定位操作。
  若主串`S`中存在与串`T`值相同的子串，则返回它在主串`S`中第一次出现的位置；否则函数值为0。

- `StrCompare(S, T)`   
  比较操作。若`S>T`，则返回值>0；若`S=T`，则返回值=0；若`S<T`，则返回值<0。

例如：
有串 `T=""`, `S= "iPhone 11 Pro Max?"`, `W="Pro"`  

- 执行基本操作 `Concat(&T, S, W)` 后，  
    `T="iPhone 11 Pro Max?Pro"`  

- 执行基本操作 `SubString(&T ,S, 4, 6)`后，  
  `T="one 11"`

- 执行基本操作 `Index(S, W)` 后，  
  返回值为 `11`

## 串的比较操作（字典排序）
在数学中，字典或词典顺序（也称为词汇顺序，字典顺序，字母顺序或词典顺序）是基于字母顺序排列的单词按字母顺序排列的方法。 这种泛化主要在于定义有序完全有序集合（通常称为字母表）的元素的序列（通常称为计算机科学中的单词）的总顺序。  
例如：
- `"abandon" < "aboard"`，  
 从第一个字符开始往后依次对比，先出现更大字符的串就更大。

- `"abstract" < "abstraction"`，  
  长串的前缀与短串相同时，长串更大。

- `"academic"="academic"`，  
  只有两个串完全相同时才相等。

任何数据存到计算机中一定是二进制数。需要确定一个字符和二进制数的对应规则这就是“**编码**”。

“**字符集**”：  
英文字符——ASCII字符集，中英文——Unicode字符集。  
注：采用不同的编码方式，每个字符所占空间不同，一般只需默认每个字符占1B即可。

# [35] 串的存储结构
结合线性表的知识，串是一种有特殊的线性表，原本的`ElemType`只需要被替换成`char`类型即可。
## 1. 顺序存储
同顺序表一样，字符串可以有：  
静态分配
```c
// 静态数组
#define MaxLen 255      // 预定义最大串为255
typedef struct StaticString {
    char ch[MaxLen];    // 每个分量存储一个字符
    int length;         // 串的实际长度    
} StaticString;         // 静态数组实现(定长顺序存储)
```
和动态分配，两类内存空间分配的形式。
```c
// 动态数组形式
#define MaxLen 255      // 预定义最大串为255
typedef struct DynmString {
    char *ch;           // 按串长分配存储区，ch指向串的基地址
    int length;         // 串的长度
} DynmString;           // 动态数组实现（堆分配存储）
DynmString S;

// 使用malloc，用完需要手动free
S.ch = (char*)malloc(MaxLen * sizeof(char));
S.length = 0;         
```

用数组来表示串，通常有四种方式（序号和索引值的不同）。
1. 变量Length单独存放，位序与索引值不同；
2. 变量Length放在索引为0的位置，字符的位序和数组下标相同；
3. 没有Length变量，以字符`'\0' `表示结尾（对应ASCII码的 0）;
4. Length变量单独存放，`ch[0]`废弃不用。

![](img/04_string/03%20数组表示字符串.jpg)

四种方案各有优劣，本文采用第四种表达字符串的方式。

## 2. 链式存储
```c
typedef struct StringNode {
    char ch;            
    struct StringNode *next;
} StringNode, *String;
```

![](img/04_string/04%20链表表示串.jpg)

这种方式存储密度低，数据1B，指针4B，可以修改为四个字符一组，
```c
typedef struct StringNode {
    char ch[4];         // 一个结点4B
    struct StringNode *next;
} StringNode, *String;
```
因为链式存储的步骤较为复杂，存储不够灵活。因此后面以顺序存储为例，对字符串进行操作。
## 3. 基于顺序存储的基本操作实现
重点关注以下的操作：
### (1) 求子串
`SubString(&Sub,S,pos,len)`，用`Sub`返回串`S`的第`pos`个字符起长度为`len`的子串。

![](img/04_string/05%20求子串.jpg)

思路：将字符串`S`的位序从`pos`到`pos + len -1` 的这个`len`个字符逐一复制给`Sub`。
```c
#define MaxLen 255      // 预定义最大串为255
typedef struct {
    char ch[MaxLen];    // 每个分量存储一个字符
    int length;         // 串的实际长度    
} StaticString;         // 静态数组实现(定长顺序存储)

/*
 *  S.ch = "Computer"
 *  S.length = 8
 */

// 求子串
bool SubString (StaticString &Sub, StaticString S, int pos, int len)
{
    // 判定串越界
    // 头字符序数pos，长度为len，尾序数为pos + len - 1
    if (pos + len - 1 > S.length) {     
        return false;
    }
    for (int i = pos; i < pos + len; i++) {
        Sub.ch[i - pos + 1] = S.ch[i];       // 从索引1开始
    }
    Sub.length = len;
    return true;
}
```

### (2) 字符串比较（字典排序）
`StrCompare(S, T)`：比较操作。  
若`S > T`，则返回值 > 0；若`S = T`，则返回值 = 0；若`S < T`，则返回值 < 0。

![](img/04_string/06%20串比较.jpg)

```c
// 比较操作
int StrCompare (StaticString S,StaticString T)
{
    // 循环次数 min{strlen(S),Strlen(T)};
    // 循环从1开始，因为数组首个位置为空。
    for (int i = 1; i <= S.length && i <= T.length; i++){
    // 一旦遇到不相等的，作差
        if (S.ch[i] != T.ch[i]) {
            return S.ch[i] - T.ch[i];
        }
    }
    // 到这里，已经退出循环，在循环内的字符逐一比较均完全相等。那么，长度长的串更大。
    return S.length - T.length;
}
```

### ★ (3) 定位操作
`Index(S, T)`：定位操作。若主串`S`中存在与串`T`值相同的子串，则返回它在主串`S`中第一次出现的位置；否则函数值为0。这一操作，需要建立在前面两个基础函数上。

![](img/04_string/07%20串的模式匹配.jpg)
```c
int Index(StaticString S, StaticString T)
{
    int pos = 1, SLen = StrLength(S), TLen = StrLength(T);
    StaticString subStr;      // 暂存子串
    /* 最多比较次数 --> SLen - TLen + 1
       首次比较，主串的索引为 1（从头开始比较，S与T头对齐），
       最后一次比较，主串的索引为 SLen - TLen + 1 （S与T 尾对齐，索引为长度差值加1）
       因此从首到尾，逐一比较，次数为：SLen - TLen + 1 
     */
    while (pos <= SLen - TLen + 1)
    {
        // 从主串 S 中以i为首，子串长度TLen为长度，取出符合条件的子串。
        SubString(subStr, S, pos, TLen);

        // 比较该子串与目的子串T是否一致
        if (StrCompare(subStr, T) != 0) {
            ++pos;            // 不一致的话，进行下一个对比
        } else {
            return pos;      // 一致的话，返回子串的首，即定位索引。
        }
    }
    return 0;                // S中不存在与T相等的子串
}
```
以上的串定位方法，可以抽象成一种滑动窗口。

