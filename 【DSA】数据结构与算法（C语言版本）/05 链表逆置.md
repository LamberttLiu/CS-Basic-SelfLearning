#数据结构 #C 

# [20] 链表逆置
链表逆置，或者说反转链表，是最常规的链表操作，需要单独拆出来，总结归纳。  
首先我们要明白什么是链表逆置，链表逆置顾名思义，链表的表头和表位改变，整个顺序完全反转。打个比方如果链表就是一列火车的话，链表逆置以后，火车头变成火车尾，第二节车厢会变成倒数第二节车厢，第三节车厢变成倒数第三节车厢以此类推最后火车尾变成火车头。

如图所示：  
![](img/02_linear_list/33%20逆置链表.JPG)

# 0.初始化准备
## 0.1 链表的声明
```cpp
typedef struct LinkedList
{
    int date;
    LinkedList* next;
} LinkedList;
```

## 0.2 创建链表
为了演示方便，这里使用的是不带头结点的链表形式，使用尾插入法创建链表：
![](img/02_linear_list/20%20单链表尾插法.JPG)

```cpp
LinkedList* CreateLinkedList()
{
    LinkedList* head = NULL, * current = NULL, * prev = NULL;
    int data;
    // 按次序输入数字，0为标记输入结束
    while (scanf("%d", &data) && data != 0)  
    {
        current = (LinkedList*)malloc(sizeof(LinkedList));
        /* 区分两种情况，首次插入和非首次插入
           首次插入，直接分配给头结点，
           非首次插入，分配给前结点的后驱结点 */
        if (head == NULL) {
            head = current;
        } else {
            prev->next = current;
        }
        
        current->date = data;
        current->next = NULL;
        prev = current;
    }
    return head;
}
```

## 0.3 打印链表
我们有了链表当然也得有个输出链表内部数据的函数，来验证查看我们链表内的内容。
```cpp
void PrintList(LinkedList* L)
{
    LinkedList* p = L;
    while (p)
    {
        printf("%d", p->date);
        p = p->next;
    }
    printf("\n");
}
```

## 0.4 释放内存
```cpp
void FreeList(LinkedList* head)
{
    LinkedList* freeNode;

    while (head != NULL)
    {
        freeNode = head;
        head = head->next;
        free(freeNode);
    }
}
```


实现逆置的方法有四种方法，以下将逐一讲解：
# 1. 迭代实现逆置
链表迭代逆置的时候需要借助三个指针，这里我们把三个指针定义为`begin`,`mid`,`end`，这三个并让他们分别指向如图所示。考虑使问题简单化，以四个结点作为示例。

![](img/02_linear_list/34%20迭代法逆置链表.JPG)

`begin`指针指向初始化为空`null`，`mid`指针指向初始化为链表头`head`，`end`指针指向初始化为第二结点。
准备工作做好了现在就可以开始一个结点一个结点的逆置了。

##  第一步：分离首结点
`mid`指针指向的结点（首结点）的指针域要与`begin`相同。
也就是`mid`指针指向的结点的指针域变成与`begin`相同的值`null`。这样子链表第一结点也就是链表头会和其他结点分离出来。
##  第二步：迭代前移
每个指针都向后移动一个结点准备逆置下一个结点，也就是说`begin`指针指向原链表第一结点也就是头结点，`mid`指针指向原链表第二结点，`end`指针指向原链表第三结点。

![](img/02_linear_list/35%20迭代法逆置链表.JPG)

## 第三步：离原结点，接新结点
`mid`指针指向的结点的指针域要与`begin`相同也，就是指向原链表第一结点，原链表的链表头。  
##  第四步：迭代前移
每个指针都向后移动一个结点准备逆置下一个结点。这个时候`begin`指针指向原链表第二结点，`mid`指针指向原链表第三结点，`end`指针指向原链表第四结点。

![](img/02_linear_list/36%20迭代法逆置链表.JPG)

##  第五步：分离原结点，接新结点
`mid`指针指向的结点的指针域要与`begin`相同也就是指向原链表第二结点。
## 第六步：迭代前移
每个指针都向后移动一个结点准备逆置下一个结点。这个时候`begin`指针指向原链表第三结点，`mid`指针指向原链表第四结点，`end`指针指向原链表第四结点的指针域也就是`null`。因为原链表已经没有了第五结点所以第四结点就是链表的表尾。
具体步骤解析如图所示。

