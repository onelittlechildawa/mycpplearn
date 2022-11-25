#include<bits/stdc++.h>
const int sN=5e4+1,N=5e4+5,M=1;
typedef long long ll;
const ll mod=998244353;
using namespace std;
int lowbit(int x){
    return x&(-x);
}
struct node{
    unordered_map<int,ll> bit; 
    void merge(node &b){
        for(auto i:b.bit)
            bit[i.first]+=i.second;
    }
    int Qquery(int x){
        ll ans=0;
        while(x){
            ans+=bit[x];
            ans%=mod;
            x-=lowbit(x);
        }
        return ans;
    }
    int query(int x,int y){return Qquery(y)-Qquery(x-1);}
    void add(int x,int y){
        while(x<N){
            bit[x]+=y;
            bit[x]%=mod;
            x+=lowbit(x);
        }
    }
};
int n,m,q,a[N+20],b[N+20];
struct seg_tree{
    node nd[N*32+20];int ls[N*32+20],rs[N*32+20],rt[N+20],cnt=0;
    void clear(){
        for(int i=1;i<=n*32;i++) nd[i].bit.clear();
        memset(rs,0,sizeof(rs));memset(ls,0,sizeof(ls));memset(rt,0,sizeof(rt));cnt=0;
    }
    void push_up(int x){
        if(!ls[x]&&!rs[x]) return;
        if(!ls[x]) nd[x]=nd[rs[x]];
        else if(!rs[x]) nd[x]=nd[ls[x]];
        else nd[x]=nd[ls[x]],nd[x].merge(nd[rs[x]]);
    }
    int add(int id,int l,int r,int a,int b,int c){
        if(!id) id=++cnt;
        if(l==r){
            nd[id].add(b,c);
            return id;
        }
        int mid=(l+r)>>1;
        if(a<=mid) ls[id]=add(ls[id],l,mid,a,b,c);
        else rs[id]=add(rs[id],mid+1,r,a,b,c);
        push_up(id);
        return id;
    }
    int merge(int a,int b,int l,int r){
        if(!a) return b;
        if(!b) return a;
        if(l==r){
            nd[a].merge(nd[b]);
            return a;
        }
        int mid=(l+r)>>1;
        ls[a]=merge(ls[a],ls[b],l,mid);
        rs[a]=merge(rs[a],rs[b],mid+1,r);
        push_up(a);
        return a;
    }
    ll query(int id,int l,int r,int a,int b,int c,int d){
        if(!id) return 0;
        if(a<=l&&r<=b) return nd[id].query(c,d);
        int mid=(l+r)>>1;ll ans=0;
        if(a<=mid) ans+=query(ls[id],l,mid,a,b,c,d);
        if(b>mid) ans+=query(rs[id],mid+1,r,a,b,c,d);
        ans%=mod;
        return ans;
    }
}s2;
vector<int> v[N+20];
void cnt2(int x,int fa){
    s2.rt[x]=0;
    for(int i:v[x]){
        if(i==fa) continue;
        cnt2(i,x);
        s2.rt[x]=s2.merge(s2.rt[x],s2.rt[i],1,sN);
    }
    int res=s2.query(s2.rt[x],1,sN,M,a[x]+M,1,b[x]+M)+1;
    int delta=0;
    delta=s2.add(delta,1,sN,a[x]+M,b[x]+M,res);
    s2.rt[x]=s2.merge(s2.rt[x],delta,1,sN);
}
void cnt3(int x,int fa){
    s2.rt[x]=0;
    for(int i:v[x]){
        if(i==fa) continue;
        cnt3(i,x);
        s2.rt[x]=s2.merge(s2.rt[x],s2.rt[i],1,sN);
    }
    int res=s2.query(s2.rt[x],1,sN,M,a[x]+M,b[x]+M,sN)+1;
    int delta=0;
    delta=s2.add(delta,1,sN,a[x]+M,b[x]+M,res);
    s2.rt[x]=s2.merge(s2.rt[x],delta,1,sN);
}
void cnt4(int x,int fa){
    s2.rt[x]=0;
    for(int i:v[x]){
        if(i==fa) continue;
        cnt4(i,x);
        s2.rt[x]=s2.merge(s2.rt[x],s2.rt[i],1,sN);
    }
    int res=s2.query(s2.rt[x],1,sN,M,a[x]+M,1,sN)+1;
    int delta=0;
    delta=s2.add(delta,1,sN,a[x]+M,b[x]+M,res);
    s2.rt[x]=s2.merge(s2.rt[x],delta,1,sN);
}
int ta[N+20],tb[N+20],tc[N+20],td[N+20],te[N+20],tf[N+20],ans[N+20];
vector<int> v1,v2,v3;
void cacl2(){
    cnt2(1,0);
    for(int i:v1){
        ans[i]=s2.query(s2.rt[ta[i]],1,sN,tb[i]+M,tc[i]+M,td[i]+M,te[i]+M);
    }
}
void cacl3(){
    s2.clear();
    cnt3(1,0);
    for(int i:v2){
        ans[i]=s2.query(s2.rt[ta[i]],1,sN,tb[i]+M,tc[i]+M,td[i]+M,te[i]+M);
    }
}
void cacl4(){
    s2.clear();
    cnt4(1,0);
    for(int i:v3){
        ans[i]=s2.query(s2.rt[ta[i]],1,sN,tb[i]+M,tc[i]+M,td[i]+M,te[i]+M);
    }
}
int main(){
    // freopen("2.in","r",stdin);
    ios::sync_with_stdio(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=0;i<n-1;i++){
        int x,y;cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=0;i<m;i++){
        cin>>ta[i]>>tb[i]>>tc[i]>>td[i]>>te[i]>>tf[i];
        if(tf[i]>0) v1.push_back(i);
        else if(tf[i]<0) v2.push_back(i);
        else v3.push_back(i);
    }
    cacl2();cacl3();cacl4();
    for(int i=0;i<m;i++) cout<<ans[i]<<endl;
    return 0;
}