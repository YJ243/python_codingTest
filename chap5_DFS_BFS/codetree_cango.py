'''
2023.09.12
틀린이유 1: 범위 체크할 때 ny < 0 이 아니라 nx<0을 중복해서 작성함
'''

from collections import deque

# n*n 격자, k개의 시작점
n, k = map(int, input().split())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

# 0은 이동 가능, 1은 이동 X

dx = [0,1,0,-1]
dy = [1,0,-1,0]

def dfs(x,y):
    q = deque()
    q.append((x,y))
    visited[x][y] = True
    count = 1
    
    while q:
        a,b = q.popleft()
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                continue
            if visited[nx][ny]:
                continue
            if graph[nx][ny] == 1:
                continue
            
            count += 1
            q.append((nx,ny))
            visited[nx][ny] = True
    return count

result = 0

for i in range(k):
    a, b = map(int, input().split())
    
    if not visited[a-1][b-1]:
        result += bfs(a-1, b-1)

print(result)