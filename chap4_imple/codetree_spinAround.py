'''
2023.10.04
빙빙 돌며 사각형 채우기
'''


# 내 풀이
n, m = map(int, input().split())
k = 1
d = 0
a = [[0 for _ in range(m)] for _ in range(n)]

dirs = ((0,1),(1,0),(0,-1),(-1,0)) # 오른쪽, 아래쪽, 왼쪽, 위쪽

def InRange(x,y):
    return 0 <= x and x < n and 0 <= y and y < m
x, y = 0,0
a[x][y] = 1

for i in range(2, n*m+1):
    nx, ny = x+ dirs[d][0], y+ dirs[d][1] # 현재 방향대로 진행
    if InRange(nx,ny) and a[nx][ny] == 0:
        # 범위 안에 있고, 아직 방문하지 않았으면
        pass
    else:
        # 범위 안에 없거나 방문한 곳에 다다르면
        d = (d+1)%4
        nx, ny = x+ dirs[d][0], y+dirs[d][1] # 방향 바꾸기
    
    x, y = nx, ny # 좌표 업데이트
    a[x][y] = i # 좌표에 값 업데이트

for i in range(n):
    for j in range(m):
        print(a[i][j], end = ' ')
    print()

# 해설

# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))
answer = [
    [0]*m
    for_ in range(n)
]

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < m

dxs, dys = [0,1,0,-1], [1,0,-1,0]
x, y = 0,0              # 시작은 (0,,0)
dir_num = 0             # 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽

# 처음 시작 위치에 초깃값 적음
answer[x][y] = 1

# n*m번 진행
for i in range(2, n*m+1):
    # 현재 방향 dir을 기준으로 그 다음 위치 값 계산
    nx, ny = x + dxs[dir_num], y + dys[dir_num]
    
    # 더 이상 나아갈 수 없다면 
    # 시계방향으로 90도 회전
    if not in_range(nx,ny) or answer[nx][ny] != 0:
        dir_num = (dir_num+1)%4
        
    # 그 다음 위치로 이동한 다음 배열에 올바른 값을 채워넣음
    x, y = nx, ny
    answer[x][y] = i

# 출력
for i in range(n):
    for j in range(m):
        print(answer[i][j], end=' ')
    print()