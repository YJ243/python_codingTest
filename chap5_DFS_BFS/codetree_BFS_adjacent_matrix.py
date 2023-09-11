'''
2023.09.11
'''

from collections import deque

VERTICES_NUM = 7
EDGES_NUM = 6

graph = [
    [0 for _ in range(VERTICES_NUM+1)]
    for _ in range(VERTICES_NUM+1)
]
# 이미 방문한 곳을 또 방문하지 않도록 필요
visited = [False for _ in range(VERTICES_NUM+1)]
q = deque()

# BFS 탐색
def bfs():
    while q: # 큐가 비워지기 전까지
        curr_v = q.popleft() # 맨 앞의 원소를 뽑아 탐색 진행
        
        # vertex에 연결된 정점 탐색
        for next_v in range(1, VERTICES_NUM + 1):
            # 방문했던 적이 없는 곳으로만 가기
            if graph[curr_v][next_v] and not visited[next_v]:
                print(next_v)
                visited[next_v] = True
                q.append(next_v)


start_points = [1,1,1,2,4,6]
end_points = [2,3,4,5,6,7]

# 인접행렬로 그래프 표현
for start, end in zip(start_points, end_points):
    graph[start][end] = 1
    graph[end][start] = 1

# root_vertex를 queue에 삽입
root_vertex = 1
print(root_vertex)
visited[root_vertex] = 1
q.append(root_vertex)
bfs()
