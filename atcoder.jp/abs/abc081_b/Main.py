N = int(input())

A = [int(s) for s in input().split()]
cnt_list = [0 for _ in range(N)]

for i in range(N):
    cnt = 0
    while A[i] % 2 == 0:
        A[i] = A[i] / 2
        cnt = cnt + 1
    cnt_list[i] = cnt

print(min(cnt_list))