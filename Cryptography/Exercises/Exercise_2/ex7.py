import sys
from sympy.ntheory.factor_ import totient as phi

sys.setrecursionlimit(4000)

## a^^b mod m
def hyperexp(a, b, m):
    if(b == 1): return a % m
    return pow(a, hyperexp(a, b - 1, phi(m)), m)
    
print(hyperexp(1707, 1782, 10**17))

## 70080500540924243

