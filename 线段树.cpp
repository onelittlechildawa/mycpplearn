#include<bits/stdc++.h>
using namespace std;
int n,ls[100005],rs[100005],sum[100005],cnt=0,rt[100005];
int fa[100005],id[100005];
int m,q;
void update(int x){
	sum[x]=sum[ls[x]]+sum[rs[x]];
}
int add(int a,int x,int y,int pos,int idx){
	if(!a) a=++cnt;
	if(x==y){
		sum[a]++;
		id[a]=idx;
		return a;
	}
	int mid=(x+y)>>1;
	if(pos<=mid) ls[a]=add(ls[a],x,mid,pos,idx);
	else rs[a]=add(rs[a],mid+1,y,pos,idx);
	update(a);
	return a;
}
int merge(int a,int b,int x,int y){
	if(!a) return b;
	if(!b) return a;
	if(x==y) {
		if(id[b]) {id[a]=id[b];sum[a]+=sum[b];}
		return a;
	}
	int mid=(x+y)>>1;
	ls[a]=merge(ls[a],ls[b],x,mid);
	rs[a]=merge(rs[a],rs[b],mid+1,y);
	update(a);
	return a;
}
int query(int a,int k,int x,int y){
	int ans;
	if(sum[a]<k||!a) return 0;
	if(x==y) return id[a];
	int mid=(x+y)>>1;
	if(k<=sum[ls[a]]) return query(ls[a],k,x,mid);
	else return query(rs[a],k-sum[ls[a]],mid+1,y);
}
int findfa(int x){
	return x==fa[x]?x:fa[x]=findfa(fa[x]);
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		int k;cin>>k;
		fa[i]=i;rt[i]=add(rt[i],1,n,k,i);
	}
	for(int i=1;i<=m;i++){
		int a,b;cin>>a>>b;
		int fx=findfa(a),fy=findfa(b);
		fa[fy]=fx;
		rt[fx]=merge(rt[fx],rt[fy],1,n);
	}
	int q;cin>>q;
	while(q--){
		char c;cin>>c;
		if(c=='Q'){
			int x,y;cin>>x>>y;
			int res=query(rt[findfa(x)],y,1,n);
			if(res) cout<<res<<endl;
			else cout<<-1<<endl;
		}
		else {
			int a,b;cin>>a>>b;
			int fx=findfa(a),fy=findfa(b);
			if(fx==fy) continue;
			fa[fy]=fx;
			rt[fx]=merge(rt[fx],rt[fy],1,n);
		}
	}
	return 0;
}
