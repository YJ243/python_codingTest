VERTICES_NUM = 7
EDGES_NUM = 6

graph = [
    [0 for _ in range(VERTICES_NUM + 1)]
    for _ in range(VERTICES_NUM + 1)
]

visited = [False for _ in range(VERTICES_NUM + 1)]

def dfs(vertex):
    for curr_v in range(1, VERTICES_NUM+1):
        if graph[vertex][curr_v] and not visited[curr_v]: # 연결되어 있고, 방문하지 않았더라면
            print(curr_v) # 방문한 노드 출력
            visited[curr_v] = True # 방문했음
            dfs(curr_v) # 재귀로 돌기

start_points = [1,1,1,2,4,6]
end_points = [2,3,4,5,6,7]

# 연결되어 있는 노드 인접 행렬로 표시
for start, end in zip(start_points, end_points):
    graph[start][end] = 1
    graph[end][start] = 1

root_vertex = 1
print(root_vertex)
visited[root_vertex] = True
dfs(root_vertex)