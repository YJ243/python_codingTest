## 2023.09.05 내풀이1
n, m = map(int, input().split())

graph = []
for i in range(n):
    graph.append(list(map(int, input().split())))
    
# 아래, 오른쪽 방향 정의
dx = [1,0]
dy = [0,1]

def dfs(x, y):
    for i in range(2):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx <0 or nx >= n or ny < 0 or ny >= m:
            continue
        if graph[nx][ny] == 0:
            continue
        
        if graph[nx][ny] == 1:
            graph[nx][ny] = graph[x][y]+1
            dfs(nx,ny)
            
dfs(0,0)
if graph[n-1][m-1] != 1:
    print(1)
else:
    print(0)
    
## 2023.09.10 내풀이2
n, m = map(int, input().split())
graph = []
for i in range(n):
    graph.append(list(map(int, input().split())))
    
dx = [1,0]
dy = [0,1]

visited = [
    [False for _ in range(m)]
    for _ in range(n)
]

def dfs(x,y):
    for i in range(2):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue
        if graph[nx][ny] == 0:
            continue
        if not visited[nx][ny]:
            dfs(nx,ny)
            
dfs(0,0)
if visited[n-1][m-1] == 1:
    print(1)
else:
    print(0)
 
 
## 2023.09.10 해설1
# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))
grid = [
    list(map(int, input().split()))
    for _ in range(n)
]

# 주어진 위치가 격자를 벗어나는지 여부를 반환
def in_range(x, y):
    return 0 <= x and x < n and 0 <= y and y < m

# 주어진 위치로 이동할 수 있는지 여부를 확인
def can_go(x, y):
    if not in_range(x,y):
        return False
    if visited[x][y] or grid[x][y] == 0:
        return False
    return True

def dfs(x,y):
    dxs, dys = [0,1], [1,0]
    
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        
        if can_go(new_x, new_y):
            visited[new_x][new_y] = 1
            dfs(new_x, new_y)

visited[0][0] = 1
dfs(0,0)

print(visited[n-1][m-1])


## 2023.09.10 해설2
# dfs 부분부터
def dfs(x,y):
    dxs, dys = [1,0], [0,1]
    
    # 탐색을 시작하기 전에 해당 위치를 방문했음을 표시
    visited[x][y] = 1
    
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        
        if can_go(new_x, new_y):
            dfs(new_x, new_y)
            
dfs(0,0)

print(visited[n-1][m-1])