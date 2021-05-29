N = int(input())
a = [int(s) for s in input().split()]

alice = 0
bob = 0

for i in range(N):
    target = max(a)
    if i % 2 == 0:
        alice = alice + target
    else:
        bob = bob + target
    a.remove(target)

print(alice - bob)