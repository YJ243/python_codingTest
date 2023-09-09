'''
date: 2023.09.09
name: Yejin
title: 음료수_연결요소 찾기(connected component)
'''

# n, m을 공백으로 구분하여 입력받기
n, m = map(int, input().split())

# 2차원 리스트의 맵 정보 입력받기
graph = []
for i in range(n):
    graph.append(list(map(int, input())))

# DFS로 특정한 노드를 방문한 뒤에 연결된 모든 노드들도 방문
def dfs(x,y):
    # 주어진 범위를 벗어나는 경우 즉시 종료
    if x < 0 or x >= n or y < 0 or y >= m:
        return False
    
    # 현재 노드를 아직 방문하지 않았다면
    if graph[x][y] == 0:
        # 해당 노드 방문 처리
        graph[x][y] = 1
        
        # 상, 하, 좌, 우의 위치도 모두 재귀적으로 호출
        # return 값을 사용하지 않기 때문에
        # 단순히 연결된 모든 노드에 대해서 방문 처리를 수행하기 위한 목적
        dfs(x-1,y)
        dfs(x+1,y)
        dfs(x, y-1)
        dfs(x, y+1)
        print("function: x, y ", x, y)
        return True # 현재 위치에 대해서 처음 DFS가 수행이 된 것
    return False


# 모든 노드(위치)에 대하여 음료수 채우기
result = 0
for i in range(n):
    for j in range(m):
        # 현재 위치에서 DFS 수행
        if dfs(i,j): # 처음 방문하는 것
            print("DFS, i, j: ", i, j)
            result += 1
            
print(result) # 정답 출력