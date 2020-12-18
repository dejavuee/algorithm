#include <cstdio>
#include <vector>
#include <algorithm>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
 
const int maxn = 100000;
vector <pair<int,int> > g[2*maxn];
int n,m,f[maxn][20],dep[maxn],dis[maxn];
void dfs(int u,int p,int d){
	f[u][0] = p;
	dep[u] = d;
	int i;
	for(i=0;i<g[u].size();i++){
		int v = g[u][i].first;
		if(v == p) continue;
		dis[v] = dis[u] + g[u][i].second;
		dfs(v,u,d+1);
	}
}

int log2(int x){
	int sum =0;
	while(x>>=1){
		sum++;
	}
	return sum+1;
}

int lca(int x,int y){
	if(dep[x]<dep[y]) swap(x,y);
	int d=log2(n)+1;
	for(int i=0;i <= d;i++){
		if((1<<i) & (dep[x]-dep[y]))
			x = f[x][i];
	}
	if(x == y)
		return x;
	else{
		for(int i=d;i>=0;i--){
			if(f[x][i]!=f[y][i]){
				x = f[x][i];
				y = f[y][i];
			}
		}
		return f[x][0];	
	}
}


int main() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		int u,v,w;
		char op[5];
		scanf("%d%d%d%s",&u,&v,&w,op);
		g[u].push_back(make_pair(v,w));
		g[v].push_back(make_pair(u,w));
	}
	dis[1]=0;
	dfs(1,1,0);
	for(int i=1;i<20;i++)
		for(int u = 1;u<=n;u++)
			f[u][i] = f[f[u][i-1]][i-1];	
	int k;
	scanf("%d",&k);	
	while(k--){
		int a,b;
		scanf("%d %d",&a,&b);
		int r = lca(a,b);
		int distance;
		distance = dis[a]+dis[b]-2*dis[r];
		printf("%d\n",distance);		
	}
	return 0;
}