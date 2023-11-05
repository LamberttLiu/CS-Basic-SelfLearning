
#操作系统 
# [35] 内存的基础知识
内存（memory）可存放数据。程序在执行前，需要先放到内存中才能被CPU处理，因为CPU寄存器中的运行速度，常常是硬盘（外存）的数万倍，直接交流必然会导致系统运行速度变慢，性能下降。因此，需要内存作为中介，缓和了CPU与硬盘之间的速度矛盾。

![](img/03_memory_mngmnt/01%20存储的分层架构.jpg)

那么问题来了，我们已经知道操作系统具备**并发性**了，系统中往往会有多个程序并发执行，也就是说会有多个程序的数据需要同时放到内存中。那么，如何在内存上区分各个程序的数据是具体放在什么地方的呢？这就涉及到了操作系统对内存的管理。比较常见的一种想法，就是给内存的**存储单元编地址**。

![](img/03_memory_mngmnt/02%20内存剖析.jpg)

以我们最常见，在电脑中能拔插的双列直插式（DIMM）内存条为例，逐步放大，内部也有一个一个的“小房间”，每个小房间就是一个“**存储单元**”。内存地址从0开始，**每个地址对应一个存储单元**。如果，计算机“**按字节编址**”，则每个存储单元大小为1字节，即1B，即8个二进制位。如果计算机“**按字编址**”，且字长为16位，则每个存储单元大小为**1个字（word）**，每个字的大小为 16 个二进制位。
## 程序指令角度看内存
我们写的代码要翻译成**CPU能识别的指令**。这些指令会告诉CPU应该去**内存的哪个地址读/写数据**，这个数据应该做什么样的处理。
比如，我们默认让这个进程的相关内容从地址`#0`开始连续存放，指令中的地址参数直接给出了变量 x 的实际存放地址（物理地址，physical address）。但是，如果这个进程不是从地址#0 开始存放的，会影响指令的正常执行吗？可能是会的，比如原来指向`356`的地址，经过了一定的偏移，指向了`14356`，你再去`356`的那个物理地址里面写存数据，肯定会出错。这个时候就可能需要一种方法，对地址进行重定位了。

![](img/03_memory_mngmnt/03%20逻辑地址和物理地址.jpg)

这里需要展开说下，指令的工作原理：原本高级语言的操作，例如C语言程序:`x = i + 1`这段程序，经过编译、链接后生成的k可执行文件中的指令中指明的是逻辑地址（logical address，相对地址），即：相对于进程的起始地址而言的地址。这里的起始地址就是有可能从`14000`。因此，二进制执行文件到执行机中运算前，需要进行先**装入到内存**，只有装载到内存以后才能被CPU执行，这个过程对某些**逻辑地址进行重定位**。这种装入，又叫**装载（Load）**。

## 装载
### 绝对装载
在编译时，如果知道程序将放到内存中的哪个位置，编译程序将产生绝对地址的目标代码。装载程序按照装载模块中的地址，将程序和数据装载内存。例如，如果知道装载模块要从地址为`1400`的地方开始存放，那么在装载的时候，直接将地址直接偏移`1400`就可以了。这种情况比较简单，只适用于**单道程序环境**。
一般而言，程序中使用的绝对地址，可在编译或汇编时给出，也可由程序员直接赋予。通常情况下都是编译或汇编时再转换为绝对地址。
### 可重定位装载
又称**静态重定位**。编译、链接后的装入模块的地址都是从0开始的，指令中使用的地址、数据存放的地址都是相对于起始地址而言的逻辑地址。可根据内存的当前情况，将装入模块装入到内存的适当位置。装载时对地址进行“重定位”，将逻辑地址变换成物理地址（地址变化在**装载时候一次性实现**）。
静态重定位的特点是在一个作业装载内存时，必须分配其要求的全部内存空间，如果没有足够的内存，就不能装载该作业。 
作业一旦进入内存后，在运行期间就不能再移动，也不能再申请内存空间。

