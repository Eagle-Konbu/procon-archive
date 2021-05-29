S=input()

num_list = [int(s) for s in S]

for i in range(len(S)):
    el = num_list[i]
    if el == 6:
        num_list[i]=9
    elif el == 9:
        num_list[i]=6
num_list.reverse()
for s in num_list:
    print(s, end="")
print("")