![](img/02_linear_list/37%20迭代法逆置链表.JPG)

到了这一步不难发现现在离完成逆置很接近了。接下来我们只需要改变mid指针的指向和head头指针的指向就好了。
## 第七步：分离原结点，接新结点
`mid`指针指向的结点的指针域要与`begin`相同也就是指向原链表第三结点。
##  第八步：变换头指针
这一次我们不需要移动`begin`，`mid`，`end`三个指针了，现在我们只需要改变`head`头指针的指向就好了，`head`头指针的指向改为和`mid`指针相同。

![](img/02_linear_list/38%20迭代法逆置链表.JPG)

## 程序实现
```cpp
// 迭代逆置法，head 为无头结点链表的头指针
LinkedList* IterationReverseLinkedList(LinkedList* head)
{
    // 空表或者只有一个结点的表，逆置等同于不操作
    if (head == NULL || head->next == NULL) {
        return head;
    }
        
    LinkedList* beg = NULL;
    LinkedList* mid = head;
    LinkedList* end = head->next;

    // 一直遍历直到条件退出
    while (true)
    {
        // mid指针指向结点的指针域要与beg指针指向一样
        mid->next = beg;

        // 判断 end 是否为 NULL，如果成立则已经找到原链表尾退出循环
        if (end == NULL) {
            break;
        }

        // beg，mid，end三个指针都向后移动一个结点准备逆置一个结点
        beg = mid;
        mid = end;
        end = end->next;
    }
    // 最后head头指针的指向改为和mid指针相同，
    // 因为最后一步退出循环时，end指针指向尾结点的next，即NULL
    // 他的前一个middle指针指向该尾结点。
    head = mid;
    return head;
}
```

# 2. 头插法逆置链表
头插法在原有链表的基础上，依次将位于链表头部的结点摘下，然后采用从头部插入的方式生成一个新链表，则此链表即为原链表的逆置版。
具体操作如图：

![](img/02_linear_list/39%20头插法法逆置链表.JPG)
## 第一步：摘除首结点
把首结点摘除下来，接到新的链表上来。头指针指向下一个结点。

## 第二步：依次摘除结点
第二步，摘除下一个结点，头插法插入到新链表表头的前面。

![](img/02_linear_list/40%20头插法法逆置链表.JPG)

## 第三步：依次摘除结点
第三步，继续重复上述操作。
## 第四步：直至结点摘除完
- 第四步，直至最后一个结点结束，使用`head`替换`newHead`。

![](img/02_linear_list/41%20头插法法逆置链表.JPG)

## 代码实现
```cpp
LinkedList* ListReverseByTailInsertion(LinkedList* head)
{
    LinkedList* newHead = NULL;
    LinkedList* temp = NULL;     // 用于临时存储结点
    if (head == NULL || head->next == NULL)
        return head;
    while (head != NULL)
    {
        temp = head;
        // 将 temp 从 head 中摘除
        head = head->next;
        // 将 temp 插入到 newHead 的头部
        temp->next = newHead;
        newHead = temp;
    }
    return newHead;
}
```

# 3. 原地逆置链表
原地逆置法和头插法的实现思想类似，唯一的区别在于，头插法是通过建立一个新链表实现的，而原地逆置法则是直接对原链表做修改，从而实现将原链表反转。
在原链表的基础上做修改，需要额外借助 2 个指针（假设分别为 `beg` 和 `end`）。
初始状态下， `beg`指针指向第一个结点，`end` 指针指向 `beg->next`，也就是原链表的第二结点。

![](img/02_linear_list/42%20原地逆置法.JPG)

## 第一步：摘除B结点，头插法插入
将 `end` 所指结点 B 从链表上摘除，然后再添加至当前链表的头部。如图：

![](img/02_linear_list/43%20原地逆置法.JPG)

## 第二步：摘除C结点，头插法插入。
同理，如图：

![](img/02_linear_list/44%20原地逆置法.JPG)

