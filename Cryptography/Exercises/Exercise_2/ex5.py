def singleTest(a, n):
    return pow(a, n - 1, n) == 1

## a = 2
def fermat(n):
    a = 2
    ## return modexp(a, n - 1, n) == 1
    ## from Python's documentation: https://docs.python.org/3/library/functions.html#pow
    ## if mod is present, return base to the power exp, modulo mod (computed more efficiently than pow(base, exp) % mod
    print(f"{n} {('might be' if singleTest(a, n) else 'is not')} prime")

## (x ^ y) % p    
def modexp(x, y, p):
    res = 1
    
    x %= p
    if(x == 0): return 0
    
    while(y > 0):
        if(y % 2 == 1): res = (res * x) % p
        
        y /= 2
        x = (x ** 2) % p
        
    return res

    
fermat(67280421310721)
fermat(170141183460469231731687303715884105721)
fermat(pow(2, 2281) - 1)
fermat(pow(2, 9941) - 1)
fermat(pow(2, 19939) - 1)
