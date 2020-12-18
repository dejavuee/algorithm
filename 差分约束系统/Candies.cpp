#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
 
using namespace std;
const int INF = 0x3f3f3f3f;
 
struct Edge
{
	int v;
	int w;
	int next;
}edge[150005];
 
int vis[30005],dis[30005],head[30005];
int cnt,n,m;
void spfa(int u)
{
	memset(dis,INF,sizeof(dis));
	memset(vis,0,sizeof(vis));
	stack <int> sta;
	dis[u] = 0;
	vis[u] = 1;
	sta.push(u);
	while(!sta.empty())
	{
		u = sta.top();
		sta.pop();
		vis[u] = 0;
		for(int i = head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			int w = edge[i].w;
			if(dis[v] > dis[u]+w)
			{
				dis[v] = dis[u]+w;
				if(!vis[v])
				{
					vis[v] = 1;
					sta.push(v);
				}
			}
		}
	}
 
}
 
int main(int argc,char **argv)
{
	int u,v,w;
	while(~scanf("%d%d",&n,&m))
	{
		memset(head,-1,sizeof(head));
		cnt = 0;
		while(m--)
		{
			scanf("%d%d%d",&u,&v,&w);
			edge[cnt].v = v;
			edge[cnt].w = w;
			edge[cnt].next = head[u];
			head[u] = cnt++;
		}
		spfa(1);
		printf("%d\n",dis[n]);
	}
	return 0;
}