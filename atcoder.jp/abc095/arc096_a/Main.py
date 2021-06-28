A, B, C, X, Y = map(int, input().split())

cnt_a = 0
cnt_b = 0
sum = 0
if A+B >= 2*C:
    cnt_c = 2*min(X, Y)

    sum = sum + C*cnt_c
    cnt_a = cnt_c / 2
    cnt_b = cnt_c / 2

if A <= 2*C:
    sum = sum + (X-cnt_a) * A
else:
    sum = sum + (X-cnt_a) * C * 2

if B <= 2*C:
    sum = sum + (Y-cnt_b) * B
else:
    sum = sum + (Y-cnt_b) * C * 2

print(int(sum))
