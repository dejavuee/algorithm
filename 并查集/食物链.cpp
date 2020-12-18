#include<cstdio>
int yes(int a){return (a%3+3)%3;}
int OK(int x) {return x==1?0:2;}
int f[50005];
int dis[50005];
int n,k,o;
int ds(int x)
{
	if(f[x]==0)
		return 0;
	return dis[x]+ds(f[x]);
}
int find(int x)
{
	if(f[x]==0)
		return x;
	else
	{
		dis[x]=ds(x);
		f[x]=find(f[x]);
		return f[x];
	}
}
int main()
{
	scanf("%d%d",&n,&k);
	for(int i=1;i<=k;i++)
	{
		int a,b,x;
		scanf("%d%d%d",&x,&a,&b);
		if(a>n||b>n||(x==2&&a==b)){o++;continue;}
		if(x==1&&a==b)continue;
		int p=find(a),q=find(b);
		if(p==q)
		{
			if(yes(ds(a)-ds(b))!=OK(x))
				o++;
		}
		else
		{
			dis[q]=yes(ds(a)-ds(b)+x-1);
			f[q]=p;
		}
	}
	printf("%d",o);
}