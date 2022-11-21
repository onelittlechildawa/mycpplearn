#include<bits/stdc++.h>
using namespace std;
int paidui[10005],npid=1;
int hurt[105];//-1 敌意 1 友善 2 类
const char paitc[105]={'P','K','D','F','N','W','J','Z'};
//           桃  杀  闪  决斗 南蛮万箭无懈连弩
//           0   1   2   3    4   5   6   7
int N,M;
int dis(int x,int y){
    int tmp=y-x;if(tmp<0) tmp+=N;
    return tmp;
}
struct pig{
    int id,type,health,withz,tiao,det;//1M主,2Z忠,3F反
    vector<int> card,circl;
    void getpai(int x){
        while(x--)card.push_back(paidui[npid++]);
    }
    bool askformiss(int x){//1-yes 0-no
        for(int i=0;i<card.size();i++){
            if(card[i]==x){
                card.erase(card.begin()+i);//TODO
                return 1;
            }
        }
        return 0;
    }
    bool hav(int x){return card.find(x)!=card.end();}
    int death(int x){
        if(health>=1) return 0;
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
int getrel(int x,int y){
    if(p[x].type==1) {
        if(pi[i].tiao&&pi[i].type==2) return 2;
        if((hurt[x]||(pi[i].tiao&&pi[i].type==3))&&!pi[i].det) return 1;
    }
}
int updaterel(int x,int y,int typ){

}
int findvic(int x){
    if(pi[x].type==1){
        for(int i:pi[x].circl){
            if(){
                return i;
            }
        }
    }
    else if(pi[x].type==2){
        for(int i:pi[x].circl){
            if(pi[i].tiao&&pi[i].type==3&&!pi[i].det){
                return i;
            }
        }
    }
    else if(pi[x].type==3){
        if(dis(1,x)<=1) return 1;
        else {
            for(int i:pi[x].circl){
                if(pi[i].tiao&&pi[i].type==2&&!pi[i].det){
                    return i;
                }
            }
        }
    }
    return 0;
}
void nouse(int x,int y,int fo){=
    for(int i:pi[x].circl){

    }
}
bool gopai(int x){
    for(int i=0;i<pi[x].card.size();i++){
        int np=pi[x].card[i],vic;
        if(np==0) {if(pi[x].health!=4) health++,pi[x].card.erase(pi[x].card.begin());return 1;}//TODO
        if(np==1){
            int td=findvic(x);
            if(td){//TODO
                if(!pi[td].askformiss(2)){
                    pi[td].health--;int tmp=pi[td].death(x);
                    if(tmp==2) {
                        pi[x].withz=0;
                        pi[x].card.clear();
                    }
                    else if(tmp==3){
                        pi[x].getpai(3);
                    }
                }
                else {

                }
            }
        }
        if(np==3){
            int td=findvic(x);
        }
    }
    return 0;
}
void runturn(int x){
    pi[x].getpai(2);
    while(gopai(x));
}
int paiti[256];
int main(){
    cin>>N>>M;
    for(int i=0;i<8;i++) paiti[paitc[i]]=i;
    for(int i=1;i<=N;i++){
        string s;cin>>s;
        pi[i].id=i;pi[i].det=1;
        for(int j=i+1;j<=N;j++) pi[i].circl.push_back(j);
        for(int j=1;j<=i-1;j++) pi[i].circl.push_back(j);
        if(s=="MP") pi[i].type=1;
        else if(s=="ZP") pi[i].type=2;
        else if(s=="FP") pi[i].type=3;
        pi[i].health=4,pi[i].withz=0;
        char c;
        for(int i=0;i<4;i++) cin>>c,pi[i].card.push_back(paiti[c]);
    }
    for(int i=1;i<=M;i++) {char c;cin>>c;paidui[i]=paiti[c];}

    return 0;
}
