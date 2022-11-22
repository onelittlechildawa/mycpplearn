a=1
with open("a.in","w+") as p:
    for i in range(1,1001):
        a*=i
        if i%25==0: p.write('"'+str(a)+'",')
