#include <cstdio>
#include <vector> 
#define MAXN 100005
using namespace std;
int vis[MAXN], left[MAXN], right[MAXN], arrayTree[MAXN], fork[MAXN];
vector<vector<int> > edge(MAXN);
int N, M;
int tot;

void DFS(int x) {
	int r;
	left[x] = tot;
	int j;
	for (j = 0; j < edge[x].size(); j++) {
		tot++;
		DFS(edge[x][j]);
	}
	right[x] = tot;
}

int lowbit(int x) {
	return (x & -x);
}
void init() {
	int i;
	for (i = 1; i <= N; i++) {
		arrayTree[i] += 1;
		int j = i + lowbit(i);
		if (j <= N)
			arrayTree[j] += arrayTree[i];
	}
}

void addt(int x, int k) {
	while (x <= N) {
		arrayTree[x] = arrayTree[x] + k;
		x = x + lowbit(x);
	}
}

int getsum(int x) {
	int ans = 0;
	while (x >=1) {
		ans = ans + arrayTree[x];
		x = x - lowbit(x);
	}
	return ans;
}

int main() {
	//freopen("C:\\Users\\Angie\\workspace\\C++\\algorithm\\apple.txt", "r", stdin);
	scanf("%d", &N);
	int i, x, y;
	for (i = 1; i <= N; i++)
		fork[i] = 1;
	/*初始化邻接矩阵*/
	for (i = 1; i < N; i++) {
		scanf("%d %d", &x, &y);
		edge[x].push_back(y);
	}
	tot = 1;
	DFS(1);
	init();
	scanf("%d", &M);
	for (i = 1; i <= M; i++) {
		char c1[2];
		int c2;
		scanf("%s%d",&c1,&c2);
		if (c1[0] == 'C') {
			x = c2;
			if (fork[x] == 0)
				addt(left[x], 1);
			else addt(left[x], -1);
			fork[x] = !fork[x];
		}
		else {
			x = c2;
			printf("%d\n", getsum(right[x]) - getsum(left[x]-1));
		}
	}
	return 0;
}