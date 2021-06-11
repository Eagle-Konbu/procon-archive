Q = int(input())

arr = []

for i in range(Q):
    t, x = map(int, input().split())
    if t == 1:
        arr.insert(0, x)
    elif t == 2:
        arr.append(x)
    else:
        print(arr[x-1])