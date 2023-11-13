'''
2023.11.02
https://www.codetree.ai/missions/2/problems/oranges-have-gone-bad?&utm_source=clipboard&utm_medium=text
k개의 상한 귤로부터 시작해서 1초에 한 번씩 모든 상한 귤로부터 인접한 귤이 동시에 전부 상하게 될 때,
각 귤마다 최초로 상하게 되는 시간을 구하는 프로그램
'''

# 내 풀이

from collections import deque

n, k = map(int, input().split())    # n개의 격자 칸, k개의 상한 귤
a = [list(map(int, input().split())) for _ in range(n)] # 격자 정보
visited = [[False for _ in range(n)] for _ in range(n)]

result = [[-1 for _ in range(n)] for _ in range(n)]

q = deque()

rotten = [
    (i,j)
    for i in range(n)
    for j in range(n)
    if a[i][j] == 2
]

q=deque()

dirs = ((1,0),(0,1),(-1,0),(0,-1))

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

def can_go(x,y):
    return in_range(x,y) and not visited[x][y] and a[x][y] == 1

def bfs():
    while q:
        x,y = q.popleft()
        for i in range(4):
            nx, ny = x + dirs[i][0], y+dirs[i][1]
            if can_go(nx,ny):   # 만약 범위 안에 있고 ,방문하지 않았고, 귤이 놓여있다면
                result[nx][ny] = result[x][y] + 1
                visited[nx][ny] = True
                q.append((nx,ny))

for rot in rotten:
    visited[rot[0]][rot[1]] = True
    q.append((rot[0], rot[1]))
    result[rot[0]][rot[1]] = 0

bfs()

for i in range(n):
    for j in range(n):
        if a[i][j] != 0 and not visited[i][j]:
            result[i][j] = -2

for i in range(n):
    for j in range(n):
        print(result[i][j], end=' ')
    print()
    
'''
해설 풀이, BFS를 한 번만 돌리면 되기 떄문에 O(N^2)
'''