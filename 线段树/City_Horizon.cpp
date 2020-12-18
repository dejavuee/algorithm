#include <cstdio>
#include <algorithm>
#define maxn 40005
using namespace std; 
typedef long long ll;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int N,num;//num是坐标数量 
int tree[maxn*8];
struct City{
	int left;
	int right;
	int h;
}city[maxn];
int pos[maxn*2];

bool cmp(City a,City b){
	return a.h <b.h;
}


void update_tree(int node,int start,int end,int l,int r,int v){
	if(start==l && end == r)
	{
		tree[node] = v;
		return;
	}
	if(tree[node] >= 0 && start+1 < end){
		tree[2*node+1] = tree[node];
		tree[2*node+2] = tree[node];
		tree[node] = -1;
	}
	int mid = (start+end)/2;
	if(r <= mid)
		update_tree(2*node+1,start,mid,l,r,v);
	else if(l >= mid)
		update_tree(2*node+2,mid,end,l,r,v);
	else
	{
		update_tree(2*node+1,start,mid,l,mid,v);
		update_tree(2*node+2,mid,end,mid,r,v);
	}
}

ll query_tree(int node,int start,int end){
	if(tree[node] >=0)
		return (ll)tree[node] * (ll)(pos[end]-pos[start]);
		else
		{
			int mid = (start+end)/2;
			ll sum_left = query_tree(2*node+1,start,mid);
			ll sum_right = query_tree(2*node+2,mid,end);
			return (sum_left+sum_right);
		}
}

int binary_search(int x){
	int l=0,r=num-1;
	while(l<=r){
		int mid = (l+r)/2;
		if(pos[mid] > x)
			r = mid-1;
		else if(pos[mid] < x)
			l = mid+1;
		else return mid;
	}
}

int main(int argc, char *argv[]) {
	scanf("%d",&N);
	for(int i=0;i<(maxn<<2);i++){
		tree[i] = 0;
	}
	for(int i=0;i<N;i++){
		scanf("%d %d %d",&city[i].left,&city[i].right,&city[i].h);
		pos[i*2] = city[i].left;
		pos[i*2+1] = city[i].right;
	}
	sort(pos,pos+2*N);
	num = 1;
	for(int i=1;i<2*N;i++){
		if(pos[i]==pos[i-1])	continue;
		else pos[num++] = pos[i]; 
	}
	sort(city,city+N,cmp);
	for(int i=0;i<N;i++){
		int leftpos = binary_search(city[i].left);
		int rightpos = binary_search(city[i].right);
		update_tree(0,0,num-1,leftpos,rightpos,city[i].h);
	}
	ll result = query_tree(0,0,num-1);
	printf("%lld\n",result);
	return 0;
}