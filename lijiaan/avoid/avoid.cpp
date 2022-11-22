#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=1e9+7;
vector<int> v[100005],w[100005];
int n,m,s,t;
int d[2][100005],inq[100005],cnt[2][100005],ccnt[2][100005];
struct node{
    
};
void spfa(int x,int tp){
    queue<int> q;
    memset(inq,0,sizeof(inq));
    q.push(x);d[tp][x]=0;inq[x]=1;cnt[tp][x]=1;
    while(!q.empty()){
        int nt=q.front();q.pop();inq[nt]=0;
        ccnt[tp][nt]=cnt[tp][nt];
        for(int i=0;i<v[nt].size();i++){
            if(d[tp][v[nt][i]]>d[tp][nt]+w[nt][i]) {
                d[tp][v[nt][i]]=d[tp][nt]+w[nt][i];
                cnt[tp][v[nt][i]]=cnt[tp][nt];
                if(!inq[v[nt][i]]) q.push(v[nt][i]),inq[v[nt][i]]=1;
            }
            else if(d[tp][v[nt][i]]==d[tp][nt]+w[nt][i]){
                cnt[tp][v[nt][i]]+=cnt[tp][nt];
                if(!inq[v[nt][i]]) q.push(v[nt][i]),inq[v[nt][i]]=1;
                // printf("%lld %lld %lld\n",cnt[tp][v[nt][i]],v[nt][i],nt);
            }
        }
        cnt[tp][nt]=0;
    }
}
signed main(){
    freopen("avoid.in","r",stdin);
    freopen("avoid.out","w",stdout);
    ios::sync_with_stdio(0);
    cin>>n>>m>>s>>t;
    for(int i=1;i<=n;i++) d[0][i]=d[1][i]=1e16;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        v[a].push_back(b);w[a].push_back(c);
        v[b].push_back(a);w[b].push_back(c);
    }
    spfa(s,0);
    // ct(s,0);
    spfa(t,1);
    // ct(t,1);
    // cout<<ccnt[0][t]<<' '<<ccnt[1][s]<<endl;
    int ans=ccnt[0][t]*ccnt[1][s]%mod;
    for(int i=1;i<=n;i++){
        if(d[0][i]==d[1][i]) {ans-=(ccnt[0][i]*ccnt[1][i]%mod);}
        else
            for(int j=0;j<v[i].size();j++){
                if(d[0][i]+d[1][v[i][j]]+w[i][j]==d[0][t]){
                    if(d[0][i]<d[0][t]/2&&d[1][v[i][j]]<d[1][s]/2){
                        // cout<<"fuck"<<endl;
                        ans-=ccnt[0][i]*ccnt[1][v[i][j]]%mod;
                    }
                }
            }
    }
    cout<<(ans+mod)%mod;
    return 0;
}
/*
6 7
1 6
1 2 1
2 3 1
3 4 1
2 4 2
4 5 1
1 5 4
5 6 1
*/