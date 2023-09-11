'''
date: 2023.09.11
틀린이유 1: 메모리 초과
틀린이유 2: 출력형식: 가장 작은 K 출력 간과하고 지나감
틀린이유 3: 출력형식: 그때의 안전 영역의 수 인데,
안전 영역 안에 있는 집의 개수를 세어서 출력함
틀린이유 4: 인덱스는 1부터인데 0부터로 출력함


--> 출력부분을 잘 보고, 문제 잘 읽자
'''

import sys
sys.setrecursionlimit(10**5)

n, m = map(int, input().split())

graph = []
for i in range(n):
    graph.append(list(map(int, input().split())))

dx = [0,1,0,-1]
dy = [1,0,-1,0]

def dfs(x,y):
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        
        # 범위 벗어나면 패스
        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue
        # k보다 작거나 같으면 안전 영역 탐색 못하니 패스
        if graph[nx][ny] <= k:
            continue
        # 이미 방문했다면 패스
        if visited[nx][ny]:
            continue
        # k보다 크고 방문하지 않았다면
        if graph[nx][ny] > k and not visited[nx][ny]:
            # 하나 확보했으니 방문표시
            visited[nx][ny] = True # 방문 표시
            dfs(nx,ny) # 재귀로 DFS 탐색


comfort_zones = []
max_height = max(map(max, graph))

for k in range(1, max_height+1):
    visited = [
        [False for _ in range(m)]
        for _ in range(n)
    ]
    comfort_zone = 0 # k 바뀔 때마다 초기화
    for i in range(n):
        for j in range(m):
            if graph[i][j] > k and not visited[i][j]:
                # k보다 높이가 커서 안전 영역으로 탐색할 수 있고
                # 방문하지 않았다면
                visited[i][j] = True
                dfs(i,j)
                comfort_zone += 1
    
    comfort_zones.append(comfort_zone) # 끝나면 붙이기

max_comfort_zone = max(comfort_zones)
max_index = comfort_zones.index(max_comfort_zone)+1


## 해설
import sys
sys.setrecursionlimit(2500)

# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))
grid =[
    list(map(int, input().split()))
    for _ in range(n)
]

visited=[
    [False for _ in range(m)]
    for _ in range(n)
]

# visited 배열을 초기화해줌
def initialize_visited():
    for i in range(n):
        for j in range(m):
            visited[i][j] = False

# 주어진 위치가 격자를 벗어나는지 여부를 반환
def in_range(x, y):
    return 0 <= x and x < n and 0 <= y and y < m

# 주어진 위치로 이동할 수 있는지 여부를 확인 
def can_go(x, y):
    if not in_range(x,y):
        return False
    
    if visited[x][y] or grid[x][y] <= k:
        return False
    
    return True

def dfs(x,y,k):
    # 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽
    dxs, dys = [0,1,0,-1], [1,0,-1,0]
    
    # 네 방향 각각에 대해 DFS 탐색
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        
        if can_go(new_x, new_y, k):
            visited[new_x][new_y] = True
            dfs(new_x, new_y, k)
zone_num = 0
def get_zone_num(k):
    global 
    
    # 새로운 탐색을 시작한다는 의미로 zone_num를 0으로 갱신하고
    # visited 배열을 초기화해줌
    zone_num = 0
    initizlize_visited()
    
    # 격자의 각 위치에 대하여 탐색을 시작할 수 있는 경우
    # 해당 위치로부터 시작한 DFS 탐색을 수행
    for i in range(n):
        for j in range(m):
            if can_go(i,j,k):
                # 해당 위치를 탐색할 수 있는 경우 visited 배열을 갱신하고
                # 안전 영역을 하나 추가해줌
                visited[i][j] = True
                zone_num += 1
                dfs(i,j,k)
                
# 가능한 안전 영역의 최솟값이 0이므로 다음과 같이 초기화해줄 수 있음
max_zone_num = -1
answer_k = 0
max_height = 100

# 각 가능한 비의 높이에 대해 안전 영역의 수를 탐색
for k in range(1, max_height+1):
    get_zone_num(k)
    # 기존의 최대 영역의 수보다 클 경우 이를 갱신하고 인덱스 저장
    
    if zone_num > max_zone_num:
        max_zone_num, answer_k = zone_num, k
print(answer_k, max_zone_num)
    
    