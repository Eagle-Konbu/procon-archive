N = int(input())
A = list(map(int, input().split()))

arr = [False for _ in range(N)]

for a in A:
    if arr[a-1] is True:
        print("No")
        exit()
    arr[a-1] = True

print("Yes")