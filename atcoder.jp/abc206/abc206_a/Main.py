from math import floor

N=int(input())

if floor(N*1.08) < 206:
    print("Yay!")
elif floor(N*1.08) == 206:
    print("so-so")
else:
    print(":(")