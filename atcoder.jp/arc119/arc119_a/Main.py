from math import log2, inf

N = int(input())

min = inf
for b in range(int(log2(N))+1):
    a = int(N/(2**b))
    c = N-a*(2**b)
    if a+b+c < min:
        min = a+b+c
print(min)