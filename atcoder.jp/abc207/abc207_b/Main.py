A, B, C, D = map(int, input().split())

cnt_blue = A
cnt_red = 0

cnt = 0

if B >= C*D:
    print(-1)
    exit()

while True:
    if cnt_blue <= cnt_red * D:
        print(cnt)
        exit()
    cnt_blue = cnt_blue + B
    cnt_red = cnt_red + C
    cnt = cnt + 1
