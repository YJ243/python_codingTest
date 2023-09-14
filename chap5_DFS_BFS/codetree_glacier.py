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

## 해설
'''
빙하가 녹을 조건: 인접한 곳에 빙하에 둘러싸여 있지 않은 물이 있는 경우
(0,0)을 시작점으로 BFS 돌리면 빙하에 둘러싸이지 않은 물의 영역 구할 수 있음
'''

from collections import deque
import enum

class Element(enum.Enum):
    WATER = 0
    GLACIER = 1
    

# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))

a = [
    list(map(int, input().split()))
    for _ in range(n)
]

# bfs에 필요한 변수들
q = deque()
glaciers_to_melt = deque()

visited = [
    [False for _ in range(m)]
    for _ in range(n)
]

cnt = 0

# 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽
dxs, dys = [0,1,0,-1], [1,0,-1,0]

# 소요 시간과 가장 마지막으로 녹은 빙하의 수를 저장
elapsed_time = 0
last_melt_cnt = 0

# 주어진 위치가 격자를 벗어나는지 여부를 반환
def in_range(x,y):
    return 0 <= x < n and 0 <= y < m

# 범위를 벗어나지 않으면서 물이어야 하고 방문한 적이 없어야 갈 수 있음
def can_go(x,y):
    return in_range(x,y) and a[x][y] == Element.WATER.value and not visited[x][y]

def is_glacier(x,y):
    return in_range(x,y) and a[x][y] == Element.GLACIER.value and not visited[x][y]

# visited 배열을 초기화
def initialize():
    for i in range(n):
        for j in range(m):
            visited[i][j] = False
            
# 빙하에 둘러싸여 있지 않은 물을 전부 구해주는 BFS
# 문제에서 가장자리는 전부 물로 주어짐
# 따라서 항상 (0,0)에서 시작하여 탐색을 진행하면
# 빙하에 둘러싸여 있지 않은 물들은 전부 visited 처리가 됨

def bfs():
    # BFS 함수가 여러 번 호출되므로
    # 사용하기 전 visited 배열을 초기화해줌
    initialize()
    
    # 항상 (0,0)에서 시작
    q.append((0,0))
    visited[0][0] = True
    
    while q:
        # queue에서 가장 먼저 들어온 원소를 뺌
        x, y = q.popleft()
        
        # queue에서 뺸 원소의 위치를 기준으로 네 방향을 확인
        for dx, dy in zip(dxs, dys):
            new_x, new_y = x + dx, y + dy
            
            
            # 더 갈 수 있는 곳이면 queue에 추가
            if can_go(new_x, new_y):
                q.append((new_x, new_y))
                visited[new_x][new_y] = True
                
    
# 현재 위치를 기준으로 인접한 영역에
# 빙하에 둘러싸여 있지 않은 물이 있는지 판단
def outside_water_exist_in_neighbor(x,y):
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        
        if in_range(new_x, new_y) and visited[new_x][new_y]:
            return True
    return False


# 인접한 영역에 빙하에 둘러싸여 있지 않은 물이 있는 빙하를 찾아 녹여줌
def melt():
    global last_melt_cnt
    
    for i in range(n):
        for j in range(m):
            if a[i][j] == Element.GLACIER.value and \
                outside_water_exist_in_neighbor(i,j):
                a[i][j] = Element.WATER.value
                last_melt_cnt += 1

# 빙하를 한 번 녹임
def simulate():
    global elapsed_time, last_melt_cnt
    
    elapsed_time += 1
    last_melt_cnt = 0
    
    # 빙하에 둘러싸여 있지 않은 물의 위치를 전부 visited 로 체크
    bfs()
    
    # 인접한 영역에 빙하에 둘러싸여 있지 않은 물이 있는 빙하를 찾아 녹임
    melt()
    
# 빙하가 아직 남아 있는지 확인
def glacier_exist():
    for i in range(n):
        for j in range(m):
            if a[i][j] == Element.GLACIER.value:
                return True
    return False

while True:
    simulate()
    
    # 빙하가 존재하는 한 계속 빙하를 녹임
    if not glacier_exist():
        break
print(elapsed_time, last_melt_cnt)