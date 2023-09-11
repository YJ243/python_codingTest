'''
2023.09.11
'''
from collections import deque

VERTICES_NUM = 7
EDGES_NUM = 6

graph = [[] for _ in range(VERTICES_NUM+1)]
visited = [False for _ in range(VERTICES_NUM+1)]
q  = deque()

def bfs():
    while q:
        curr_v = q.popleft()
        
        for next_v in graph[curr_v]:
            if not visited[next_v]:
                print(next_v)
                visited[next_v] = True
                q.append(next_v)
                
start_points = [1,1,1,2,4,6]
end_points = [2,3,4,5,6,7]

for start, end in zip(start_points, end_points):
    graph[start].append(end)
    graph[end].append(start)


root_vertex = 1
print(root_vertex)
visited[root_vertex] = True
q.append(root_vertex)
bfs()