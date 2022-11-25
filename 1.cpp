// LUOGU_RID: 95345570
#include<bits/stdc++.h>
using namespace std;
int ispri[1000005];
vector<int> pri;
void init(){
    for(int i=2;i<=1000000;i++){
        if(!ispri[i]) pri.push_back(i);
        for(int j=0;j<pri.size()&&i*pri[j]<=1000000;j++){
            ispri[i*pri[j]]=1;
            if(i%pri[j]==0) break;
        }
    }
}
long long ans[1005][1005];
long long lcm(long long x,long long y){
    if(!x) return y;
    if(!y) return x;
    return x/__gcd(x,y)*y;
}
int main(){
    int n;cin>>n;init();
    // if(n==2) {puts("4 7\n23 10");return 0;}
    for(int i=1;i<=n;i++)
        for(int j=((i+1)&1)+1;j<=n;j+=2)
            ans[i][j]=(long long)pri[(i+j)/2]*pri[n+(i-j)/2+(n+1)/2];
    for(int i=1;i<=n;i++)
        for(int j=(i&1)+1;j<=n;j+=2)
            ans[i][j]=lcm(ans[i][j-1],lcm(ans[i-1][j],lcm(ans[i+1][j],ans[i][j+1])))+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<ans[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}