A, V = map(int, input().split())
B, W = map(int, input().split())
T = int(input())

distance = abs(B-A)

if V <= W:
    print("NO")
    exit()

if distance / (V-W) <= T:
    print("YES")
else:
    print("NO")