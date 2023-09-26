'''
date: 2023.09.05/2023.09.09
name: Yejin
title: 음료수
'''
## 1. 특정한 지점의 주변 상, 하, 좌, 우를 살펴본 뒤 0이면서 아직 방문하지 않은 지점이 있다면 해당 지점 방문
## 2. 방문한 지점에서 다시 상, 하, 좌, 우를 살펴보면서 방문을 진행 --> 연결된 모든 지점을 방문할 수 있음
## 3. 1~2를 모든 노드에서 반복

# N, M을 공백으로 입력받기
n, m = map(int, input().split())

# 2차원 리스트의 맵 정보 입력받기
graph = []

for i in range(n):
    graph.append(list(map(int, input())))

# DFS로 특정한 노드를 방문한 뒤에 연결된 모든 노드들도 방문
def dfs(x, y):
    if x <= -1 or x >= n or y <= -1 or y >= m:
        return False
    # 현재 노드를 아직 방문하지 않았다면
    if graph[x][y] == 0:
        # 해당 노드 방문 처리
        graph[x][y] = 1
        
        # 상, 하, 좌, 우의 위치도 모두 재귀적으로 호출
        dfs(x-1, y)
        dfs(x+1, y)
        dfs(x, y-1)
        dfs(x, y+1)
        return True
    # 현재 노드를 방문했거나 틀이 뚫려있지 않다면
    return False

# 모든 노드(위치)에 대하여 음료수 채우기
result = 0
for i in range(n):
    for j in range(m):
        # 현재 위치에서 DFS 수행
        if dfs(i, j) == True:
            result += 1
    

print(result)   