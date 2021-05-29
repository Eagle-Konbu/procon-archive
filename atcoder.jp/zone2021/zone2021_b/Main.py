import math


def angle(d, h):
    return math.atan(h/d)


N, D, H = map(int, input().split())
d = [0 for _ in range(N)]
h = [0 for _ in range(N)]

for i in range(N):
    d[i], h[i] = map(int, input().split())

H_list = [0]
for i in range(N):
    H_list.append(h[i]-d[i]*(H-h[i])/(D-d[i]))

print(max(H_list))