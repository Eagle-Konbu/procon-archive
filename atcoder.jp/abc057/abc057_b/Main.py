import math

N, M = map(int, input().split())

student_list = []
point_list = []

for _ in range(N):
    a, b = map(int, input().split())
    student_list.append((a, b))

for _ in range(M):
    c, d, = map(int, input().split())
    point_list.append((c, d))

idx_list = [0]*N
for i in range(N):
    idx = 0
    distance = math.inf
    for j in range(M):
        d = math.fabs(point_list[j][0]-student_list[i][0]) + \
            math.fabs(point_list[j][1]-student_list[i][1])
        if d < distance:
            idx = j + 1
            distance = d
    idx_list[i] = idx

for i in idx_list:
    print(i)