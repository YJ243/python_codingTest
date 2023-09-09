'''
2023.09.05
'''

n, m = map(int, input().split())

graph = [[] for _ in range(n+1)]
visited = [False for _ in range(n+1)]

for i in range(m):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)
    
def dfs(graph, v):
    visitd[v] = True
    count = 0
    for i in graph[v]:
        if not visited[i]:
            count += 1
            count += dfs(graph, i)
    return count

print(dfs(graph, 1))

'''
2023.09.09
'''

n, m = map(int, input().split())
graph = [[] for _ in range(n+1)]

for i in range(m):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)
    
visited = [False for _ in range(n+1)]

count = 0
def dfs(v):
    visited[v] = True
    global count
    for i in graph[v]:
        if not visited[i]:
            count += 1
            dfs(i)
            
dfS(1)
print(count)

### answer
# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))

# index를 1번부터 사용하기 위해 m+1만큼 할당
graph = [[] for _ in range(n+1)]
vertex_cnt = 0

def dfs(vertex):
    global vertex_cnt
    
    # 해당 정점에서 이어져있는 모든 정점을 탐색
    for curr_v in graph[vertex]:
        # 아직 간선이 존재하고 방문한 적이 없는 정점에 대해서만 탐색 진행
        if not visited[curr_v]:
            visited[curr_v] = True
            vertex_cnt += 1
            dfs(curr_v)
            
for i in range(m):
    v1, v2 = tuple(map(int, input().split()))
    
    # 각 정점이 서로 이동이 가능한 양방향 그래프이므로
    # 각 정점에 대한 간선을 각각 저장해줌
    graph[v1].append(v2)
    graph[v2].append(v1)
    
visited[1] = True
dfs(1)

print(vertex_cnt)

### answer (adjacent matrix)
# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))

# index를 1번부터 사용하기 위해 n+1만큼 할당
graph = [
    [0 for _ in range(n+1)]
    for _ in range(n+1)
]

visited = [False for _ in range(n+1)]
vertex_cnt = 0

def dfs(vertex):
    global vertex_cnt
    
    # 해당 정점에서 이어져있는 모든 정점을 탐색
    for curr_v in range(1, n+1):
        # 아직 간선이 존재하고 방문한 적이 없는 정점에 대해서만 탐색 진행
        if graph[vertex][curr_v] and not visited[curr_v]:
            visited[curr_v] = True
            vertex_cnt += 1
            dfs(curr_v)
            
for i in range(m):
    v1, v2 = tuple(map(int, input().split()))
    
    # 각 정점이 서로 이동이 가능한 양방향 그래프이기 때문에
    # 각 정점에 대한 간선을 각각 저장해줌
    graph[v1][v2] = 1
    graph[v2][v1] = 1
    
visited[1]=True
dfs(1)

print(vertex_cnt)