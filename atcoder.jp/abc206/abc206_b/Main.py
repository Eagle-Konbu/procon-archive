N=int(input())

day = 1
sum = 0
while True:
    sum = sum + day
    if sum >= N:
        print(day)
        exit()
    day = day + 1