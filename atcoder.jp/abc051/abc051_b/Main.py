K, S = map(int, input().split())


cnt = 0
for z in range(K+1):
    for y in range(K+1):
        x = S-z-y
        if x >= 0 and x <= K:
            cnt = cnt + 1

print(cnt)