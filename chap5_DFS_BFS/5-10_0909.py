'''
date: 2023.09.09
name: Yejin
title: 음료수
'''

n, m = map(int, input().split())
graph=[]

for i in range(n):
    graph.append(list(map(int, input())))

# 이동할 방향 정의 (상,하,좌,우)
dx = [1,-1,0,0]
dy = [0,0,-1,1]

visited = [[False for _ in range(m)] for _ in range(n)]

# DFS로 특정한 노드를 방문한 뒤에 연결된 모든 노드들도 방문
def dfs(x,y):
    # 주어진 범위를 벗어나는 경우 즉시 종료
    if x <= -1 or x >= n or y <= -1 or y >= m:
        return False
    # 구멍이 뚫려있는 경우에
    #
    if graph[x][y] == 0:
        # 방문했다 표시
        visited[x][y] = True
    
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx < 0 or nx >=n or ny < 0 or ny >= m:
            continue
        if graph[nx][ny]:
            continue
        if visited[nx][ny]:
            continue
        if not visited[nx][ny]:
            print("dfs 탐색 중", nx, ny)
            dfs(nx,ny)
            print("dfs 탐색 끝", nx, ny)
            return True
        return True
    
    

result = 0
for i in range(n):
    for j in range(m):
        if dfs(i,j):
            print(i,j)
            print()
            result += 1
            
print(result)

# (1,2)인 경우