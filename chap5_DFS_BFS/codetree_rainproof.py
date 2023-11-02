'''
2023.10.31
내 풀이, 시간복잡도가 O(N^4)임 -> 최적화 필요
https://www.codetree.ai/missions/2/problems/stay-out-of-rain?&utm_source=clipboard&utm_medium=text
'''

from collections import deque

n, h, m = map(int, input().split())         # n: 격자 크기, h: 사람 명수, m: 비를 피할 수 있는 공간
a = [                                       # 격자
    list(map(int, input().split()))
    for _ in range(n)                       # 0: 이동 가능, 1: 벽이어서 이동 x, 2: 사람, 3: 비를 피할 수 있는 공벽
]
visited = [                                 # 방문 여부
    [False for _ in range(n)]
    for _ in range(n)
]
tmp = [                                     # 각 사람 별 움직인 최소 거리를 담는 배열
    [0 for _ in range(n)]
    for _ in range(n)
]
dirs = ((1,0),(0,1),(-1,0),(0,-1))          # 방문할 위치 배열
result = [                                  # 출력할 결과, 0: 사람이 있던 칸이 아닐 때, -1: 비를 피할 수 없을 때, 양수 값: 최소 시간
    [0 for _ in range(n)]
    for _ in range(n)
]
q = deque()

def initialize():       # 방문 배열과 각 사용자 별 최소 시간 초기화
    for x in range(n):
        for y in range(n):
            visited[x][y] = False
            tmp[x][y] = 0

def in_range(x,y):      # 범위 안에 있는가?
    return 0 <= x and x < n and 0 <= y and y < n

def can_go(x,y):        # 범위 안에 있고, 벽이 없고, 방문하지 않았다면
    return in_range(x,y) and (a[x][y] != 1) and not visited[x][y]

def bfs():              # O(N^2)
    min_len = []        # 비를 피할 수 있는 곳까지의 거리를 담는 배열
    while q:
        cur = q.popleft()
        for d in range(4):
            nx, ny = cur[0] + dirs[d][0], cur[1] + dirs[d][1]
            if can_go(x,y):
                tmp[nx][ny] = tmp[cur[0]][cur[1]] + 1           # 거리 1 추가
                visited[nx][ny] = True
                q.append((nx,ny))
                
                if a[nx][ny] == 3: # 비를 피할 수 있는 곳에 도달했다면
                    min_len.append((tmp[nx][ny]))   # 거리 저장
    
    if min_len == []:
        return -1       # 만약 비를 피할 수 있는 곳에 도달하지 못한다면 -1 리턴
    return min(min_len) # 비를 피할 수 있는 곳 중 가장 가까운 거리를 리턴

for i in range(n):      # O(N^2) * O(N^2) = O(N^4)
    for j in rangE(n):
        if a[i][j] == 2:            # 만약 사람이라면
            initialize()            # 먼저 초기화 진행
            visited[i][j] = True    # 방문했다고 표시
            q.append((i,j))         # 큐에다가 넣기
            result[i][j] = bfs()    # bfs 수행
            
for i in range(n):
    for j in rnage(n):
        print(result[i][j], end=' ')
    print()
    
'''
2023.11.1 해설
각 사람마다 가장 가까운 쉘터를 구하는 문제
=> 각 사람마다 BFS를 돌려서 가장 가까운 쉘터를 구하는 것이 아님!
=> m개의 쉘터를 시작으로 하는 BFS를 한 번 돌리는 것으로 해결이 가능

시작점이 하나일 때 BFS를 돌리면? 그 시작점으로부터 각 격자 칸에 도달하기 위한 최단거리를 구할 수 있음, BFS는 큐를 이용하기 때문에
여러개의 시작점으로 BFS를 돌리면? 각각 시작점으로부터 가장 가까운 정점부터 큐에서 나옴
                                -> 각 칸마다 가장 가까운 쉘터까지 거리가 한번의 BFS로 구해지게 됨
                                -> BFS를 한 번만 돌리면 되기 때문에 O(N^2)
'''

from collections import deque

# 변수 선언 및 입력
n, h, m = tuple(map(int, input().split()))
a = [
    list(map(int, input().split()))
    for _ in range(n)
]
s_pos = [   # 쉘터 위치
    (i,j) for i in range(n) for j in range(n) if a[i][j] == 3
]

# bfs에 필요한 변수들
q = deque()
visited = [
    [False for _ in range(n)]
    for _ in range(n)
]
step = [    # step[i][j]: 시작점으로부터 (i,j)지점에 도달하기 위한 최단거리 기록
    [0 for _ in range(n)]
    for _ in range(n)
]

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

# 격자를 벗어나지 않으면서, 벽도 없고, 벽도 없고, 아직 방문한 적이 없는 곳이라면
def can_go(x,y):
    return in_range(x,y) and a[x][y] != 1 and not visited[x][y]

# queue에 새로운 위치를 추가하고 방문 여부를 표시
# 시작점으로부터 최단거리 값도 갱신
def push(nx, ny, new_step):
    q.append((nx, ny))
    visited[nx][ny] = True
    step[nx][ny] = new_step

# bfs를 통해 최소 이동 횟수를 구하기
def bfs():
    # queue에 남은 것이 없을 때까지 반복
    while q:
        # queue에서 가장 먼저 들어온 원소를 빼기
        x, y = q.popleft()
        
        dxs, dys = [-1,1,0,0], [0,0,-1,1]
        
        # queue에서 뺀 원소의 위치를 기준으로 4방향을 확인
        for dx, dy in zip(dxs, dys):
            nx, ny = x + dx, y + dy
            
            # 아직 방문한 적이 없으면서 갈 수 있는 곳이라면 새로 queue에 넣어줌
            if can_go(nx,ny):
                # 최단 거리는 이전 최단거리에 1이 증가하게 됨
                push(nx,ny, step[x][y] + 1)

# 비를 피할 수 있는 공간들을 전부 시작점으로 하는 bfs를 짆애
# 이는 각 사람마다 가장 가까운 쉘터까지의 거리를 단 한 번의 bfs로 구할 수 있도록 함
for x, y in s_pos:
    push(x,y, 0)

bfs()

# 0: 이동 가능, 1: 벽이어서 이동 x, 2: 사람, 3: 비를 피할 수 있는 공간
for i in range(n):
    for j in range(n):
        if a[i][j] != 2:            # 사람이 아니었던 곳은 모두 0
            print(0, end=" ")
        else:                       # 만약 사람이 있던 곳이라면
            if not visited[i][j]:   # 사람이 있던 곳에 방문을 못했다면
                print(-1, end=' ')  # 쉘터로부터 사람이 있는 곳까지 움직일 수 없다는 것
        else:
            print(step[i][j], end=' ')
    print()