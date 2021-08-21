from itertools import permutations

s,k_str=input().split()

k=int(k_str)

list = sorted(list(set([''.join(p) for p in permutations(s)])))

print(list[k-1])