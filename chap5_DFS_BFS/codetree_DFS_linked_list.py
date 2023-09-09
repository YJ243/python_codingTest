VERTICES_NUM = 7
EDGES_NUM = 6

graph = [[] for _ in range(VERTICES_NUM + 1)]
visitd = [False for _ in range(VERTICES_NUM + 1)]

def dfs(vertex):
    for curr_v in graph[vertex]: # 연결되어 있는 노드에 대해서
        if not visited[curr_v]: # 만약 방문하지 않았더라면
            print(curr_v) # 방문한 노드 출력
            visited[curr_v] = True # 방문했다
            dfs(curr_v) # dfs 재귀 돌기
            
start_points = [1,1,1,2,4,6]
end_points = [2,3,4,5,6,7]


for start, end in zip(start_points, end_points):
    graph[start].append(end)
    graph[end].append(start)
    
root_vertex = 1
print(root_vertex)
visited[root_vertex] = True
dfs(root_vertex)