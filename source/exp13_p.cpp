#include<bits/stdc++.h>
using namespace std;

const int N = 200005,inf = 0x3f3f3f3f,M = 500005;
bool vis[N];
int n,m,num=0;
long long min_cost[N];
int head[N];
vector<int> ve;

struct Edge
{
    int t,w,nxt;
}edge[2*M];

void add(int x,int y,int _w){
    edge[num].t=y;
    edge[num].w=_w;
    edge[num].nxt=head[x];
    head[x]=num++;
}

long long prim()
{
    long long ans=0,tot=1;
    vis[1]=true;
    for(int i=1;i<=n;i++) min_cost[i]=inf;
    for(int i=head[1];i!=-1;i=edge[i].nxt){
        min_cost[edge[i].t]=edge[i].w;
    }
    while(true){
        int v=0;
        //选出一个没有经过且到点集距离最小的顶点
        for(int i=1;i<=n;i++){
            if(!vis[i] && (!v || min_cost[v]>min_cost[i]))
                v=i;
        }
        if(!v) break;
        tot++;
        ans+=min_cost[v];
        vis[v]=true;
        //必定是新加入的点影响了其他未加入的点到这个点集的距离，以这个新点为边点，更新所有未加入点到这个点击的距离
        for(int i=head[v];i!=-1;i=edge[i].nxt){
            int to=edge[i].t,weight=edge[i].w;
            if(!vis[to] && min_cost[to]>weight){
                min_cost[to]=weight;
            }
        }
    }
    if(tot!=n) return -1;
    return ans;
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) ve.push_back(i);
    memset(head,-1,sizeof(head));
    int x,y,w;
    for(int i=0;i<m;i++){
        cin>>x>>y>>w;
        add(x,y,w);
        add(y,x,w);
    }
    cout<<prim()<<endl;
    // system("pause");
    return 0;
}