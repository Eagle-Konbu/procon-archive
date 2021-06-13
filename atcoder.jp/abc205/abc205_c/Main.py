A, B, C = map(int, input().split())

if C % 2 == 0:
    A, B = abs(A), abs(B)
elif A < 0 and B < 0:
    A, B = -B, -A

if A > B:
    print(">")
elif A == B:
    print("=")
else:
    print("<")
