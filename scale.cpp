#include<bits/stdc++.h>

using namespace std;

const int MAXN=100000+10;
vector<long long> G[MAXN];
vector<int> ans;
long long k[MAXN],sum[MAXN];
int n;

void input(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		G[i].push_back(min(a,b));
		G[i].push_back(max(a,b));
	}
}

long long work(long long nod){
	long long a=G[nod][0],b=G[nod][1];
	if(a<0&&b<0) return k[nod]=2;
	if(a<0) return k[nod]=work(b)*2;
	return k[nod]=max(work(a),work(b))*2;
}

long long gcd(long long a,long long b){
	long long x=min(a,b),y=max(a,b),tmp;
	while(x%y!=0){
		tmp=x%y;
		x=y;
		y=tmp;
	}
	return a/y*b;
}

long long solve(long long suma,int a,long long sumb,int b){
	long long tmp=gcd(suma-sumb,k[b]);
	while( (tmp+sumb-suma)%k[a]!=0 ){
		tmp*=2;
	}
	return tmp+sumb;
}

long long dfs(int nod){
	long long a=G[nod][0],b=G[nod][1];
	if(a<0&&b<0){
		return sum[nod]=-2*min(a,b);
	}
	else if(a<0){
		long long suma=-a,sumb=dfs(b);
		if(suma<=sumb) return sum[nod]=2*sumb;
		else{
			return sum[nod]=2*(sumb+gcd(k[b],suma-sumb));
		}
	}
	else{
		int suma=dfs(a),sumb=dfs(b);
		if(suma>sumb) return sum[nod]=2*solve(suma,a,sumb,b);
		else return sum[nod]=2*solve(sumb,b,suma,a);
	}
}

void output(long long x){//cout<<x<<endl;
	if(!x) return;
	output(x/2);
	cout<<x%2;
}

int main(){
	input();
	work(1);
	dfs(1);
//	cout<<sum[1]<<endl; 
//	output(sum[1]);
	for(int i=1;i<=n;i++) output(sum[i]),puts("");
	puts("");
	return 0;
}
/*
4
2 3
-9 4
-2 -13
-1 -7

5
2 4
-1 3
-1 -5
-5 5
-3 -7

*/