### 动态运行时装载（runtime loading）
又称**动态重定位**。编译、链接后的装载模块的地址都是从0开始的。装载程序把装载模块装载内存后，并不会立即把逻辑地址转换为物理地址，而是把**地址转换推迟到程序真正要执行时**才进行。因此装载内存后所有的地址依然是逻辑地址。这种方式需要一个**重定位寄存器**（relocate register）的支持。这也是当前最成熟，并且正在使用的装载方式。重定位寄存器中，记录了程序装载模块的存放的起始地址，在执行的时候，进行地址偏移，对偏移后的地址（物理地址）进行操作。
这部分装载工作，交给装载器（Loader）实现，装载器也是操作系统的重要组成部分。
采用动态重定位时允许程序在内存中发生移动，且可将程序**分配到不连续的存储区**中；在程序运行前只需装载它的部分代码即可投入运行，然后在程序运行期间，根据需要动态申请分配内存；便于程序段的共享，可以向用户提供一个比存储空间大得多的地址空间，这一部分在后面的虚拟内存部分进行详细解释。

![](img/03_memory_mngmnt/04%20程序装载.jpg)
## 从装载角度理解程序运行
从写程序到程序运行，经历了以下复杂的步骤：
- 编译（compile）：由编译程序将用户源代码编译成若干个目标模块（编译就是把高级语言翻译为机器语言）。
- 链接（link）：由链接程序将编译后形成的一组目标模块，以及所需库函数链接在一起，形成一个完整的装载模块。
- 装载（load）：由装载程序将装载模块装载内存运行。

![](img/03_memory_mngmnt/05%20程序执行过程.jpg)

## 链接的三种方式
载装载前需要进行链接，链接也分为三种。
1. 静态链接：在程序运行之前，先将各目标模块及它们所需的库函数连接成一个完整的可执行文件（装载模块），之后不再拆开。
2. 装载时动态链接：将各目标模块装载内存时，边装载边链接的链接方式。
3. 运行时动态链接：在程序执行中需要该目标模块时，才对它进行链接，用不到的不需要进行链接。其优点是便于修改和更新，便于实现对目标模块的共享。这里在后面的静态库和动态库等概念后再详细阐述。

# [36] 内存管理的概念
操作系统作为系统资源的管理者，当然也需要对内存进行管理，要管些什么呢？主要有以下这些：
## 内存管理
1. 负责**内存空间的分配与回收**。
2. 提供某种技术从逻辑上对内存空间进行扩充，这一点体现了操作系统的虚拟性。
3. 提供地址转换功能，负责程序的逻辑地址与物理地址的转换。
4. 提供内存保护功能，保证各进程在各自存储空间内运行，互不干扰。

注意：
>为了使编程更方便，程序员写程序时应该只需要关注**指令、数据**的逻辑地址。
>而逻辑地址到物理地址的转换（这个过程称为地址重定位）应该由操作系统负责，这样就保证了程序员写程序时不需要关注物理内存的实际情况。

## 内存保护
内存保护可采取两种方法：

![](img/03_memory_mngmnt/06%20内存保护.jpg)

方法一：在CPU中设置一对上、下限寄存器，存放进程的上、下限地址。进程的指令要访问某个地址时，CPU检查是否越界。
方法二：采用重定位寄存器（又称基址寄存器，base register）和界地址寄存器（又称限长寄存器，limit register）进行越界检查。重定位寄存器中存放的是进程的起始物理地址，界地址寄存器中存放的是进程的最大逻辑地址。
# [37] 内存覆盖（overlay）与内存交换（swap）
早期的计算机内存很小，比如 IBM 推出的第一台PC机最大只支持 1MB 大小的内存。因此经常会出现内存大小不够的情况。这个时候，人们引入了覆盖技术，用来解决“程序大小超过物理内存总和”的问题。
## 覆盖
覆盖是一种运行大于物理内存大小的程序的技术，**它只保留在任何给定时间需要的指令和数据**。将程序划分为多个模块（段），使并非所有模块都需要同时在内存中。常用的段常驻内存，不常用的段在需要时调入内存。内存中分为一个“固定区”和若干个“覆盖区”。需要常驻内存的段放在“**固定区**”中，调入后就不再调出（除非运行结束），不常用的段放在“**覆盖区**”，需要用到时调入内存，用不到时调出内存。
![](img/03_memory_mngmnt/07%20覆盖.jpg)

