#数据结构  #C 
# [69] 图的基本操作

图的基本操作如下：
```c
// 判断图 G 是否存在边 <x,y> 或 (x, y) 
Adjacent(G, x, y);

// 列出图 G 中与结点 x 邻接的边
Neighbors(G, x);

// 在图 G 中插入顶点 x 
InsertVertex(G, x);

// 从图 G 中删除顶点 x
DeleteVertex(G,x);

// 若无向边(x, y)或有向边不存在，则向图G中添加该边。 
AddEdge(G, x, y);

// 若无向边(x, y)或有向边存在，则从图G中删除该边。 
RemoveEdge(G, x, y);

// 求图G中顶点x的第一个邻接点，若有则返回顶点号。若x没有邻接点 或图中不存在x，则返回-1。 
FirstNeighbor(G, x);

// 假设图G中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一 个邻接点的顶点号，若y是x的最后一个邻接点，则返回-1。 
NextNeighbor(G, x, y);

// 获取图G中边(x, y)或对应的权值。 
Get_edge_value(G, x, y);

// 设置图G中边(x, y)或对应的权值为v。
Set_edge_value(G, x, y, v);
```

本节以邻接矩阵和邻接表两种存储结构，来分析各类操作的实际复杂度。

# [70] 图的广度遍历优先
从树的角度，以层序遍历入手，了解图的广度优先遍历。
- 树：不存在“回路”，搜索相邻的结点时，不可能搜到已经访问过的结点。
- 图：搜索相邻的顶点时，有可能搜到已经访问过的顶点。

图的⼴度优先遍历（Breadth-First-Search, BFS）
要点： 
1. 找到与⼀个顶点相邻的所有顶点；
2. 标记哪些顶点被访问过；
3. 需要⼀个辅助队列。

函数实现：
- `FirstNeighbor(G,x);`
	- 求图`G`中顶点x的第⼀个邻接点，若有则返回顶点号。 若x没有邻接点或图中不存在x，则返回-1。 
- `NextNeighbor(G, x, y);`
	- 假设图`G`中顶点`y`是顶点`x`的⼀个邻接点，返回除`y`之外顶点`x`的下⼀个邻接点的顶点号，若`y`是`x`的最后⼀个邻接点，则返回-1。

```c
bool visited[MaxVertexNum];   // 访问标记数组

// 对图G进行广度优先遍历
void BFSTraverse(Graph G)
{
    // 初始化标记数组
    for (int i = 0; i < G.vexNum; i++) {
        visited[i] = false;
    }

    Init(Q);
    // 从起始点开始遍历
    for (int i = 0; i < G.vexNum; i++)
    {
        if (!visited[i]) {  // 对每一个连通分量调用一次BFS
            BFS(G, i);      // 防止出现隔离的顶点
        }
    }
}

// 广度优先遍历
void BFS(Graph G, int v)
{
    visit(v);   // 从顶点出发开始遍历
    visited[v] = true;      // v已经被访问到
    EnQueue(Q, v);          // 将v压入队列Q
    while (!IsEmptyQue(Q)) {
        DeQueue(Q, v);      // v出队列Q
        
        // 检测v的所有邻接顶点
        for (w = FirstNeighbor(G, v) ;w >= 0; w = NextNeighbor(G, v, w))
        {
            if (!visited[w])    // w为未曾访问的顶点
            {
                visit(w);       // 访问
                visited[w] = true;
                EnQueue(Q, w);  // 再将w顶点压入队列中
            }
        }
    }
}
```
# [71] 图的深度遍历优先
从树的角度，以先根遍历入手，了解图的广度优先遍历。树的遍历时采用递归的方式实现：

```c
bool visited[MaxVertexNum];   // 访问标记数组

// 对图G进行深度优先遍历
void DFSTraverse(Graph G)
{
    // 初始化标记数组
    for (int i = 0; i < G.vexNum; i++) {
        visited[i] = false;
    }
    // 从起始点开始遍历
    for (int i = 0; i < G.vexNum; i++)
    {
        if (!visited[i]) {  // 对每一个连通分量调用一次DFS
            DFS(G, i);      // 防止出现隔离的顶点
        }
    }
}

void DFS(Graph G, int v)
{
    visit(v);               // 访问顶点v
    visited[v] = true;      // 更新标记数组

    // 检测v的下一个邻接顶点
    for (w = FirstNeighbor(G, v) ;w >= 0; w = NextNeighbor(G, v, w))
    {
        if (!visited[w])
        {
            DFS(G,w);
        }
    }
}
```

# [72] 最小生成树
连通图的生成树是包含图中全部顶点的一个极小连通子图。
若图中顶点数为`n`，则它的生成树含有 `n - 1` 条边。对生成树而言，若砍去它的一条边，则会变成非连通图，若加上一条边则会形成一个回路。

对于⼀个带权连通⽆向图 $G = (V, E)$，⽣成树不同，每棵树的权（即树中所有边上的权值之和）也可能不同。  
设 $R$ 为 $G$ 的所有⽣成树的集合，若 $T$ 为 $R$ 中边的权值之和最⼩的⽣成树，则 $T$ 称为 $G$ 的最⼩⽣成树（Minimum-Spanning-Tree, MST），又叫最小代价树 。

- 最小生成树可能有多个，但边的权值之和总是唯⼀且最⼩的，
- 最小生成树的边数 = 顶点数 - 1。砍掉⼀条则不连通，增加⼀条边则会出现回路，
- 如果⼀个连通图本身就是⼀棵树，则其最⼩⽣成树就是它本身，
- 只有连通图才有⽣成树，非连通图只有⽣成森林。

## Prim算法
从某⼀个顶点开始构建⽣成树；
每次将代价最⼩的新顶点纳入生成树，直到所有顶点都纳入为止。

## Kruskal 算法
每次选择⼀条权值最小的边，使这条边的两头连通（原本已经连通的就不选）。