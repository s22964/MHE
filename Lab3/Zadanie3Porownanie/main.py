import sys
from itertools import permutations
import time
file = open("PythonTime.txt", "a")
start_time = time.time()

n = len(sys.argv)

def Quality(v,T):
    Q=0
    i=0
    while i<len(v):
        s=sum(v[i])
        Q+=abs(T-s)
        i+=1
    return Q



S=[];
for i in range(1, n):
    S.append(int(sys.argv[i]))
if not (len(S)%3==0):
    print("Zbior musi byc podzielny przez 3!")

else:
    m=len(S)
    Sum=sum(S)
    T=int(Sum/(m/3))
    print("Suma T="+str(T))
    Q=-1
    v=[]
    act=[]
    ans=[]

    X=0
    S.sort()
    for x in permutations(S):
        act.clear()
        i=0
        X+=1
        v.clear()
        j=0

        while j<m/3:
            v=[x[i],x[i+1],x[i+2]]
            act.append(v)
            j+=1
            i+=3

        result=Quality(act,T)
        if (Q >= 0 and result < Q)or(Q < 0):
            Q=result
            ans=act
    print("Wynik:")
    a=0
    while a<len(ans):
        print("{",end="")
        b=0
        while b<len(ans[a]):
            print(str(ans[a][b]),end="")
            if b+1<len(ans[a]):
                print(",",end="")
            b+=1
        a+=1
        print("}")
    print("Jakosc: "+str(Q))
    print("Iteracje: "+str(X))
t=time.time() - start_time
file.write(str(t))
file.write("\n")
file.close()