覆盖技术必须由程序员声明覆盖结构，并由操作系统完成自动覆盖。但是它也具备一定的缺点，对用户不透明，增加了用户编程负担。所以，覆盖技术只用于早期的操作系统中，现在已成为历史。

![](img/03_memory_mngmnt/08%20覆盖技术的例子.jpg)
## 交换
交换（对换）技术，主要方法是当内存空间紧张时，系统将内存中某些进程暂时换出外存，把外存中某些已具备运行条件的进程换入内存（进程在内存与磁盘间动态调度）。

![](img/03_memory_mngmnt/09%20交换技术.jpg)

在进程管理中提及了**中级调度**（内存调度），就是要决定将哪个处于挂起状态的进程重新调入内存，中级调度就是实现交换技术的方式。
本来，CPU当中由很多进程正在并发运行，如果某一个时刻，就会将某些进程缓存在外存中，插入到挂起队列中，进程相关的PCB会保存在内存中，等到进程资源不紧张的时候，再将进程资源换入内存。PCB就是一个全局的表，记录了进程放在了外存的什么位置，便于换入时候的寻找进程。

暂时换出外存等待的进程状态为挂起状态（挂起态，suspend），挂起态又可以进一步细分为就绪挂起、阻塞挂起两种状态。

![](img/03_memory_mngmnt/11%20七状态进程模型.jpg)

### 应该在外存（磁盘）的什么位置保存被换出的进程？
具有对换功能的操作系统中，通常把磁盘空间分为文件区和对换区两部分。
- **文件区**，主要用于存放文件，主要追求存储空间的利用率，因此对文件区空间的管理采用**离散分配**方式；
- **对换区**，空间只占磁盘空间的小部分，被换出的进程数据就存放在对换区。由于对换的速度直接影响到系统的整体速度，因此对换区空间的管理主要追求换入换出速度，因此通常对换区采用**连续分配**方式（这些需要在文件管理章节后进一步阐述）。   
总之，对换区的I/O速度比文件区的更快。
### 什么时候应该交换？
交换通常在许多进程运行且内存吃紧时进行，而系统负荷降低就暂停。例如：在发现许多进程运行时经常发生缺页（在后序会详细解释），就说明内存紧张，此时可以换出一些进程；如果缺页率明显下降，就可以暂停换出。
### 应该换出哪些进程？
- 可优先换出阻塞进程；
- 可换出优先级低的进程；
- 为了防止优先级低的进程在被调入内存后很快又被换出，造成进程饥饿（Starvation）现象，有的系统还会考虑进程在内存的驻留时间。（注意，PCB会常驻内存，不会被换出外存）。

# [38] 连续分配管理方式
## 单一连续分配
在单一连续分配方式中，内存被分为**系统区**和**用户区**。系统区通常位于内存的低地址部分，用于存放操作系统相关数据；用户区用于存放用户进程相关数据。内存中只能有一道用户程序，用户程序独占整个用户区空间。这是早期的内存管理使用情况。
### 优缺点
优点：
- 实现简单；无外部碎片；
- 可以采用覆盖技术扩充内存；
- 不一定需要采取内存保护（例如早期的PC操作系统：MS-DOS）。
缺点：
- 只能用于单用户、单任务的操作系统中；
- 有内部碎片；
- 存储器利用率极低。
其中碎片（memory fragmentation）是指分配给某进程的内存区域中，如果有些部分没有用上，就是“内部碎片”。
## 固定分区分配
20世纪60年代出现了支持多道程序的系统，为了能在内存中装载多道程序，且这些程序之间又不会相互干扰，于是将整个用户空间划分为**若干个固定大小的分区**，在每个分区中只装载一道作业，这样就形成了最早的、最简单的一种可运行多道程序的内存管理方式。
- 当分区大小相等时：缺乏灵活性，但是很适合用于用一台计算机控制多个相同对象的场合（比如：钢铁厂有n个相同的炼钢炉，就可把内存分为n个大小相等的区域存放n个炼钢炉控制程序）
- 当分区大小不等时：增加了灵活性，可以满足不同大小的进程需求。根据常在系统中运行的作业大小情况进行划分（比如：划分多个小分区、适量中等分区、少量大分区）。

![](img/03_memory_mngmnt/12%20连续分配内存.jpg)

