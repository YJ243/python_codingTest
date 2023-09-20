'''
2023.09.15
문제는 한 번에 풀었는데 잦은 실수(k자리에 2를 박음, popleft() 빼먹음)로 시간 빼먹음
--> 코드 한 줄 한 줄 작성할 때 집중하자
'''
# 내 답안
from collections import deque
from itertools import combinations

n, k, u, d = map(int, input().split())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

max_city = 0
all_city = [(i,j) for i in range(n) for j in range(n)]
start_city = list(combinations(all_city, k))

dx = [-1,1,0,0]
dy = [0,0,-1,1]

def bfs(x,y):
    q = deque()
    go_cnt = 1
    visited[x][y] = True
    q.append((x,y))
    
    while q:
        a,b = q.popleft()
        
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            if nx < 0 or nx >= n or ny < 0 or ny >= n:
                continue
            if visited[nx][ny]:
                continue
            
            if graph[nx][ny] >= graph[a][b]:
                diff = graph[nx][ny] - graph[a][b]
            else:
                diff = graph[a][b] - graph[nx][ny]
            
            if u <= diff <= d:
                go_cnt += 1
                visited[nx][ny] = True
                q.append((nx, ny))
        return go_cnt
    
for combi in start_city:
    cnt = 0
    for i in range(n):
        for j in range(n):
            visited[i][j] = False
    
    for city in combi:
        cnt += bfs(city[0], city[1])
        
    if max_city < cnt:
        max_city = cnt
print(max_city)        