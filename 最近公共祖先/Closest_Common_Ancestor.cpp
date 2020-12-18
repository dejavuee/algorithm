#include <cstdio>
#include <vector>
#include <algorithm>
#include <map> 
#include <cstring>
using namespace std;
/*
5
5:(3) 1 4 2
1:(0)
4:(0)
2:(1) 3
3:(0)
6
(1 5) (1 4) (4 2)
(2 3)
(1 3) (4 3)
*/
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

const int maxn = 905;
vector <int> g[maxn];
map <int,int> result;
int n,m,f[maxn][15],dep[maxn],root,ind[maxn];

void dfs(int u,int p,int d){
	f[u][0] = p;
	dep[u] = d;
	int i;
	for(i=0;i<g[u].size();i++){
		int v = g[u][i];
		if(v == p) continue;
		dfs(v,u,d+1);
	}
}

bool cmp (pair <int,int> a,pair <int,int> b){
	return a.second < b.second;
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
	for(int i=log2(dep[x]-dep[y]);i>=0;i--){
		if((1<<i)<=dep[x]-dep[y])
			x = f[x][i];
	}
	if(x == y)
		return x;
	else{
		for(int i=log2(dep[x]);i>=0;i--){
			if(f[x][i]!=f[y][i]){
				x = f[x][i];
				y = f[y][i];
			}
		}
		return f[x][0];	
	}
}

int main() {
	while(scanf("%d",&n)!=EOF){
	result.clear();
	memset(f,0,sizeof(g));
	memset(dep,0,sizeof(dep));
    memset(ind,0,sizeof(ind));
	for(int i=1;i<=n;i++)
        g[i].clear();
	
	int i;
	for(i=0;i<n;i++){
		int u,num;
		scanf("%d:(%d)",&u,&num);
		while(num--){
			int v;
			scanf("%d",&v);
			g[u].push_back(v);
			g[v].push_back(u);
			ind[v]++;
		}
	}
	for(i=1;i<=n;i++){
		if(ind[i]==0)
		{
			root = i;
			break;
		}			
	}
	dfs(root,root,0);
	for(int i=1;i<12;i++)
		for(int u = 1;u<=n;u++)
			f[u][i] = f[f[u][i-1]][i-1];	
	scanf("%d",&m);	
	while(m--){
		int a,b;
		char c =getchar();
		while(c !='(') c = getchar();
		scanf("%d %d",&a,&b);
		while(c !=')') c = getchar();
		int r = lca(a,b);
		result[r]++;		
	}
	for(map<int,int> ::iterator it = result.begin();it!=result.end();it++){
		printf("%d:%d\n",it->first,it->second);
	}
}
	return 0;
}