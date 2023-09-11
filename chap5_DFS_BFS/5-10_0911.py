'''
date: 2023.09.11
name: Yejin
title: 음료수 얼려먹기
'''

n, m = map(int, input().split())

graph = []
for i in range(n):
    graph.append(list(map(int, input())))
    

visited = [
    [False for _ in range(m)]
    for _ in range(n)
]
dx = [0,1,0,-1]
dy = [1,0,-1,0]

def dfs(x,y):
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue
        if visited[nx][ny]:
            continue
        if graph[nx][ny]:
            continue
        
        if not visited[nx][ny] and graph[nx][ny]==0:
            visited[nx][ny] = True
            dfs(nx,ny)
            
cnt = 0
for i in range(n):
    for j in range(m):
        if graph[i][j] == 0 and not visited[i][j]:
            visited[i][j] = True
            dfs(i,j)
            cnt += 1
print(cnt)
            
