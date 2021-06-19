N = int(input())
A = list(map(int, input().split()))

duplicate_cnt = 0
A = sorted(A)
a_tmp = 0
cnt_tmp = 0

for a in A:
    if a != a_tmp:
        duplicate_cnt = duplicate_cnt + int(cnt_tmp*(cnt_tmp-1)/2)
        cnt_tmp = 0
        a_tmp = a
    cnt_tmp = cnt_tmp + 1
duplicate_cnt = duplicate_cnt + int(cnt_tmp*(cnt_tmp-1)/2)

all_cnt = int(N*(N-1)/2)
print(all_cnt-duplicate_cnt)