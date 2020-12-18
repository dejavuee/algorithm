#include <cstdio>
#include <string>

using namespace std;
typedef long long ll;
const int maxn=200005;
int wa[maxn],wb[maxn],wv[maxn],wss[maxn],rak[maxn],height[maxn],cal[maxn],sa[maxn],idx[maxn];
char s[100005],str[maxn];
int n;
int k; 
ll sta[maxn],num[maxn];
int cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void DA(int *r,int *sa,int n,int M) {
     int i,j,p,*x=wa,*y=wb,*t;
     for(i=0;i<M;i++) wss[i]=0;
     for(i=0;i<n;i++) wss[x[i]=r[i]]++;
     for(i=1;i<M;i++) wss[i]+=wss[i-1];
     for(i=n-1;i>=0;i--) sa[--wss[x[i]]]=i;
     for(j=1,p=1;p<n;j*=2,M=p) {
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) wv[i]=x[y[i]];
        for(i=0;i<M;i++) wss[i]=0;
        for(i=0;i<n;i++) wss[wv[i]]++;
        for(i=1;i<M;i++) wss[i]+=wss[i-1];
        for(i=n-1;i>=0;i--) sa[--wss[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
        x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
     }
     return;
}
void calheight(int *r,int *sa,int n) {
     int i,j,k=0;
     for(i=1;i<=n;i++) rak[sa[i]]=i;
     for(i=0;i<n;height[rak[i++]]=k)
     for(k?k--:0,j=sa[rak[i]-1];r[i+k]==r[j+k];k++);
     for(int i=n;i;i--)rak[i]=rak[i-1],sa[i]++;
}

ll solve(int flag){
	ll sum=0,tmp=0;
	int top=0;//栈顶
	int i,cnt;
	for(i=2;i<=n;i++){
		if(height[i]<k)
			tmp = top = 0;
		else{
			int cnt = 0; 
			if(idx[sa[i-1]]==flag){
				tmp+=height[i]-k+1;
				cnt++;
			}
			while(top>0 && height[i]<=sta[top-1])
			{
				tmp = tmp - num[top-1] * (sta[top-1]-k+1) + (num[top-1]*(height[i]-k+1));
                cnt = cnt+ num[top-1];
                top--;
			}
			sta[top] = height[i];
			num[top] = cnt;
			top++;
			if(idx[sa[i]] != flag)
				sum += tmp;
		}
	}
	return sum; 
}

int main(){
    int cas=1,i,j;
    while(scanf("%d",&k)){
    	if(k==0)
    		break;	
    	n = 1;
    	scanf("%s",s+1);
    	int len = strlen(s+1);
    	for(i=1;i<=len;i++){
    		cal[n]=s[i];
    		idx[n]=0;
    		n++;
    		
    	}
    	cal[n]='#';
    	idx[n]=0;
    	n++;
    	scanf("%s",s+1);
    	len = strlen(s+1);
		 for(i=1;i<=len;i++){
		 	cal[n]=s[i];
		 	idx[n]=1;
		 	n++;
		 }
		 n--;
		 cal[n+1]=0;
		 DA(cal+1,sa,n+1,200);
         calheight(cal+1,sa,n);
         
         ll total = solve(0)+solve(1);
         printf("%lld\n",total);
        
    }
}