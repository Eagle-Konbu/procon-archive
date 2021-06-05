N = int(input())
job_list = []
for _ in range(N):
    A, B = map(int, input().split())
    job_list.append({
        "duration": A,
        "due": B
    })

job_list.sort(key=lambda x: x["due"])

t = 0
for job in job_list:
    t = t + job["duration"]
    if t > job["due"]:
        print("No")
        exit()

print("Yes")
