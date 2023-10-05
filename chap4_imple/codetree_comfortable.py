'''
2023.10.05
'''

# 내 풀이
n, m = map(int, input().split())
a=[[0 for _ in range(n)]for _ in range(n)]

dirs = ((0,1),(1,0),(0,-1),(-1,0))

for i in range(m):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    a[x][y] = 1
    cnt = 0
    for j in range(4):
        nx, ny = x + dirs[j][0], y + dirs[j][1]
        if nx < 0 or nx >= n or ny < 0 or ny >= n: continue
        if a[x+dirs[j][0]][y+dirs[j][1]]:
            cnt += 1
    if cnt == 3: 
        print(1)
    else:
        print(0)


# 해설
# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))
arr =[
    [0]*n
    for _ in range(n)
]

dxs = [0,1,0,-1]
dys = [1,0,-1,0]

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

def adjacent_cnt(x,y):
    cnt = 0
    for dx, dy in zip(dxs, dys):
        nx, ny = x + dx, y + dy
        if in_range(nx,ny) and arr[nx][ny] == 1:
            cnt += 1
    return cnt

for _ in range(m):
    x, y = tuple(map(int, input().split()))
    x -= 1
    y -= 1
    arr[x][y] = 1
    
    # 해당 칸을 탐색
    if adjacent_cnt(x,y) == 3:
        print(1)
    else:
        print(0)