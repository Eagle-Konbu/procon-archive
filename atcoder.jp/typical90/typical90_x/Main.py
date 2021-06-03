N, K = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))

dif = sum(abs(a-b) for a, b in zip(A, B))
if dif > K or dif % 2 != K % 2:
    print("No")
else:
    print("Yes")
