'''
2023.09.12
'''
# 내 답안
from collections import deque

n, m = map(int, input().split())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(m)]
    for _ in range(n)
]

dx = [0,1,0,-1]
dy = [1,0,-1,0]

def bfs(X,y):
    q = deque()
    q.append((x,y))
    visited[x][y] = True
    
    while q:
        a, b = q.popleft()
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                continue
            if visited[nx][ny]:
                continue
            if graph[nx][ny] == 0:
                continue
            
            visited[nx][ny] = True
            graph[nx][ny] = graph[a][b] + 1
            q.append((nx,ny))

bfs(0,0)

if graph[n-1][m-1] != 1:
    print(1)
else:
    print(0)
    

# 해설
from collections import deque

# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))

a = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(m)]
    for _ in range(n)
]

q = deque()

# 주어진 위치가 격자를 벗어나는지 여부를 반환함
def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < m

# 주어진 위치로 이동할 수 있는지 여부를 확인
def can_go(x,y):
    return in_range(x,y) and a[x][y] and not visited[x][y]

def bfs():
    # queue에 남은 것이 없을 때까지 반복
    while q:
        # queue에서 가장 먼저 들어온 원소를 뺌
        x, y = q.popleft()
        
        # queue에서 뺀 원소의 위치를 기준으로 4방향을 확인
        dxs, dys = [0,1,0,-1], [1,0,-1,0]
        for dx, dy in zip(dxs, dys):
            new_x, new_y = x + dx, y + dy
            
            # 아직 방문한 적이 없으면서 갈 수 있는 곳이라면
            # 새로 queue에 넣어주고 방문 여부를 표시
            if can_go(new_x, new_y):
                q.append((new_x, new_y))
                visited[new_x][new_y] = True

# bfs를 이용해 최소 이동 회수를 구함
# 시작점을 queue에 넣고 시작
q.append((0,0))
visited[0][0] = True

bfs()

# 우측 하단을 방문한 적이 있는지 여부를 출력
answer = 1 if visited[n-1][m-1] else 0
print(answer)