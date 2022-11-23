#include<bits/stdc++.h>
const int N=3e5;
using namespace std;
int n,fa[N][22],dep[N],rt[N];
int sum[32*N],cnt=0,res[32*N],ls[32*N],rs[32*N];
int w[N];
int m,ans[N];
vector<int> v[N];
int merge(int a,int b,int x,int y){
    if(!a) return b;
    if(!b) return a;
    if(x==y){
        sum[a]+=sum[b];
        return a;
    }
    int mid=(x+y)>>1;
    ls[a]=merge(ls[a],ls[b],x,mid);
    rs[a]=merge(rs[a],rs[b],mid+1,y);
    return a;
}
int add(int id,int x,int y,int co,int val){
    if(!id) id=++cnt;
    if(x==y){
        sum[id]+=val;
        return id;
    }
    int mid=(x+y)>>1;
    if(co<=mid)ls[id]=add(ls[id],x,mid,co,val);
    else rs[id]=add(rs[id],mid+1,y,co,val);
    return id;
}
int get(int id,int x,int y,int co){
    if(!id) return 0;
    if(x==y) return sum[id];
    int mid=(x+y)>>1;
    if(co<=mid) return get(ls[id],x,mid,co);
    else return get(rs[id],mid+1,y,co);
}
void initlca(int x){
    for(int i=0;i<=20;i++) fa[x][i+1]=fa[fa[x][i]][i];
    for(int i:v[x]){
        if(i==fa[x][0]) continue;
        dep[i]=dep[x]+1;
        fa[i][0]=x;initlca(i);
    }
}
int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int d=dep[x]-dep[y],i=0;d;d>>=1,i++) 
        if(d&1) x=fa[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--)
        if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void cacl(int x){
    for(int i:v[x]){
        if(i==fa[x][0]) continue;
        cacl(i);
        rt[x]=merge(rt[x],rt[i],1,2*N);
    }
    if(w[x]&&n+dep[x]+w[x]<=2*n)
        ans[x]+=get(rt[x],1,N*2,n+dep[x]+w[x]);
    ans[x]+=get(rt[x],1,N*2,n+dep[x]-w[x]);
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    initlca(1);
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=0;i<m;i++){
        int a,b;cin>>a>>b;
        int t=lca(a,b);
        rt[a]=add(rt[a],1,N*2,n+dep[a],1);
        rt[b]=add(rt[b],1,N*2,n+dep[t]*2-dep[a],1);
        // cout<<lca(a,b)<<endl;
        rt[t]=add(rt[t],1,N*2,n+dep[a],-1);
        rt[fa[t][0]]=add(rt[fa[t][0]],1,N*2,n+dep[t]*2-dep[a],-1);
    }
    cacl(1);
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    return 0;
}