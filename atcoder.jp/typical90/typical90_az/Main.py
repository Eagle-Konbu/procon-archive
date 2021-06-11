N = int(input())

A = [[0 for _ in range(6)] for _ in range(N)]

for i in range(N):
    A[i] = list(map(int, input().split()))

score = 1
for i in range(N):
    score = (score * sum(A[i])) % (10**9+7)
print(score)