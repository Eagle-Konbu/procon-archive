N = int(input())

red = []
blue = []

for i in range(N):
    a, b = map(int, input().split())
    red.append({
        "x": a,
        "y": b
    })
for i in range(N):
    c, d = map(int, input().split())
    blue.append({
        "x": c,
        "y": d
    })

cnt = 0
for b in sorted(blue, key=lambda x: x["x"]):
    candidate = [r for r in red if r["x"] < b["x"] and r["y"] < b["y"]]
    if len(candidate) > 0:
        red.remove(sorted(candidate, key=lambda x: x["y"])[-1])
        cnt = cnt + 1

print(cnt)
