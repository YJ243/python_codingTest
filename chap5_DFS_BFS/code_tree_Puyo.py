'''
2023.09.11
틀린 이유 1: 출력에서 4 이상일 때에만 최대 블럭수를 출력한다고 잘못 봄,
4보다 작을 때에도 최대 블럭수를 출력하도록 하였음--> 문제 제대로 읽기
'''

import sys
sys.setrecursionlimit(10**5)

n = int(input())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

dx = [0,1,0,-1]
dy = [1,0,-1,0]

block_cnt = 0
def dfs(x,y,k):
    global block_cnt
    
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        
        if nx < 0 or nx >= n or ny < 0 or ny >= n:
            continue
        if visited[nx][ny]:
            continue
        if graph[nx][ny] != k:
            continue
        if graph[nx][ny] == k and not visited[nx][ny]:
            block_cnt += 1
            visited[nx][ny] =True
            dfs(nx,ny,k)
    return block_cnt

block_cnt_list=  []
bam_block = 0

for i in range(n):
    for j in range(n):
        if not visited[i][j]:
            k = graph[i][j]
            visited[i][j] = True
            block_cnt = 1 # 계속 초기화
            ret = dfs(i,j,k)
            block_cnt_list.append(block_cnt)
            if block_cnt >= 4: # 폭발된 블록 뭉텅이가 있으면
                bam_block += 1

print(bam_block, max(block_cnt_list))

## 해설

# 변수 선언 및 입력:
n = int(input())

grid = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited =[
    [False for _ in range(n)]
    for _ in range(n)
]

max_block, bomb_cnt = 0,0
curr_block_num = 0

# 탐색하는 위치가 격자 범위 내에 있는지 여부를 반환
def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

# 탐색하는 위치로 움직일 수 있는지 여부를 반환
def can_go(x, y, color):
    if not in_range(x,y):
        return False
    if visited[x][y] or grid[x][y] != color:
        return False
    return True

def dfs(x,y):
    global curr_block_num
    
    # 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽
    dxs, dys = [0,1,0,-1], [1,0,-1,0]
    
    # 네 방향 각각에 대해 DFS 탐색
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        
        if can_go(new_x, new_y, grid[x][y]):
            visited[new_x][new_y] = true
            # 블럭 하나 추가
            curr_block_num += 1
            dfs(new_x, new_y)
            
# 격자의 각 위치에서 탐색을 시작할 수 있는 경우
# 한 블럭에 대한 DFS 탐색을 수행
for i in range(n):
    for j in range(n):
        if not visited[i][j] and grid[i][j]:
            # 해당 블럭을 방문할 수 있는 경우 visited 배열을 갱신
            # 새로운 블럭을 탐색한다는 의미로 curr_block_num을 1로 갱신
            visited[i][j] = True
            curr_block_num = 1
            
            dfs(i,j)
            
            # 한 블럭 묶음에 대한 탐색이 끝난 경우 답을 갱신
            if curr_block_num >= 4:
                bomb_cnt += 1
                
            max_block = max(max_block, curr_block_num)

print(bomb_cnt, max_block)