在这个场景下，操作系统需要建立一个数据结构——**分区说明表**，来实现各个分区的分配与回收。每个表项对应一个分区，通常按分区大小排列。每个表项包括对应分区的大小、起始地址、状态（是否已分配）。
当某用户程序要装载内存时，由操作系统内核程序根据用户程序大小检索该表，从中找到一个能满足大小的、未分配的分区，将之分配给该程序，然后修改状态为“已分配”。
### 优缺点
优点：
实现简单，无外部碎片。
缺点：
- 当用户程序太大时，可能所有的分区都不能满足需求，此时不得不采用覆盖技术来解决，但这又会降低性能；
- 会产生内部碎片，内存利用率低。
## 动态分区分配
动态分区分配又称为**可变分区分配**。这种分配方式不会预先划分内存分区，而是在进程装载内存时，根据进程的大小动态地建立分区，并使分区的大小正好适合进程的需要。因此系统分区的大小和数目是可变的。（例如，假设某计算机内存大小为64MB，系统区8MB，用户区共56MB，在进程A运行是占据一段，B运行时占据邻接一段...）但是这样会产生一些空缺现象，因此需要探讨如何解决这种问题。

![](img/03_memory_mngmnt/13%20动态分区内存.jpg)
## 系统要用什么样的数据结构记录内存的使用情况？
- 空闲分区表：每个空闲分区对应一个表项。表项中包含分区号、分区大小、分区起始地址等信息。
- 空闲分区链：每个分区的起始部分和末尾部分分别设置前向指针和后向指针。起始部分处还可记录分区大小等信息。

![](img/03_memory_mngmnt/14%20空闲分区表.jpg)

## 当很多个空闲分区都能满足需求时，应该选择哪个分区进行分配？
问题又以下几个选项: 
1. 应该用最大的分区进行分配;
2. 还是用最小的分区进行分配;
3. 用地址最低的部分进行分配。

当一个新作业装载内存时，须按照一定的**动态分区分配算法**，从空闲分区表（或空闲分区链）中选出一个分区分配给该作业。由于分配算法算法对系统性能有很大的影响，因此人们对它进行了广泛的研究。具体算法在下一个部分详细解释。
## 如何进行分区的分配与回收操作？ 
假设系统采用的数据结构是“空闲分区表” 如何分配？
- 情况一：回收区的前面或者后面有一个相邻的空闲分区，那么，将两个相邻的空闲分区合并为一个。
- 情况二：回收区的前、后各有一个相邻的空闲分区，三个相邻的空闲分区合并为一个。
- 情况三：回收区的前、后都没有相邻的空闲分区，新增一个表项。

动态分区分配没有内部碎片，但是有外部碎片。注意区分：**内部碎片**，当进程被分配给内存块时，如果该进程小于请求的内存，则会在分配的内存块中创建一个可用空间。然后，分配的内存和请求的内存之间的差异称为**内部碎片**。**外部碎片**，当进程加载或从内存中删除时，将创建一个可用空间。此可用空间在内存中创建一个空白空间暂时未使用，称为**外部碎片**。

![](img/03_memory_mngmnt/15%20内部碎片.jpg)
![](img/03_memory_mngmnt/16%20外部碎片.jpg)

如果内存中空闲空间的总和本来可以满足某进程的要求，但由于进程需要的是一整块连续的内存空间，因此这些“碎片”不能满足进程的需求。可以通过紧凑（压缩，Compaction）技术来解决外部碎片。

![](img/03_memory_mngmnt/17%20内存压缩.jpg)

# [39] 动态分区分配算法
结合上述内存分配方式，动态分区分配算法算是目前最优的一种方式，较少有内存碎片，并且配合内存压缩技术，能优化内存使用效率。那么，在动态分区分配方式中，当很多个空闲分区都能满足需求时，应该选择哪个分区进行分配？
## 1. 首次适应算法
首次适应算法（First Fit Method），每次都从低地址开始查找，找到第一个能满足大小的空闲分区。 

![](img/03_memory_mngmnt/18%20首次适应算法.jpg)
![](img/03_memory_mngmnt/19%20首次适应算法.jpg)
![](img/03_memory_mngmnt/20%20首次适应算法.jpg)

空闲分区以地址递增的次序排列。每次分配内存时顺序查找空闲分区链（或空闲分区表），找到大小能满足要求的第一个空闲分区。

