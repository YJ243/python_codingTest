'''
2023.10.30
https://www.codetree.ai/missions/2/problems/escape-with-min-distance?&utm_source=clipboard&utm_medium=text
* 탈출 가능한 경로의 최단 거리를 출력
'''

from collections import deque
n, m = map(int, input().split())    # 변수 선언 및 입력
maze = [list(map(int, input().split())) for _ in range(n)]  # 뱀X: 1, 뱀o: 0 --> 1으로만 이동 가능
answer = [[0 for _ in range(m)] for _ in range(n)]          # 최단 거리를 담아놓는 배열, answer[i][j]: 시작점으로부터 (i,j) 지점에 도달하기 위한 최단거리
visited = [[False for _ in range(m)] for _ in range(n)]     # 방문 여부 기록

def push(x,y,k):        # answer[x][y]에 k를 적고 큐에 새로운 위치를 추가
    answer[x][y] = k    # 시작점으로부터 최단거리 값 갱신
    visited[x][y] = True# 방문 표시
    q.append((x,y))
    
def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < m 

# 격자를 벗어나지 않으면서, 아직 방문한 적이 없고, 뱀도 없다면
# 지금 이동하는 것이 최단거리임을 보장할 수 있음
def can_go(x,y):
    return in_range(x,y) and not visited[x][y] and maze[x][y] == 1

dirs = ((1,0),(0,1),(-1,0),(0,-1))

# bfs를 통해 최소 이동 횟수를 구하기
def bfs():
    while q:    # 큐에 남은 것이 없을 때까지 반복
        cur = q.popleft()   # 큐에 가장 먼저 들어온 원소를 빼기
        for i in range(4):  # 큐에서 뺀 원소의 위치를 기준으로 4방향을 확인
            nx, ny = cur[0] + dirs[i][0], cur[1] + dirs[i][1]
            if can_go(nx,ny):   # 아직 방문한 적이 없으면서 갈 수 있는 곳이라면 새로 큐에 넣어줌
                # 최단 거리는 이전 최단거리에 1이 증가
                push(nx, ny, answer[cur[0]][cur[1]]+1)      # 여기서 answer+1이 아니라 maze+1로 해서 잘못 출력함

q = deque()
push(0, 0, 0)
bfs()

if answer[n-1][m-1] == 0:
    print(-1)
else:
    print(answer[n-1][m-1])     # 처음에 maze를 출력해서 틀림