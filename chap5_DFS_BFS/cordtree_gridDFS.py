n, m = map(int, input().split())

graph = []
for i in range(n):
    graph.append(list(map(int, input().split())))
    
# 아래, 오른쪽 방향 정의
dx = [1,0]
dy = [0,1]

def dfs(x, y):
    for i in range(2):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx <0 or nx >= n or ny < 0 or ny >= m:
            continue
        if graph[nx][ny] == 0:
            continue
        
        if graph[nx][ny] == 1:
            graph[nx][ny] = graph[x][y]+1
            dfs(nx,ny)
            
dfs(0,0)
if graph[n-1][m-1] != 1:
    print(1)
else:
    print(0)