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