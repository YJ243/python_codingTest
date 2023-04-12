n, m = map(int, input().split())
x, y, d = map(int, input().split())

answer = 0

d = [[0]*m for _ in range(n)]
d[x][y] = 1

array = []
for i in range(n):
    array.append(list(map(int, input().split())))

# ºÏ, µ¿, ¼­