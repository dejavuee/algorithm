#include<vector>
#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std; 
 
const int N = 2E5;
 
char str[N],a[N];
int n,s[N],sa[N],rk[N],oldrk[N<<1];
int cnt[N],ht[N],px[N],id[N],idx[N];
 
bool cmp(int x,int y,int w){
	return oldrk[x]==oldrk[y] && oldrk[x+w]==oldrk[y+w];
}
 
void da(int s[],int n,int m){
	int i,p=0,w,k;
	
	for(i=1;i<=n;i++) ++cnt[rk[i] = s[i]];
	for(i=1;i<=m;i++) cnt[i] += cnt[i-1];
	for(i=n;i>=1;i--) sa[cnt[rk[i]]--] = i;
	
	for(w=1;w<n;w<<=1,m=p){
		for(p=0,i=n;i>n-w;i--) id[++p]=i;
		for(i=1;i<=n;i++)
		    if(sa[i]>w) id[++p]=sa[i]-w;
		memset(cnt,0,sizeof(cnt));
		for(i=1;i<=n;i++) ++cnt[px[i] = rk[id[i]]];
		for(i=1;i<=m;i++) cnt[i] += cnt[i-1];
		for(i=n;i>=1;i--) sa[cnt[px[i]]--] = id[i];
		memcpy(oldrk,rk,sizeof(rk));
		
		for(p=0,i=1;i<=n;i++)
		    rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
	}
	
	for(i=1,k=0;i<=n;i++){
		if(k) --k;
		while(s[i+k]==s[sa[rk[i]-1]+k]) ++k;
		ht[rk[i]]=k;
	} 
}
 
int num[105],m;
 
vector<int>ans,vt;
 
bool judge(){
 
	int tot=0; 
	for(int i=1;i<=m;i++)
	  if(num[i]) tot++;
	if(tot>m/2){                 
	    for(int i=1;i<=m;i++)
	      if(num[i]){
	        vt.push_back(num[i]);    //记录一下
	        break;
		  }
		return 1;
	}
	return 0;
}
 
bool check(int len){
	vt.clear();
	memset(num,0,sizeof(num));
	bool flag=0;
	for(int i=2;i<=n;i++){
		if(ht[i]>=len){
			num[idx[sa[i-1]]]=sa[i-1];
			num[idx[sa[i]]]=sa[i];
		}
		else{
			if(judge()){   
			   	flag=1;
			}
			memset(num,0,sizeof(num));
		}
	}
	return judge()||flag;
}
 
int main(){
	
    int T=0;
	while(scanf("%d",&m)&&m){
		memset(cnt,0,sizeof(cnt));
		if(T>0) puts("");
		n=0;
		for(int i=1;i<=m;i++){
			scanf("%s",a+1);
			int len=strlen(a+1);
			for(int j=1;j<=len;j++){
				str[++n]=a[j];
				s[n]=str[n];
				idx[n]=i;
			}
			str[++n]='#';
			s[n]=150+i;
		}
		n--;
		da(s,n,300);
		int l=1,r=1000,ANS=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){
				ANS=mid;
				ans=vt;
				l=mid+1;
			}
			else r=mid-1;
		}
		if(ANS==-1){
			puts("?");
		}
		else{
			vector<string>S;
			for(int i=0;i<ans.size();i++){
				char s[1005];
				for(int j=0;j<ANS;j++){
					s[j]=str[j+ans[i]];
				}
				s[ANS]='\0';
				S.push_back(s);
			}
			sort(S.begin(),S.end());
			for(int i=0;i<S.size();i++) cout<<S[i]<<'\n'; 
		}
		T++;
	}
}