程序实现：
```c
#include <stdio.h>

void implimentFirstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    // This will store the block id of the allocated block to a process
    int allocate[processes];
    int occupied[blocks];

    // initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for(int i = 0; i < processes; i++)
	{
		allocate[i] = -1;
	}
	
	for(int i = 0; i < blocks; i++){
        occupied[i] = 0;
    }
	
    // take each process one by one and find
    // first block that can accomodate it
    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < blocks; j++) 
        { 
        if (!occupied[j] && blockSize[j] >= processSize[i])
            {
                // allocate block j to p[i] process
                allocate[i] = j;
                occupied[j] = 1;
 
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocate[i] != -1)
            printf("%d\n",allocate[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

void main()
{
    int blockSize[] = {30, 5, 10};
    int processSize[] = {10, 6, 9};
    int m = sizeof(blockSize)/sizeof(blockSize[0]);
    int n = sizeof(processSize)/sizeof(processSize[0]);
    
    implimentFirstFit(blockSize, m, processSize, n);
}
```

输出：
```txt
Process No.	Process Size	Block no.
1 		10 		1
2 		6 		3
3 		9 		Not Allocated
```
## 2. 最佳适应算法
最佳适应算法（Best Fit Method）的算法思想，由于动态分区分配是一种连续分配方式，为各进程分配的空间必须是连续的一整片区域。因此为了保证当“大进程”到来时能有连续的大片空间，可以尽可能多地留下大片的空闲区，即，优先使用更小的空闲区。 

![](img/03_memory_mngmnt/21%20最佳适应算法.jpg)
![](img/03_memory_mngmnt/22%20最佳适应算法.jpg)
![](img/03_memory_mngmnt/23%20最佳适应算法.jpg)

空闲分区按**容量递增**次序链接。每次分配内存时顺序查找空闲分区链（或空闲分区表），找到大小能满足要求的第一个空闲分区。
程序实现：
```c
#include <stdio.h>

void implimentBestFit(int blockSize[], int blocks, int processSize[], int proccesses)
{
    // This will store the block id of the allocated block to a process
    int allocation[proccesses];
    int occupied[blocks];
    
    // initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for(int i = 0; i < proccesses; i++){
        allocation[i] = -1;
    }
    
    for(int i = 0; i < blocks; i++){
        occupied[i] = 0;
    }
 
    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i = 0; i < proccesses; i++)
    {
        
        int indexPlaced = -1;
        for (int j = 0; j < blocks; j++) { 
            if (blockSize[j] >= processSize[i] && !occupied[j])
            {
                // place it at the first block fit to accomodate process
                if (indexPlaced == -1)
                    indexPlaced = j;
                    
                // if any future block is smalller than the current block where
                // process is placed, change the block and thus indexPlaced
		// this reduces the wastage thus best fit
                else if (blockSize[j] < blockSize[indexPlaced])
                    indexPlaced = j;
            }
        }
 
        // If we were successfully able to find block for the process
        if (indexPlaced != -1)
        {
            // allocate this block j to process p[i]
            allocation[i] = indexPlaced;
            
            // make the status of the block as occupied
            occupied[indexPlaced] = 1;
        }
    }
 
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < proccesses; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
 
// Driver code
int main()
{
    int blockSize[] = {100, 50, 30, 120, 35};
    int processSize[] = {40, 10, 30, 60};
    int blocks = sizeof(blockSize)/sizeof(blockSize[0]);
    int proccesses = sizeof(processSize)/sizeof(processSize[0]);
 
    implimentBestFit(blockSize, blocks, processSize, proccesses);
 
    return 0 ;
}
```

输出：
```txt
Process No.	Process Size	Block no.
1 		10 		2
2 		30 		1
3 		60 		4
4 		30 		4
```
## 3. 最坏适应算法
最大适应算法（Largest Fit Method）算法思想：为了解决最佳适应算法的问题，即留下太多难以利用的小碎片，可以在每次分配时优先使用最大的连续空闲区，这样分配后剩余的空闲区就不会太小，更方便使用。 

![](img/03_memory_mngmnt/24%20最坏适应算法.jpg)
![](img/03_memory_mngmnt/25%20最坏适应算法.jpg)
![](img/03_memory_mngmnt/26%20最坏适应算法.jpg)

