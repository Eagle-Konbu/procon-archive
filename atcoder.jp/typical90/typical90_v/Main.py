from math import gcd

a, b, c = map(int, input().split())

g = gcd(gcd(a, b), c)
if g == 1:
    print(a+b+c-3)
    exit()
print(int(a/g+b/g+c/g-3))
