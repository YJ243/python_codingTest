# bfs는 간선의 비용이 모두 같을 때 최단 거리를 탐색하기 위해 사용할 수 있는 알고리즘
# bfs는 시작 지점에서 가까운 노드부터 차례대로 그래프의 모든 노드를 탐색



from collections import deque
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

def bfs(x,y):
    
    queue = deque([(x,y)])
    visited[x][y] = True
    while queue:
        coordinate = queue.popleft()
        v, w = coordinate[0], coordinate[1]
        for i in range(4):
            nx = v + dx[i]
            ny = w + dy[i]
            if nx < 0 or nx >= n or ny < 0 or ny >= m:
                continue
            if visited[nx][ny]:
                continue
            if graph[nx][ny] == 0:
                continue
            if not visited[nx][ny] and graph[nx][ny]:
                visited[nx][ny]=True
                graph[nx][ny] = graph[v][w]+1
                queue.append([nx,ny])
                
    
bfs(0,0)
print(graph[n-1][m-1])