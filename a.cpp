#include<bits/stdc++.h>
using namespace std;
int paidui[1000005],npid=1;
int hurt[105];//-1 敌意 1 友善 2 类
const char paitc[105]={'P','K','D','F','N','W','J','Z'};
//           桃  杀  闪  决斗 南蛮万箭无懈连弩
//           0   1   2   3    4   5   6   7
int N,M;
int tu=1,pl=1;
int shalim=9999;
struct pig{
    int id,type,health,withz,tiao,det;//1M主,2Z忠,3F反
    vector<int> card,circl;
    void getpai(int x){
        while(x--){card.push_back(paidui[npid++]);if(npid>M) npid--;};
    }
    int askformiss(int x){//1-yes 0-no
        for(int i=0;i<card.size();i++){
            if(card[i]==x){
                int ts=card.size();
                // cout<<"erase"<<*(card.begin()+i)<<endl;
                card.erase(card.begin()+i);//TODO
                assert(card.size()<ts);
                return 1;
            }
        }
        return 0;
    }
    // bool hav(int x){return find(card.begin(),card.end(),x)!=card.end();}
    int death(int x){
        if(health>=1) {return 0;}
        else if(askformiss(0)){
            health=1;
            return 0;
        }
        else {
            health=0;
            det=1;
            if(x==1&&type==2) return 2;
            if(type==3) return 3;
            return 1;
        }
    }
}pi[105];
int dis(int x,int y){
    if(y>x){
        int cnt=0;
        for(int i=x+1;i<=y;i++){
            if(!pi[i].det) cnt++;
        }
        return cnt;
    }
    else {
        int cnt=0;
        for(int i=x+1;i<=N;i++)
            if(!pi[i].det) cnt++;
        for(int i=1;i<=y;i++) 
            if(!pi[i].det) cnt++;
        return cnt;
    }
}
int checkwin(){
    if(pi[1].det) return 2;
    for(int i=1;i<=N;i++) if(pi[i].type==3&&!pi[i].det) return 0;
    return 1;
}
int getrel(int x,int y){
    if(pi[y].det||pi[x].det)return 0;
    if(pi[x].type==1) {
        if(y==1||pi[y].tiao&&pi[y].type==2) return 2;//能够献殷勤
        if((hurt[y]||(pi[y].tiao&&pi[y].type==3))) return 1;
    }
    else if(pi[x].type==2){
        if(y==1||pi[y].tiao&&pi[y].type==2) return 2;
        if(pi[y].tiao&&pi[y].type==3) return 1;
    }
    else if(pi[x].type==3){
        if(pi[y].tiao&&pi[y].type==3) return 2;
        if(y==1||pi[y].tiao&&pi[y].type==2) return 1;
    }
    return 0;
}
void updaterel(int x,int y,int typ){
    if(pi[x].type==1) return;
    if(typ==1){//fuck
        if(y==1||pi[y].tiao&&pi[y].type==2) pi[x].tiao=1;
        if(pi[y].tiao&&pi[y].type==3) pi[x].tiao=1;
    }
    else {
        if(y==1||pi[y].tiao&&pi[y].type==2) pi[x].tiao=1;
        if(pi[y].tiao&&pi[y].type==3) pi[x].tiao=1;
    }
}
int findvic(int x,int lim){
    if(pi[x].type==1){
        for(int i:pi[x].circl){
            if(i==x) continue;
            // cout<<hurt[i]<<'\n';
            if(getrel(x,i)==1&&dis(x,i)<=lim){
                return i;
            }
        }
    }
    else if(pi[x].type==2){
        for(int i:pi[x].circl){
            if(i==x) continue;
            if(getrel(x,i)==1&&dis(x,i)<=lim){
                return i;
            }
        }
    }
    else if(pi[x].type==3){
        if(dis(x,1)<=lim) return 1;
        else {
            for(int i:pi[x].circl){
                if(i==x) continue;
                if(getrel(x,i)==1&&dis(x,i)<=lim){
                    return i;
                }
            }
        }
    }
    return 0;
}
bool nouse(int x,int y,int fo){
    for(int i:pi[x].circl){
        if(fo+1==getrel(i,y)){
            if(pi[i].askformiss(6)){
                pi[i].tiao=1;
                // cout<<i<<"use J\n";
                if(nouse(i,y,fo^1)) return 0;
                else return 1;
            }
        }
    }
    return 0;
}
void hur(int x,int y,int car){

    // cout<<x<<"hurt"<<y<<' '<<car<<endl;
    
    if(y==1&&(car==4||car==5)) hurt[x]=1;
    pi[y].health--;
    int tmp=pi[y].death(x);
    if(tmp==2) {
        if(checkwin()) return ;
        pi[x].withz=0;
        pi[x].card.clear();
    }
    else if(tmp==3){
        if(checkwin()) return;
        pi[x].getpai(3);
    }
}
void fight(int x,int y){
    if(x==1&&pi[y].type==2) {hur(x,y,3);return;}
    while(1){
        if(!pi[y].askformiss(1)) {hur(x,y,3);return;}
        if(!pi[x].askformiss(1)) {hur(y,x,3);return;}
    }
}
void chupai(int x,int y,int z){

    // printf("%d,%c,%d\n",x,paitc[pi[x].card[y]],z);//TOD
    
    pi[x].card.erase(pi[x].card.begin()+y);
}
bool gopai(int x){
    for(int i=0;i<pi[x].card.size();i++){
        int np=pi[x].card[i],vic;
        if(np==0) {if(pi[x].health!=4) {pi[x].health++;chupai(x,i,x);return 1;}}
        if(np==1&&shalim){
            int td=findvic(x,1);
            if(td){
                chupai(x,i,td);
                updaterel(x,td,1);
                if(!pi[td].askformiss(2)){
                   hur(x,td,np);
                   if(checkwin()) return 0;
                }
                shalim--;
                return 1;
            }
        }
        if(np==3){
            int td=findvic(x,999);
            if(td){
                chupai(x,i,td);
                updaterel(x,td,1);
                if(nouse(x,td,1)) return 1;
                fight(x,td);
                if(checkwin()) return 0;
                return 1;
            }
        }
        if(np==4){
            chupai(x,i,0);
            for(int j:pi[x].circl){
                if(j==x||pi[j].det) continue;
                if(nouse(x,j,1)) continue;
                if(!pi[j].askformiss(1)){
                    hur(x,j,4); 
                    if(checkwin()) return 0;
                }
            }
            return 1;
        }
        if(np==5){
            chupai(x,i,0);
            for(int j:pi[x].circl){
                // cout<<j<<'\n';
                if(j==x||pi[j].det) continue;
                if(nouse(x,j,1)) continue;
                if(!pi[j].askformiss(2)){
                    hur(x,j,5);
                    if(checkwin()) return 0;
                }
            }
            return 1;
        }
        if(np==7){
            chupai(x,i,x);
            pi[x].withz=1;
            shalim=99999;
            return 1;
        }
    }
    return 0;
}
void runturn(int x){
    shalim=1;if(pi[x].withz) shalim=99999;
    pi[x].getpai(2);

    // printf("--------\n%d%d\n",pl,x);
    // for(int i:pi[x].card) cout<<paitc[i]<<' ';puts("");//
    
    while(gopai(x)&&!pi[x].det);
    pl++;

    // for(int i=1;i<=N;i++){
    //     if(pi[i].det) cout<<"DEAD";
    //     else 
    //         for(int j:pi[i].card) cout<<paitc[j]<<' ';//
    //     cout<<pi[i].health<<' '<<pi[i].tiao<<"\n";
    // }

}
int paiti[256];
int main(){
    // freopen("6.in","r",stdin);
    // freopen("a.ou","w",stdout);
    cin>>N>>M;
    for(int i=0;i<8;i++) paiti[paitc[i]]=i;
    for(int i=1;i<=N;i++){
        string s;cin>>s;
        pi[i].id=i;pi[i].det=0;
        for(int j=i;j<=N;j++) pi[i].circl.push_back(j);
        for(int j=1;j<=i-1;j++) pi[i].circl.push_back(j);
        if(s=="MP") pi[i].type=1;
        else if(s=="ZP") pi[i].type=2;
        else if(s=="FP") pi[i].type=3;
        pi[i].health=4,pi[i].withz=0;
        char c;
        for(int j=0;j<4;j++) cin>>c,pi[i].card.push_back(paiti[c]);
    }

    // for(int i=1;i<=N;i++){
    //     if(pi[i].det) cout<<"DEAD";
    //     else 
    //         for(int j:pi[i].card) cout<<paitc[j]<<' ';//
    //     cout<<pi[i].health<<"\n";
    // }
    
    for(int i=1;i<=M;i++) {char c;cin>>c;paidui[i]=paiti[c];}
    for(int i=1;i<=N;i++){
        if(pi[i].det) {if(i==N) i=0;continue;}
        runturn(i);
        if(checkwin()) break;
        if(i==N) i=0;
    }
    if(checkwin()==2) cout<<"FP\n";
    else cout<<"MP\n";
    for(int i=1;i<=N;i++){
        if(pi[i].det) cout<<"DEAD";
        else 
            for(int j:pi[i].card) cout<<paitc[j]<<' ';
        cout<<'\n';
    }
    return 0;
}
