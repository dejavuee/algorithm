#include <cstdio>
#include <cstdlib>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int pre[1005],w[1005];
int bag1[605],bag2[605];
int dp[605][305],chose[305][305],seti[605];
int find(int x){ //找根节点,更新权值
	int r=x,w1=0;
	while(pre[r]!=r){
	    w1+=w[r];
		r=pre[r];
	}
	pre[x]=r;
	w[x]=w1%2;
	return r;
}
void Union_n(int x,int y){  //不同类合并
	int r1= find(x);
	int r2=find(y);
	if(r1!=r2){
	pre[r1]=y;
	w[r1]=(-w[x]+3)%2;
	}
}
void Union(int x,int y){
	int r1= find(x);
	int r2=find(y);
	if(r1!=r2){
	pre[r1]=y;
	w[r1]=(-w[x]+2)%2;
	}
}

int check (int x){
    int r;
	r = find(x);
	if(chose[0][seti[r]]== w[x])
		return 1;
	else return 0;
}
void DP(int p1,int total,int w){ //动态规划选择集合里同类还是不同类
	int i,j;
	for(i=0;i<=w;i++)
	for(j=0;j<=p1;j++){
			chose[i][j]=0;
	}
	dp[0][0]=1; 
	for(i=1;i<=w;i++){
		for(j=p1;j>=0;j--)
			{
				if(j-bag1[1] >=0)
					dp[i][j] += dp[i-1][j-bag1[i]];
				if(j-bag2[1]>=0)
					dp[i][j] += dp[i-1][j-bag2[i]];
				if(dp[i][j]>=2)	dp[i][j]=2;
				if(dp[i][j]==1){
					if(j - bag1[i] >=0 && dp[i-1][j-bag1[i]] ==1)	
						chose[i][j]=0;
					if(j - bag2[i] >=0 && dp[i-1][j-bag2[i]] ==1) 
						chose[i][j]=1;
				}
			}
	}
	if(dp[w][p1]!=1)
		printf("no\n");
	else{
		int i=w,j=p1;
		while(i>=1){
			chose[0][i] = chose[i][j];
			j = (chose[0][i]==0? j-bag1[i]:j-bag2[i]);
			i--;
		}
		for(i=1;i<=total;i++)
			if(check(i))
				printf("%d\n",i);
		printf("end\n");
	}
	
}
int main() {
	int n,p1,p2;
	int i,j;
	while(scanf("%d %d %d",&n,&p1,&p2)){
		int x,y;
		char c[4];
		if(n==0 && p1==0 && p2==0)
			break;
		for(i=1;i<=(p1+p2);i++){
			pre[i]=i;
			w[i]=0;
			seti[i]=0;
			bag1[i]=0;
			bag2[i]=0;
		}
		for(i=0;i<=(p1+p2);i++)
			for(j=0;j<=(p1+p2);j++){
			dp[i][j]=0;
		}
		for(i=1;i<=n;i++){
			scanf("%d %d %s",&x,&y,c);
			if(find(x)==find(y))
				continue;
			if(c[0]=='n'){
				Union_n(x,y);
			}
			else{
				Union(x,y);
			}
		}
		int j=0;  //记录集合个数和根节点
	    for(i=1;i<=(p1+p2);i++){
		    if(pre[i]==i)
		    {
			    j++;
			    seti[i]=j;
		    }
	    }
	    for(i=1;i<=(p1+p2);i++){ //统计各集合同类和不同类的数量
	        int r = find(i);
			if(w[i]==0) bag1[seti[r]]++;
			else bag2[seti[r]]++;
		}	
	DP(p1,p1+p2,j);
	}
	return 0;
}