#include<bits/stdc++.h>
const int sN=5e4,N=5e4,M=1;
typedef long long ll;
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
            x-=lowbit(x);
        }
        return ans;
    }
    int query(int x,int y){return Qquery(y)-Qquery(x-1);}
    void add(int x,int y){
        while(x<N){
            bit[x]+=y;
            x+=lowbit(x);
        }
    }
};
struct seg_tree{
    node nd[N*20+20];int ls[N*20+20],rs[N*20+20],rt[N+20],cnt=0;
    // seg_tree(){memset(rs,0,sizeof(rs));memset(ls,0,sizeof(ls));memset(rt,0,sizeof(rt));cnt=0;}
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
    int query(int id,int l,int r,int a,int b,int c,int d){
        if(!id) return 0;
        if(a<=l&&r<=b) return nd[id].query(c,d);
        int mid=(l+r)>>1,ans=0;
        if(a<=mid) ans+=query(ls[id],l,mid,a,b,c,d);
        if(b>mid) ans+=query(rs[id],mid+1,r,a,b,c,d);
        return ans;
    }
}s1,s2,s3;
int n,m,q,a[N+20],b[N+20];
vector<int> v[N+20];
void cnt1(int x,int fa){
    s1.rt[x]=s1.add(s1.rt[x],1,sN,a[x]+M,b[x]+M,1);
    for(int i:v[x]){
        if(i==fa) continue;
        cnt1(i,x);
        s1.merge(s1.rt[x],s1.rt[i],1,sN);
    }
    int qs2=s1.query(s1.rt[x],1,sN,1,1,a[x]+M,b[x]+M);
    int qs3=s1.query(s1.rt[x],1,sN,1,b[x]+M,a[x]+M,sN);
    s2.rt[x]=s2.add(s2.rt[x],1,sN,a[x]+M,b[x]+M,qs2);
    s3.rt[x]=s3.add(s3.rt[x],1,sN,a[x]+M,b[x]+M,qs3);
}
void cnt2(int x,int fa){
    for(int i:v[x]){
        if(i==fa) continue;
        cnt2(i,x);
        s2.merge(s2.rt[x],s2.rt[i],1,sN);
        s3.merge(s3.rt[x],s3.rt[i],1,sN);
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin>>n;
    // for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    s1.rt[1]=s1.add(s1.rt[1],1,sN,2,2,1);
    while(1){
        int a,b,c,d;cin>>a>>b>>c>>d;
        cout<<s1.nd[s1.rt[1]].query(c+M,d+M)<<endl;
        cout<<s1.query(s1.rt[1],1,sN,a+M,b+M,c+M,d+M)<<endl;
    }
    return 0;
}
/*5
1 1
1 2
2 1
2 2
3 3
1 2
2 3
3 4
4 5*/