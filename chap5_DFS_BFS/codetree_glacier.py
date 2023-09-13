'''
2023.09.14
'''
# 처음 작성하던 답


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
water_visited = [
    [False for _ in range(m)]
    for _ in range(n)
]
is_surrounded_water = [
    [False for _ in range(m)]
    for _ in range(n)
]
time = 0 # 빙하가 전부 녹는데 걸리는 시간
melt_cnt = 0 # 녹은 빙하의 크기, 맨 마지막 것을 답으로
meltable_list = [] # 매 초마다 초기화 하면서 각 시간별 녹일 수 있는 빙하 좌표 담기

dx = [-1,1,0,0]
dy = [0,0,-1,1]

#### 주목, 이제 check_water()만 하면 이 문제도 끝나는거야!!!!!
def check_water():
    # 이 함수는 0이 1로 둘러싸였는지 아닌지 체크
    # 만약 0이 1로 둘러싸였으면?--> is_surrounded_water를 True

    # step1: 연결요소 먼저 찾고
    # step2: 걔를 둘러싼 격자칸이 1인지 확인
    # 만약 둘러싼 격자칸이 1이다? 그럼 그 연결요소 모두 is_surrounded_water = True
    for i in range(1,n-1):
        for j in range(1, m-1):
            if graph[i][j] == 0

def bfs(x,y):
    global meltable_list
    meltable_list = []
    q = deque()
    visited[x][y] = True
    q.append((x,y))

    while q:
        a, b = q.popleft()
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]

            if nx < 1 or nx >= n-1 or ny < 1 or ny >= m-1:
                continue
            if visited[nx][ny]:
                continue
            if not graph[nx][ny]:
                continue


            # 여기서 중요한 건 상하좌우에 현재 탐색하는 1과 맞닿아 있는 0이 있는지
            
            # 그럼 여기서 또 dx dy 써야하는건가?
            # 현재 1인 좌표의 상하좌우 탐색함
            valid_stone = 0
            for i in range(4):
                nx_s = nx + dx[i]
                ny_s = ny + dy[i]
                if not graph[nx_s][ny_s] and not is_surrounded_water[nx_s][ny_s]:# 해당 돌이 1로 둘러싸이지 않았다면
                    valid_stone += 1
            # 그 맞닿아 있는 0이 있고, 그 0 중 하나라도 1로 둘러싸이지 않았다면 meltable_list에 넣기
            if valid_stone > 0:
                meltable_list.append((nx, ny))
            # 그리고 큐에 넣기
            visited[nx][ny] = True
            q.append((nx,ny))



# 모든 빙하가 녹을 때까지 반복
while 1:
    remain_ice = sum(graph, []).count(1)
    if remain_ice == 0:
        break
    melt_cnt = 0
    
    # 먼저 1로 둘러싸인 물이 있는지 확인
    for i in range(1,n-1):
        for j in range(1,m-1):
            if not graph[i][j] and not water_visited[i][j]:
        
    check_water()
    for i in range(1,n-1):
        for j in range(1, m-1):
            if graph[i][j] and not visited[i][j]:
                bfs(i,j) # bfs 탐색 돌기, 돌면서 확인하는데

    # 녹일 빙하 0으로 만들기/ 녹일 빙하 크기 melt_cnt에 담기
    
    for ice in meltable_list:
        a,b = ice
        graph[a][b] = 0
        melt_cnt += 1
    time += 1

print(time, melt_cnt)


## 최종 답
import sys
input = sys.stdin.readline
from collections import deque

n, m = map(int, input().split())

graph = [list(map(int, input().split())) for _ in range(n)]

dx = [-1,1,0,0]
dy = [0,0,-1,1]

'''
(0,0) 에서 시작해서 BFS 수행하면 외부에서 이어져 있는 물이니 빙하로 둘러싸인 
'''
# 격자 가장 바깥 부분의 외부 물부터 시작해서 상하좌우로 이동, 만나는 빙하를 녹임
# BFS를 계속 수행하면, 빙하 바깥쪽의 물에서 시작하여 빙하 내부의 물까지도 방문할 수 있음
# 빙하 내부의 물에 도달하면, 그 물은 빙하에 둘러싸인 물이 아니게 됨, 빙하로 막혀있다면 BFS를 통해 접근할 수 없었을 것이기 때문

def bfs():
    global graph
    # 매 초마다 새로운 graph에 대해 bfs 수행하니 visited도 초기화 시켜줌
    visited = [[False for _ in range(m)] for _ in range(n)]
    next_graph = [row.copy() for row in graph]
    
    q = deque()
    
    # 빙하에 둘러싸이지 않는 물 탐색
    q.append((0,0))
    visited[0][0] = True
    
    while q:
        x, y = q.popleft()
        for i in range(4):
            nx, ny = x + dx[i], y + dy[i]
            
            if 0 <= nx < n and 0 <= ny < m and not visited[nx][ny]:
                visited[nx][ny] = True
                if graph[nx][ny] == 1: # 만약 물과 맞닿아 있는 빙하라면
                    next_graph[nx][ny] = 0 # 녹이기
                else: # 만약 외부 물과 연결된 물이라면
                    q.append((nx,ny)) # 큐에 넣어서 이후에 맞닿아 있는 빙하 도달할 수 있도록 함
    return next_graph # 빙하가 녹은 후의 상태 반환

time = 0
while sum(map(sum,graph)) > 0 : # 빙하가 완전히 녹을 떄까지 (합이 0이 되면 break)
    melt_cnt = sum(map(sum,graph)) # 현재 빙하의 양
    graph = bfs() # 빙하 녹이고 나온 결과 
    time += 1 # 시간 증가

print(time, melt_cnt)