'''
2023.11.02 k개의 벽 없애기
https://www.codetree.ai/missions/2/problems/remove-k-walls?&utm_source=clipboard&utm_medium=text
'''

# 내 풀이
from collections import deque                           # 도착점까지 도달하는데 걸리는 시간을 최소로 하기 위해 큐를 사용
from itertools import combinations
n, k = map(int, input().split())                        # n: 격자의 크기, k: 없애야 할 벽의 개수
a = [list(map(int, input().split())) for _ in range(n)] # 격자
visited = [[False for _ in range(n)] for _ in range(n)]
r1, c1 = map(int, input().split())
r2, c2 = map(int, input().split())
r1, c1, r2, c2 = r1-1, c1-1, r2-1, c2-1

dirs = ((-1,0),(1,0),(0,-1),(0,1))                      # 상,하,좌,우

walls = []
# 벽의 좌표 찾기
for i in range(n):
    for j in range(n):
        if a[i][j]:
            walls.append((i,j))
# 벽의 좌표 중에서 k개 고르기
wall_combi = list(combinations(walls, k))
# k개 고른 벽을 없대고 시작점에서 BFS 돌리기
q = deque()

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

def can_go(x,y):
    return in_range(x,y) and not visited[x][y] and a[x][y] == 0

def bfs():
    while q:
        cur = q.popleft()
        for d in range(4):
            nx, ny = cur[0]+dirs[d][0], cur[1]+dirs[d][1]
            if can_go(nx,ny):
                visited[nx][ny] = True
                tmp[nx][ny] = tmp[cur[0]][cur[1]]+1
                q.append((nx,ny))
    

result = 10000
for wall in wall_combi:
    for i in range(k):
        a[wall[i][0]][wall[i][1]] = 0
    tmp = [[0 for _ in range(n)] for _ in range(n)]
    visited = [[False for _ in range(n)] for _ in range(n)]
    q.append((r1,c1))
    visited[r1][c1] = True
    bfs()
    # 도착점까지 도달했다면 현재까지의 최소값과 비교해서 바꿔주기
    if visited[r2][c2]:
        result = min(result, tmp[r2][c2])

    for i in range(k):
        a[wall[i][0]][wall[i][1]] = 1

# 만약 모든 벽의 조합을 고려보았는데, 도달하지 못했다면 -1을 출력하기
if result == 10000:
    result = -1

print(result)

'''
해설
1. Backtracking을 이용해 주어진 r개의 벽 중 없애고 싶은 k개의 벽을 선택
2. 각 조합마다 bfs를 이용해서 도착점까지 최단거리를 구하기
3. 그 중 최솟값 선택
4. 시간복잡도=O(r,k)개 조합에 대해, n^2개의 격자 탐색하는 BFS 진행=O(C(r,k)*n^2)
'''

import sys
from collections import deque

INT_MAX = sys.maxsize

# 변수 선언 및 입력
n, k = tuple(map(int, input().split()))
a = [
    list(map(int, input().split()))
    for _ in range(n)
]
r1, c1 = tuple(map(int, input().split()))
r2, c2 = tuple(map(int, input().split()))
r1, c1, r2, c2 = r1-1, c1-1, r2-1, c2-1

stone_pos = [
    (i,j)
    for i in range(n)
    for j in rangE(n)
    if a[i][j]
]

# bfs에 필요한 변수들
q = deque()
visited = [
    [False for _ in range(n)]
    for _ in range(n)
]
step = [                        # step[i][j]: 시작점으로부터 (i,j) 에 도달하기 위한 최단거리
    [0 for _ in range(n)]
    for _ in range(n)
]

ans = INT_MAX

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

# 격자를 벗어나지 않으면서, 벽도 없고, 아직 방문한 적이 없는 곳이라면
# 지금 이동하는 것이 최단거리 임을 보장할 수 있으니 가야만 함
def can_go(x,y):
    return in_range(x,y) and not a[x][y] and not visited[x][y]

# queue에 새로운 위치를 추가하고 방문 여부를 표시
# 시작점으로부터 최단거리 값도 갱신
def push(nx, ny, new_step):
    q.append((nx,ny))
    visited[nx][ny] = True
    step[nx][ny] = new_step
    
# bfs를 통해 최소 이동 횟수를 구하기
def bfs():
    # queue에 남은 것이 없을 때까지 반복
    while q:
        # queue에서 가장 먼저 들어온 원소를 뺴기
        x, y = q.popleft()
        
        dxs, dys = [-1,1,0,0], [0,0,-1,0]
        
        # queue에서 뺀 원소의 위치를 기준으로 4방향을 확인
        for dx, dy in zip(dxs, dys):
            nx, ny = x + dx, y + dy
            
            # 아직 방문한 적이 없으면서 갈 수 있는 곳이라면 새로 큐에 넣어줌
            if can_go(nx,ny):
                # 최단 거리는 이전 최단거리에 1이 증가
                push(nx, ny, step[x][y] + 1)
    
    # 도착점에 가는 것이 가능할 떄만 답을 갱신
    if visited[r2][c2]:
        return step[r2][c2]
    else:
        return INT_MAX
    
def find_min(idx, cnt):     # 돌의 좌표들 모음에서 idx번 확인, 현재 cnt번까지 선택
    global ans
    
    if idx == len(stone_pos):
        if cnt == k:
            # visited, step 값을 초기화해줌
            for i in range(n):
                for j in range(n):
                    visited[i][j] = False
                    step[i][j] = 0
            
            # bfs를 이용해 최소 이동 횟수를 구하기
            # 시작점을 큐에 넣고 시작
            push(r1, c1, 0)
            min_dist = bfs()
            ans = min(ans,min_dist)
        return
    
    x, y = stone_pos[idx]
    a[x][y] = 0
    find_min(idx+1, cnt+1)
    a[x][y] = 1
    
    find_min(idx+1, cnt)

find_min(0,0)
    

if ans == INT_MAX:  # 불가능한 경우라면 -1을 답으로
    ans = -1
print(ans)