#include <cstdio>
#include <vector>
#include <queue>
#define INF 0x7f7f7f7f
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int m,n;
int need[25],work[25],check[25],vis[25],dis[25];
vector <pair<int,int> > g[25];
void spfa(int u){
	queue <int> q;
	vis[u] = 1;
	check[u] = 1;
	q.push(u);
	while(!q.empty()){
		u = q.front();
		vis[u] = 0;
		q.pop();
		int i;
		for(i = 0; i < g[u].size(); i++){
			int v = g[u][i].first;
			int w = g[u][i].second;
			if(dis[v] < dis[u]+w){
				dis[v] = dis[u] +w;
				if(!vis[v]){
					vis[v] = 1;
					check[v]++;
					if(check[v]>24)
					{
						dis[24]=-1;
						return;
					}
					q.push(v);			
				}
			}
		}
	}
}


void add(int u,int v,int w){
	g[u].push_back(make_pair(v,w));
}

int main() {
	scanf("%d",&m);
	while(m--){
	for(int i=0;i<25;i++)
		g[i].clear();
	for(int i=0;i<25;i++){
		work[i]=0;
	}
	for(int i=1;i<25;i++){
		scanf("%d",&need[i]);
	}
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int t;
		scanf("%d",&t);
		work[t+1]++;
	}
	int num,result=-1;
	for(num=0;num<=n;num++){
		for(int i=0;i<25;i++)
			g[i].clear();
		for(int i=0;i<25;i++){
			vis[i]=0;
			check[i]=0;
			dis[i]=-INF;
		}
		for(int t=1;t<=24;t++){
			add(t-1,t,0);
			add(t,t-1,-work[t]);
			if(t<8)
				add(16+t,t,need[t]-num);
			else add(t-8,t,need[t]);
		}
		add(0,24,num);
		dis[0]=0;
		spfa(0);
		result = (dis[24]==num);
		if(result){
			printf("%d\n",num);
			break;
		}
		else continue;	
	}
	if(result ==0)
		printf("No Solution\n");
}
	return 0;
}