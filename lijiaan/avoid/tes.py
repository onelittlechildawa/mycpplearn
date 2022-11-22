import math
mod=int(1e9+7)
tmp=201260731
while 1:
    if(abs(int((-1+math.sqrt(1+4*tmp))/2)-(-1+math.sqrt(1+4*tmp))/2)<0.1):
        break
    tmp+=mod
print(tmp,(-1+math.sqrt(1+4*tmp))/2)