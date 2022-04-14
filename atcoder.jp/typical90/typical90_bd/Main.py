n, s = map(int, input().split())
a, b = [0], [0]

for _ in range(n):
    a_tmp, b_tmp = map(int, input().split())
    a.append(a_tmp)
    b.append(b_tmp)

dp_a = [[False for _ in range(s + 1)] for _ in range(n + 1)]
dp_b = [[False for _ in range(s + 1)] for _ in range(n + 1)]

dp_a[0][0] = True
dp_b[0][0] = True

for i in range(1 ,n + 1):
    for j in range(1, s + 1):
        if j - a[i] >= 0:
            dp_a[i][j] = dp_a[i - 1][j - a[i]] or dp_b[i - 1][j - a[i]]
        if j - b[i] >= 0:
            dp_b[i][j] = dp_a[i - 1][j - b[i]] or dp_b[i - 1][j - b[i]]

ans = ""

s_tmp = s

for i in reversed(range(1, n + 1)):
    if dp_a[i][s_tmp]:
        ans = ans + "A"
        s_tmp = s_tmp - a[i]
    elif dp_b[i][s_tmp]:
        ans = ans + "B"
        s_tmp = s_tmp - b[i]
    else:
        print("Impossible")
        exit()

print(ans[::-1])