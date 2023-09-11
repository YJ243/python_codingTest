'''
date: 2023.09.10
name: Yejin
title: classify villeage
'''

'''
# 그리드 상에서 상하좌우 인접한 위치로 이동 가능 --> 양방향으로 연결된 그래프
# 각 마을에 대한 탐색이 끝나고 나면 DFS 탐색을 하면서 방문한 정점의 개수를 저장

'''

## 내 답안
n = int(input())

graph = []

for _ in range(n):
    graph.append(list(map(int, input().split())))

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]    
dx = [-1,1,0,0]
dy = [0,0,-1,1]

people_in_villeage = 0
def dfs(x,y):
    people_in_villeage = 1 # 현재 마을의 사람 수를 저장할 변수
    
    visited[x][y] = True
    
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx < 0 or nx >= n or ny < 0 or ny >= n:
            continue
        if not graph[nx][ny]:
            continue
        
        if not visited[nx][ny] and graph[nx][ny]:
            visited[nx][ny] = True
            people_in_villeage += dfs(nx,ny) # 인접한 마을의 사람 수를 더함
            
    return people_in_villeage # 현재 마을의 사람 수 반환
            
# 각 마을의 사람 수를 담을 리스트
people = []

# 마을 개수
villeage_count = 0
for i in range(n):
    for j in range(n):
        if graph[i][j] == 1 and not visited[i][j]:
            people_in_villeage = dfs(i, j) # dfs로 돌았다면
            villeage_count += 1
            people.append(people_in_villeage)

people.sort()
print(villeage_count)
for p in people:
    print(p)
    

## 해설

# 변수 선언 및 입력
n = int(input()) 
grid = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

people_num = 0
people_nums = list()

# 주어진 위치가 격자를 벗어나는지 여부를 반환
def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

# 주어진 위치로 이동할 수 있는지 여부를 확인
def can_go(x,y):
    if not in_range(x,y):
        return False
    if visited[x][y] or grid [x][y] == 0:
        return False
    return True

def dfs(x,y):
    global people_num
    
    # 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽
    dxs, dys = [0,1,0,-1], [1,0,-1,0]
    
    # 네 방향 각각에 대해 DFS 탐색 수행
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        if can_go(new_x, new_y):
            visited[new_x][new_y] = True
            
            # 마을에 존재하는 사람을 한 명 추가해줌
            people_num += 1
            dfs(new_x, new_y)
            
# 격자의 각 위치에서 탐색을 시작할 수 있는 경우
# 한 마을에 대한 DFS 탐색 수행 
for i in range(n):
    for j in range(n):
        if can_go(i,j):
            # 해당 위치를 방문할 수 있는 경우 visited 배열을 갱신하고
            # 새로운 마을을 탐색한다는 의미로 people_num을 1으로 갱신
            visited[i][j] = True
            people_num = 1
            
            dfs(i,j)
            
            # 한 마을에 대한 탐색이 끝난 경우 마을 내의 사람 수를 저장
            people_nums.append(people_num)
            
# 각 마을 내 사람의 수를 오름차순 정렬
people_nums.sort()

print(len(people_nums))

for i in range(len(people_nums)):
    print(people_nums[i])
        