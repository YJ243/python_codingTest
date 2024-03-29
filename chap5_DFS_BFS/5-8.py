'''
date: 2023.09.04/2023.09.09
name: Yejin
title: DFS 
'''
# DFS는 스택 자료구조 이용 --> 실제 구현은 재귀 함수를 이용할 때 간결하게 구현 가능
# 1. 탐색 시작 노드를 스택에 삽입하고 방문 처리
# 2. 스택의 최상단 노드에 방문하지 않은 인접 노드가 있으면 그 인접 노드를 스택에 넣고 방문처리
#    방문하지 않은 인접 노드가 없으면 스택에서 최상단 노드를 꺼냄
# 1, 2를 계속 반복

'''
재귀적으로 방문하지 않은 노드들을 계속해서 방문한다는 점에서 깊이 우선으로,
최대한 깊게 그래프를 탐색할 수 있음
'''
# DFS 함수 정의
def dfs(v):
    # 현재 노드를 방문 처리
    visited[v] = True
    print(v, end=' ') # 탐색 순서(스택에 들어간 순서)
    
    # 현재 노드와 연결된 다른 노드를 재귀적으로 방문
    for i in graph[v]:
        if not visited[i]:
            dfs(i)
        
    

# 각 노드가 방문된 정보를 리스트 자료형으로 표현(1차원 리스트)
visited = [False for _ in range(9)]
visited = [False] * 9
print(visited)

# 각 노드가 연결된 정보를 리스트 자료형으로 표현 (2차원 리스트)
graph = [
    [],
    [2,3,8],
    [1,7],
    [1,4],
    [3,5],
    [3,4],
    [7],
    [2,6,8],
    [1,7]
]

# 정의된 DFS 함수 호출
dfs(1)