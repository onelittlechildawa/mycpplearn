#include<bits/stdc++.h>
#define int long long
using namespace std;
int mod=998244353;
int ksm(int x,int y){
    int t=1;
    while(y){
        if(y&1) t*=x;
        y>>=1;
        x*=x;
        x%=mod;t%=mod;
    }
    return t;
}
int fact[2000005],nifact[2000005];
int C(int a,int b){
	return fact[a]*nifact[a-b]%mod*nifact[b]%mod;
}
signed main(){
    // cout<<ksm(2,10)<<endl;
    int n,u,v,a,b;cin>>n>>u>>v>>a>>b;
    int p=u*ksm(v,mod-2)%mod;
    fact[1]=1;
    for(int i=2;i<=2000000;i++) fact[i]=fact[i-1]*i,fact[i]%=mod,nifact[i]=ksm(fact[i],mod-2)%mod;
    int ans=0;
    cout<<p<<endl;
    ans=a*n%mod*ksm(1-p+mod,mod-2)%mod;
    for(int j=0;j<=n-1;j++){
        int tmp=ksm(1-ksm(p,n-j)+mod,mod-2);
        if((n-j)&1)ans+=b*C(n,j)%mod*tmp%mod;
        else ans-=b*C(n,j)%mod*tmp%mod,ans+=mod;
        ans%=mod;
    }
    cout<<(ans+mod*2)%mod;
    return 0;
}