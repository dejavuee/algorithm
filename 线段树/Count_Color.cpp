#include <cstdio>
#define maxn 100005

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int L,T,O;
int tree[maxn<<2],lazy[maxn<<2];
int color[32]={0,1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824};
void build_tree(int node,int start,int end){
	lazy[node]=1;
	if(start == end)
		tree[node] = 1;
	else{
	int mid = (start+end)/2;
	int left_node = 2*node+1;
	int right_node = 2*node+2;
	build_tree(left_node,start,mid);
	build_tree(right_node,mid+1,end);
	tree[node] = (tree[left_node] | tree[right_node]);
	}
}

void update_tree(int node,int start,int end,int l,int r,int v){
	if(start==l && end == r)
	{
		tree[node] = v;
		lazy[node] = v;
		return; 
	}
	if(lazy[node]!=0){
		tree[2*node+1] = lazy[node];
		tree[2*node+2] = lazy[node];
		lazy[2*node+1] = lazy[node];
		lazy[2*node+2] = lazy[node];
		lazy[node] = 0;
	}
		int mid = (start+end)/2;
		if(r <= mid)
			update_tree(2*node+1,start,mid,l,r,v);
		else if(l > mid)
			update_tree(2*node+2,mid+1,end,l,r,v);
		else
		{
			update_tree(2*node+1,start,mid,l,mid,v);
			update_tree(2*node+2,mid+1,end,mid+1,r,v);
		}
		int left_node = 2*node+1;
		int right_node = 2*node+2;
		tree[node] = tree[left_node] | tree[right_node];
}

int query_tree(int node,int start,int end,int L,int R){
	if(L==start && R==end)
		return tree[node];
	if(lazy[node]!=0){
		tree[2*node+1] = lazy[node];
		tree[2*node+2] = lazy[node];
		lazy[2*node+1] = lazy[node];
		lazy[2*node+2] = lazy[node];
		lazy[node] = 0;
	}
		int mid = (start+end)/2;
		if(R <= mid)
			query_tree(2*node+1,start,mid,L,R);
		else if(L > mid)
			query_tree(2*node+2,mid+1,end,L,R);
		else
		{
			int sum_left = query_tree(2*node+1,start,mid,L,mid);
			int sum_right = query_tree(2*node+2,mid+1,end,mid+1,R);
			return sum_left|sum_right;
		}
		int left_node = 2*node+1;
		int right_node = 2*node+2;
		tree[node] = (tree[left_node] | tree[right_node]);	 
}

int cal(int r){
	int ans=0;
	while(r>0){
		ans++;
		r -= (r & (-r));
	}
	return ans;
}

int main(int argc, char *argv[]) {
	scanf("%d %d %d",&L,&T,&O);
	for(int i=0;i<(maxn<<2);i++){
		tree[i] = 0;
	}
	build_tree(0,0,L-1);
	for(int i=0;i<O;i++){
		char op;
		getchar();
		scanf("%c",&op);
		int a,b,v;
		if(op=='C')
		{
			scanf("%d %d %d",&a,&b,&v);
			if(a <=b)
				update_tree(0,0,L-1,a-1,b-1,color[v]);
			else update_tree(0,0,L-1,b-1,a-1,color[v]);
		}
		else{
			int result;
			scanf("%d %d",&a,&b);
			if(a <=b)
				result = query_tree(0,0,L-1,a-1,b-1);
			else result = query_tree(0,0,L-1,b-1,a-1);
			printf("%d\n",cal(result));
		}
	}
	return 0;
}