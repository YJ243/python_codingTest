'''
2023.09.12
틀린이유 1: 범위 체크할 때 ny < 0 이 아니라 nx<0을 중복해서 작성함
'''

from collections import deque

# n*n 격자, k개의 시작점
n, k = map(int, input().split())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

# 0은 이동 가능, 1은 이동 X

dx = [0,1,0,-1]
dy = [1,0,-1,0]

def dfs(x,y):
    q = deque()
    q.append((x,y))
    visited[x][y] = True
    count = 1
    
    while q:
        a,b = q.popleft()
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                continue
            if visited[nx][ny]:
                continue
            if graph[nx][ny] == 1:
                continue
            
            count += 1
            q.append((nx,ny))
            visited[nx][ny] = True
    return count

result = 0

for i in range(k):
    a, b = map(int, input().split())
    
    if not visited[a-1][b-1]:
        result += bfs(a-1, b-1)

print(result)


## 해설
'''
시작점이 여러 개인 경우의 bfs탐색 --> 처음 queue에 모든 시작점을 집어 넣고 시작

- dfs: 특정 위치 한 곳을 기준으로 진행-> 각 시작점에 대해 각각 탐색을 진행해야 함
- bfs: queue라는 자료구조를 이용해 현재 방문한 위치를 여러 곳 담을 수 있음
--> 시작점이 여러 개인 경우 초기 queue에 시작점을 전부 집어 넣고 시작
'''

from collections import deque

# 변수 선언 및 입력:
n, k = tuple(map(int, input().split()))

grid = [
    list(map(int, input().split()))
    for _ in range(n)
]

# bfs에 필요한 변수들
bfs_q = deque()
visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

def can_go(x,y):
    return in_range(x,y) and not grid[x][y] and \
        not visited[x][y]

def bfs():
    # queue에 남은 것이 없을 때까지 반복
    while bfs_q:
        # queue에서 가장 먼저 들어온 원소를 뺌
        x, y = bfs_q.popleft()
        
        dxs, dys = [1,-1,0,0], [0,0,1,-1]
        
        # queue에서 뺸 원소의 위치를 기준으로 4방향 확인 
        for dx, dy in zip(dxs, dys):
            nx, ny = x + dx, y + dy
            
            # 아직 방문한 적이 없으면서 갈 수 있는 곳이면
            # 새로 queue에 넣어주고 방문 여부를 표시
            if can_go(nx,ny):
                bfs_q.append((nx,ny))
                visited[nx][ny] = True
                
# 시작점을 모두 bfs queue에 넣음
for _ in range(k):
    x, y = tuple(map(int, input().split()))
    bfs_q.append((x-1,y-1))
    visited[x-1][y-1] = Ture
    
# bfs를 진행
bfs()

# list comprehension 이용!!
ans = sum([
    1
    for i in range(n)
    for j in range(n)
    if visited[i][j]
])

print(ans)
    
