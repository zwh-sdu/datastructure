#include <iostream>
#include <queue>
#include <cstring>
#define maxsize 100001 //最大顶点数
using namespace std;

int vis[maxsize], dis[maxsize];
int len; //序列长度

struct EdgeNode
{                                 //定义边节点
    int adjvex;                   //该边所指向的顶点的位置
    struct EdgeNode *next; //指向下一条边的指针
    int w;                        //边的权重
};

struct HeadNode //定义表头节点
{
    EdgeNode *firstNode; //指向第一条依附于表头的指针
    int val;             //节点信息
};

struct ALGraph //邻接表
{
    HeadNode list[maxsize];  //创建有maxsize个节点的图
    int point_num, edge_num; //整个图的顶点数和边数
};

class Graph
{
public:
    Graph(int n = 100) //构造函数
    {
        G.point_num = n;
        for (int i = 0; i <= n; i++)
        {
            G.list[i].val = i;
            G.list[i].firstNode = NULL;
        }
    }
    void insert(int u, int v); //增加边
    void erase(int u, int v);  //删除边
    int component_count();     //返回图中有多少连通分量
    void component_print();    //输出连通子图最小节点编号
    void dfs(int start);       //计算从s节点开始的dfs序列长度
    void dfs_count(int start); //为求连通分量使用的的dfs
    void dfs_min(int start);   //输出从s点开始的字典序最小的dfs序列
    int bfs(int start);        //返回从t点开始的bfs序列的长度
    void bfs_min(int start);   //输出从t点开始字典序最小的bfs序列
    void dijkstra(int s);      //输出从s点到t点的最短路径，若是不存在路径则输出-1
    void show();               //输出整个图的邻接表，方便调试
private:
    ALGraph G;
};

void Graph::insert(int u, int v)
{
    //新建两个边节点
    EdgeNode *edge1 = new EdgeNode;
    EdgeNode *edge2 = new EdgeNode;
    edge1->adjvex = v; //edge1边是从u指向v的
    edge2->adjvex = u; //edge2边是从v指向u的
    //因为为了方便后面的按字典序最小输出bfs和dfs序的题目要求
    //要保证链表的有序性，即从小到大按顺序排列，所以插入的时候要放到合适的位置
    EdgeNode *p = G.list[u].firstNode, *pp = NULL;
    if (p == NULL || p->adjvex > v) //如果当前链表为空或者第一个节点的adjvex就比要插入的节点的adjvex大，就直接插入到链表首部
    {
        edge1->next = G.list[u].firstNode;
        G.list[u].firstNode = edge1;
    }
    else
    {

        while (p != NULL && p->adjvex < v)
        {
            //cout<<"****"<<p->adjvex<<endl;
            pp = p;
            p = p->next;
        }
        if (p == NULL) //当前链表中所有的边节点的adjvex都比要插入边的adjvex小，就就插入到链表的最后一个位置
        {
            pp->next = edge1;
            edge1->next = NULL;
        }
        else
        {
            //这时p的adjvex比要插入的adjvex大，pp的adjvex比要插入的adjvex小，插入到p个pp之间即可
            edge1->next = p;
            pp->next = edge1;
        }
    }
    //此时edge1插入完毕，下面用同样的方法插入edge2即可
    p = G.list[v].firstNode;
    pp = NULL;
    if (p == NULL || p->adjvex > u) //如果当前链表为空或者第一个节点的adjvex就比要插入的节点的adjvex大，就直接插入到链表首部
    {
        edge2->next = G.list[v].firstNode;
        G.list[v].firstNode = edge2;
    }
    else
    {
        while (p != NULL && p->adjvex < u)
        {
            pp = p;
            p = p->next;
        }
        if (p == NULL) //当前链表中所有的边节点的adjvex都比要插入边的adjvex小，就就插入到链表的最后一个位置
        {
            pp->next = edge2;
            edge2->next = NULL;
        }
        else
        {
            //这时p的adjvex比要插入的adjvex大，pp的adjvex比要插入的adjvex小，插入到p个pp之间即可
            edge2->next = p;
            pp->next = edge2;
        }
    }
    G.edge_num++;
}

void Graph::erase(int u, int v)
{
    EdgeNode *p = G.list[u].firstNode, *pp = NULL;
    while (p != NULL && p->adjvex != v)
    { //遍历当前链表，找到adjvex=v的边
        pp = p;
        p = p->next;
    }
    if (p == NULL) //如果没找到
    {
        cout << "不存在，删除失败" << endl;
        return;
    }
    //找到了
    if (pp != NULL) //如果要删除的边不是链表的firstnode
    {
        pp->next = p->next;
    }
    else //如果要删除的边正好是这个链表的firstnode
    {
        G.list[u].firstNode = p->next;
    }
    delete p; //释放被删除边所占的空间

    //用同样的方法删除对边
    p = G.list[v].firstNode;
    pp = NULL;
    while (p != NULL && p->adjvex != u)
    { //遍历当前链表，找到adjvex=v的边
        pp = p;
        p = p->next;
    }
    if (p == NULL) //如果没找到
    {
        cout << "不存在，删除失败" << endl;
        return;
    }
    //找到了
    if (pp != NULL) //如果要删除的边不是链表的firstnode
    {
        pp->next = p->next;
    }
    else //如果要删除的边正好是这个链表的firstnode
    {
        G.list[v].firstNode = p->next;
    }
    delete p; //释放被删除边所占的空间
    G.edge_num--;
}

