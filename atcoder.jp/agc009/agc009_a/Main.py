N = int(input())
A = [0 for _ in range(N)]
B = [0 for _ in range(N)]
D = [0 for _ in range(N)]
for i in range(N):
    A[i], B[i] = map(int, input().split())

cnt_sum = 0
for i in reversed(range(N)):
    A[i] = A[i] + cnt_sum
    if A[i] % B[i] != 0:
        press_cnt = B[i] - A[i] % B[i]
        cnt_sum = cnt_sum + press_cnt


print(cnt_sum)