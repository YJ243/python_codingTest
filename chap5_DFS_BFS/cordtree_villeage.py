'''
date: 2023.09.10
name: Yejin
title: classify villeage
'''

n = int(input())

graph = []

for _ in range(n):
    graph.append(list(map(int, input().split())))

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]    
dx = [-1,1,0,0]
dy = [0,0,-1,1]

people_in_villeage = 0
def dfs(x,y):
    people_in_villeage = 1 # 현재 마을의 사람 수를 저장할 변수
    
    visited[x][y] = True
    
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx < 0 or nx >= n or ny < 0 or ny >= n:
            continue
        if not graph[nx][ny]:
            continue
        
        if not visited[nx][ny] and graph[nx][ny]:
            visited[nx][ny] = True
            people_in_villeage += dfs(nx,ny) # 인접한 마을의 사람 수를 더함
            
    return people_in_villeage # 현재 마을의 사람 수 반환
            
# 각 마을의 사람 수를 담을 리스트
people = []

# 마을 개수
villeage_count = 0
for i in range(n):
    for j in range(n):
        if graph[i][j] == 1 and not visited[i][j]:
            people_in_villeage = dfs(i, j) # dfs로 돌았다면
            villeage_count += 1
            people.append(people_in_villeage)

people.sort()
print(villeage_count)
for p in people:
    print(p)