空闲分区按**容量递减**次序链接。每次分配内存时顺序查找空闲分区链（或空闲分区表），找到大小能满足要求的第一个空闲分区。
```c
#include <stdio.h>

void implimentWorstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    // This will store the block id of the allocated block to a process
    int allocation[processes];
    int occupied[blocks];
    
    // initially assigning -1 to all allocation indexes
    // means nothing is allocated currently
    for(int i = 0; i < processes; i++){
        allocation[i] = -1;
    }
    
    for(int i = 0; i < blocks; i++){
        occupied[i] = 0;
    }
 
    // pick each process and find suitable blocks
    // according to its size ad assign to it
    for (int i=0; i < processes; i++)
    {
	int indexPlaced = -1;
	for(int j = 0; j < blocks; j++)
	{
	    // if not occupied and block size is large enough
	    if(blockSize[j] >= processSize[i] && !occupied[j])
            {
                // place it at the first block fit to accomodate process
                if (indexPlaced == -1)
                    indexPlaced = j;
                    
                // if any future block is larger than the current block where
                // process is placed, change the block and thus indexPlaced
                else if (blockSize[indexPlaced] < blockSize[j])
                    indexPlaced = j;
            }
        }
 
        // If we were successfully able to find block for the process
        if (indexPlaced != -1)
        {
            // allocate this block j to process p[i]
            allocation[i] = indexPlaced;
            
            // make the status of the block as occupied
            occupied[indexPlaced] = 1;
 
            // Reduce available memory for the block
            blockSize[indexPlaced] -= processSize[i];
        }
    }
 
    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d \t\t\t %d \t\t\t", i+1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n",allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}
 
// Driver code
int main()
{
    int blockSize[] = {100, 50, 30, 120, 35};
    int processSize[] = {40, 10, 30, 60};
    int blocks = sizeof(blockSize)/sizeof(blockSize[0]);
    int processes = sizeof(processSize)/sizeof(processSize[0]);
 
    implimentWorstFit(blockSize, blocks, processSize, processes);
 
    return 0;
}
```

输出：
```txt
Process No.	Process Size	Block no.
1 		40 		4
2 		10 		1
3 		30 		2
4 		60 		Not Allocated
```

缺点：每次都选最大的分区进行分配，虽然可以让分配后留下的空闲区更大，更可用，但是这种方式会导致较大的连续空闲区被迅速用完。如果之后有“大进程”到达，就没有内存分区可用了。
## 4. 邻近适应算法
邻近适应算法(Next Fit Method)算法思想：首次适应算法每次都从链头开始查找的。这可能会导致低地址部分出现很多小的空闲 分区，而每次分配查找时，都要经过这些分区，因此也增加了查找的开销。如果每次都从上次查 找结束的位置开始检索，就能解决上述问题。    

![](img/03_memory_mngmnt/27%20邻接适应算法.jpg)

如何实现：空闲分区以地址递增的顺序排列（可排成一个循环链表）。每次分配内存时从上次查找结束的位置开始查找空闲分区链（或空闲分区表），找到大小能满足要求的第一个空闲分区。
伪代码：
1. 输入内存块的数量。
2. 输入每个内存块的大小。
3. 输入进程数及其大小。
4. 首先选择每个进程，检查是否可以将其分配给当前内存块。
5. 如果步骤 4 中的条件为真，则为进程分配所需的内存，并从停止搜索的内存块中检查下一个进程，而不是从开始检查。
6. 如果当前内存大小较小，则继续检查下一个块。
7. 停止。
## 5. 对比
首次适应算法每次都要从头查找，每次都需要检索低地址的小分区。 但是这种规则也决定了当低地址部分有更小的分区可以满足需求时，会更有可能用到低地址部分的小分区，也会更有可能把高地址部分的大分区保留下来（最佳适应算法的优点）邻近适应算法的规则可能会导致无论低地址、高地址部分的空闲分区都有相同的概率被使用，也就导致了高地址部分的大分区更可能被使用，划分为小分区，最后导致无大分区可用（最大适应算法的缺点）。    
综合来看，四种算法中，**首次适应算法**的效果反而更好。



