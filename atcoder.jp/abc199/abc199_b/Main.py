from math import inf

N = int(input())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

x_min, x_max = 0, inf

for i in range(N):
    if A[i] > x_min:
        x_min = A[i]
    if B[i] < x_max:
        x_max = B[i]

print(max(0, x_max-x_min+1))