void Graph::show()
{
    cout << "-----------------" << endl;
    for (int i = 1; i <= G.point_num; i++)
    {
        cout << G.list[i].val;
        EdgeNode *p = G.list[i].firstNode;
        while (p != NULL)
        {
            cout << "->" << G.list[p->adjvex].val;
            p = p->next;
        }
        cout << endl;
    }
}

void Graph::dfs_count(int start)
{
    vis[start] = 1;
    EdgeNode *p = G.list[start].firstNode;
    while (p != NULL)
    {
        if (!vis[p->adjvex])
            dfs_count(p->adjvex);
        p = p->next;
    }
}

int Graph::component_count() //返回图中有多少连通分量
{
    int res = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= G.point_num; i++)
    {
        if (!vis[i]) //如果还没有被遍历过，就以这个点为起点再遍历，说明有一个新的连通分量
        {
            dfs_count(i);
            res++;
        }
    }
    return res;
}

void Graph::component_print() //输出连通子图最小节点编号
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= G.point_num; i++)
    {
        if (!vis[i]) //如果还没有被遍历过，就以这个点为起点再遍历，说明有一个新的连通分量
        {
            cout << i << " ";
            dfs_count(i);
        }
    }
    cout << endl;
}

void Graph::dfs(int start) //返回从s节点开始的dfs序列长度
{
    vis[start] = 1; //说明这个点已经被遍历过了，防止后面被重复遍历
    EdgeNode *p = G.list[start].firstNode;
    len++;
    while (p != NULL)
    {
        if (!vis[p->adjvex])
            dfs(p->adjvex);
        p = p->next;
    }
}

void Graph::dfs_min(int start) //输出从s点开始的字典序最小的dfs序列
{
    cout << G.list[start].val << " ";
    vis[start] = 1; //说明这个点已经被遍历过了
    EdgeNode *p = G.list[start].firstNode;
    while (p != NULL)
    {
        if (!vis[p->adjvex])
        {
            dfs_min(p->adjvex);
        }
        p = p->next;
    }
}

int Graph::bfs(int start) //返回从t点开始的bfs序列的长度
{
    memset(vis, 0, sizeof(vis));
    int res = 0;
    queue<int> q; //利用队列实现bfs
    q.push(start);
    int f;
    while (!q.empty())
    {
        f = q.front();
        q.pop();
        res++;
        vis[f] = 1;
        EdgeNode *p = G.list[f].firstNode;
        while (p != NULL)
        {
            if (!vis[p->adjvex])
            {
                vis[p->adjvex] = 1;
                q.push(p->adjvex);
            }
            p = p->next;
        }
    }
    return res;
}

void Graph::bfs_min(int start) //输出从t点开始字典序最小的bfs序列
{
    memset(vis, 0, sizeof(vis));
    queue<int> q; //利用队列实现bfs
    q.push(start);
    int f;
    while (!q.empty())
    {
        f = q.front();
        q.pop();
        cout << G.list[f].val << " ";
        vis[f] = 1;
        EdgeNode *p = G.list[f].firstNode;
        while (p != NULL)
        {
            if (!vis[p->adjvex])
            {
                vis[p->adjvex] = 1;
                q.push(p->adjvex);
            }
            p = p->next;
        }
    }
    cout << endl;
}

void Graph::dijkstra(int start) //输出从s点到t点的最短路径，若是不存在路径则输出-1
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    for (int i = 1; i <= G.point_num; i++)
    {
        dis[i] = maxsize;
        vis[i] = 0;
    }
    dis[start] = 0;
    q.push(make_pair(0, start));
    while (!q.empty())
    {
        int x = q.top().second;
        q.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        EdgeNode *p = G.list[x].firstNode;
        while (p != NULL)
        {
            int nex = p->adjvex;
            if (dis[nex] > dis[x] + 1)
            {
                dis[nex] = dis[x] + 1;
                q.push(make_pair(dis[nex], nex));
            }
            p = p->next;
        }
    }
}

int main()
{
    int n, m, s, t, op, u, v;
    cin >> n >> m >> s >> t;
    Graph g(n);
    while (m--)
    {
        cin >> op >> u >> v;
        if (op == 0)
        {
            g.insert(u, v);
        }
        else if (op == 1)
        {
            g.erase(u, v);
        }
        // g.show();
    }
    //第一行输出图中有多少个连通分量
    cout << g.component_count() << endl;
    //第二行输出所有连通子图中最小点的编号（升序），编号间用空格分隔；
    g.component_print();
    //第三行输出从s点开始的dfs序列长度；
    memset(vis,0,sizeof(vis));
    g.dfs(s);
    cout << len << endl;
    //第四行输出从s点开始的字典序最小的dfs序列；
    memset(vis, 0, sizeof(vis));
    g.dfs_min(s);
    cout << endl;
    //第五行输出从t点开始的bfs序列的长度；
    cout << g.bfs(t) << endl;
    //第六行输出从t点开始字典序最小的bfs序列；
    g.bfs_min(t);
    //第七行输出从s点到t点的最短路径，若是不存在路径则输出-1。
    g.dijkstra(s);
    if (dis[t] == maxsize)
        cout << -1 << endl;
    else
        cout << dis[t] << endl;
    // system("pause");
    return 0;
}
