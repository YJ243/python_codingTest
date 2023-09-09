# 인접 행렬로 그래프 표현하기
# 1-2, 1-3, 1-4, 2-5, 4-6, 6-7
start_points = [1,1,1,2,4,6]
end_points = [2,3,4,5,6,7]

VERTICES_NUM = 7
EDGES_NUM = 6

graph = [
    [0 for _ in range(VERTICES_NUM + 1)]
    for _ in range(VERTICES_NUM + 1)
]

visited = [False for _ in range(VERTICES_NUM + 1)]

def dfs(vertex):
    for curr_v in range(1, VERTICES_NUM + 1):
        if graph[vertex][curr_v] and not visited[curr_v]:
            print(curr_v)
            visited[curr_v] = True
            dfs(curr_v)
    
# Root vertex에서 탐색 시작
root_vertex = 1
print(root_vertex)
visited[root_vertex] = True
dfs(root_vertex)