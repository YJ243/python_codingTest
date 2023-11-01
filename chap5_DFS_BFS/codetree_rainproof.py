'''
2023.10.31
내 풀이, 시간복잡도가 O(N^4)임 -> 최적화 필요
'''

from collections import deque

n, h, m = map(int, input().split())         # n: 격자 크기, h: 사람 명수, m: 비를 피할 수 있는 공간
a = [                                       # 격자
    list(map(int, input().split()))
    for _ in range(n)                       # 0: 이동 가능, 1: 벽이어서 이동 x, 2: 사람, 3: 비를 피할 수 있는 공간
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