## 第三步：摘除D结点，头插法插入。
最后完成一步，完成链表的逆置。

![](img/02_linear_list/45%20原地逆置法.JPG)

## 代码实现
```c
LinkedList* ReverseInPlace(LinkedList* head)
{
    LinkedList *beg = NULL;
    LinkedList *end = NULL;
    if (head == NULL || head->next == NULL) {
        return head;
    }
        
    beg = head;
    end = head->next;
    while (end != NULL)
    {
        // 将 end 从链表中摘除
        beg->next = end->next;
        // 将 end 移动至链表头
        end->next = head;
        head = end;
        // 调整 end 的指向，另其指向 beg 后的一个结点，为反转下一个结点做准备
        end = beg->next;
        // 以上的这四条操作，每一步都是一个左右倒换，经过四步操作后，完成了原地插入。
    }
    return head;
}
```

# 4. 递归调用逆置链表
递归逆置法和迭代逆置法的思想恰好相反，递归逆置法的实现思想是从链表的尾结点开始，依次向前遍历，遍历过程依次改变各结点的指向，即另其指向前一个结点。  
递归理解起来要比迭代难一点，我们先附上实现代码，然后一一讲解。
## 代码实现
```c
LinkedList* recursion_reverseList(LinkedList* head)
{
    /* 空链表或者只有一个结点的时候直接返回头指针就好了，因为逆置没有意义。
       当然这个也是我们递归的出口，如果找到最后一个结点的时候开始向外层层退出 */
    if (head == NULL || head->next == NULL) {
        return head;
    }
    /* 递归内入，原链表被分成多个子链表，直到最后一个结点。
       最后一个结点也会被分成只有一个链表头的子链表 */
    LinkedList* newHead = recursion_reverseList(head->next);

    /* 在每一层递归中head指针指向的结点的下一个结点的指针域，
    要与head指针指向要相同，
    这也就是在从子链表拆卸一个结点，接到正在逆置的链表后面。
        
    例如 head 指向原链表的第二结点，
    此时第二结点接在原链表的第一结点，经过上面操作以后，
    原链表第二结点会被接在原链表第三结点后面，实现部分逆置。
        
    做完上述操作后把当前head指针指向结点的指针域改为null，
    因为这个是当前我们已经逆置完的结点组成的子链表的链表尾。*/

    head->next->next = head;
    head->next = NULL;
    return newHead;

    /* newHead 指针保存最后一个结点，也就是原链表尾，
    并一直向一层返回，    逆置后我们的原链表尾会变成逆置后的链表头，
    这个就是逆置后的表头，
    一直向上返回能保证链表逆置完还能找到新的链表头 */
    }
}

```
初始状态，创建一个变量，`newHead`，用于返回链表头指针。

![](img/02_linear_list/46%20递归逆置法.JPG)

## 第一步：层层调用
经过四层的递归调用，此时的`NewHead`还没有指向结点，因为在递归内还尚且没有完成。
每经过一次递归调用，都会有一个作用域范围内的`head`指针变量，在图中，为了以示区分，使用不同的颜色作分别。

![](img/02_linear_list/47%20递归逆置法.JPG)

四层递归调用结束，原来的链表被分割成多个独立的子链表。

## 第二步：层层退出
- 退出第四层的时候，`newHead`会得到第四次`if`语句返回的子链表头，也就是原链表的链表尾，图中第四结点。也就是返回了第四个子链表的头指针`head`。
- 三号子链表会跟在四号子链表的后面。也就是说接在逆置后的链表的表头后面，三号子链表的指针域被初始化为`null`，因为它是当前逆置完的链表的链表尾。
- 二号子链表被接在三号子链表后面，二号子链表的指针域被初始化为`null`。

![](img/02_linear_list/48%20递归逆置法.JPG)

- 一号子链表，也就是原链表的第一节，就是链表的头部，被接在了当前逆置链表的尾部，并把指针域初始化为`null`。

递归退出，链表已经完成了逆置。

# 参考链接
[C语言 链表逆置四种方法 超详细_qascetic的博客-CSDN博客_链表逆置](https://blog.csdn.net/m0_52072919/article/details/115566960)


