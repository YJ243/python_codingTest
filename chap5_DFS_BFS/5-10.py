n, m = map(int, input().split())

model = [[0]*m for _ in range(n)]
# 2차원 리스트의 맵 정보 입력받기

graph = []
for i in range(n):
    graph.append(list(map(int, input().split())))


count = 0

# 특정 지점의 주변 상, 하, 좌, 우를 모두 살펴본 뒤 
# 주변 지점 중 값이 '0'이면서 아직 방문하지 않은 지점이 있으면 해당 지점 방문

# 방문한 지점에서 다시 상,하,좌,우 살펴보면서 방문 진행

# 1-2과정 방문하면서 방문하지 않은 지점의 수를 세기

visited = [[0]*m for _ in range(n)]

# dfs로 특정한 노드를 방문한 뒤에 연결된 모든 노드들도 방문
def dfs(x,y):
    # 주어진 범위를 벗어나는 경우 즉시 종료
    if x <= -1 or x >= n or y <= -1 or y >= m:
        return False
    # 현재 노드를 아직 방문하지 않았다면
    if graph[x][y] == 0:
        # 해당 노드 방문 처리
        graph[x][y] = 1
        # 상,하,좌,우 모두 재귀적으로 호출
        dfs(x-1, y)
        dfs(x+1, y)
        dfs(x, y-1)
        dfs(x, y+1)
        return True
    return False

# 모든 노드에 대해 음료수 채우기

result = 0
for i in range(n):
    for j in range(m):
        # 현재 위치에서 DFS 수행
        if dfs(i, j) == True:
            result += 1

print(result) # 정답 출력