#include <cstdio>
#include<algorithm>
#define MAXN 20005
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef long long ll;
ll at[MAXN],post[MAXN];
int N;
ll cow1[MAXN];
pair <int,ll> cow[MAXN];
pair <int,ll> pos[MAXN];

int lowbit(int x){
	return x & -x;
}

void init(){
	int i;
	for(i=1;i<=N;i++){
		at[i]+=pos[i].second;
		int j = i+lowbit(i);
		if(j<=N)
			at[j]+=at[i]; 
	}
	for(i=1;i<=N;i++){
		post[i]+=1;
		int j = i+lowbit(i);
		if(j<=N)
			post[j]+=post[i]; 
	}
/*	for(i=1;i<=N;i++){
		printf("%d ",post[i]);
	}
	printf("\n");
	for(i=1;i<=N;i++){
		printf("%d ",at[i]);
}
	printf("\n");*/
}

bool cmp (pair <int,ll> a1,pair <int,ll> a2) {
	return a1.second > a2.second;
}

bool cmp2 (pair <int,ll> a1,pair <int,ll> a2) {
	return a1.second < a2.second;
}

void addq(ll *bit,int x,ll k){
	while(x<=N){
		bit[x]+=k;
		x+=lowbit(x);
	}
}

ll getsum(ll* bit,int x){
	ll ans=0;
	while(x>=1){
		ans = ans+bit[x];
		x = x-lowbit(x);
	}
	return ans;
}

ll insum(ll *bit,int from,int to){
	return getsum(bit,to)-getsum(bit,from-1);
}

int main() {
	//freopen(".//cow.txt","r",stdin);
	scanf("%d",&N);
	int i,j,x,y;
	for(i=1;i<=N;i++){
		scanf("%d %d",&cow1[i],&y);
		pos[i]=make_pair(i,y);
	}
	sort(pos+1,pos+N+1,cmp2); //将奶牛对于坐标排序
	init(); //初始化关于坐标的两个线段树  
	for(i=1;i<=N;i++){
		cow[i]=make_pair(i,cow1[pos[i].first]); 
	}
	sort(cow+1,cow+N+1,cmp); //将奶牛对于v排序 
	ll total = 0;
	for(i=1;i<=N;i++){
		int j;
		//printf("%d:%d \n",cow[i].first,cow[i].second);
		ll leftnum = insum(post,1,cow[i].first-1);
		ll rightnum = insum(post,cow[i].first+1,N);
		total += cow[i].second * (insum(at,cow[i].first+1,N) - insum(at,1,cow[i].first-1));
		total +=cow[i].second *(leftnum-rightnum) * pos[cow[i].first].second;
		addq(post,cow[i].first,-1);
		addq(at,cow[i].first,-pos[cow[i].first].second);
	}
	printf("%lld\n",total);
	return 0;
}