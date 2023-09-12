'''
2023.09.12
# 테스트케이스는 맞았는데, graph가 커지면 틀림 --> 중간에 논리 오류가 있는듯 but 코드가 복잡해져서 
어디를 고쳐야할지...?
'''

from collections import deque

n, k = map(int, input().split())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]
start_x, start_y = map(int, input().split()) # 초기 시작 위치

dx = [-1,0,1,0]
dy = [0,-1,0,1]

def bfs(start_x,start_y):
    # bfs 돌때마다 visited 초기화
    visited = [
        [False for _ in range(n)]
        for _ in range(n)
    ]
    q = deque()
    q.append((start_x,start_y)) 

    visited[start_x][start_y] = True # 시작 위치 방문
    
    x = graph[start_x][start_y] # 시작 위치 값

    cur_max = 0 # x보다 작은 숫자 중 최댓값
    '''
    놓친 부분1: 일단 초기 start 값으로 반환 값을 초기화해놓으면, 움직일 수 없는 경우(사방이 큰 숫자로 둘러싸인 경우)
    체크할 수 있었음
    '''
    # 반환 좌표 (일단 초깃값로 저장)
    result_x = start_x
    result_y = start_y
    while q: # 큐가 빌 때까지
        a,b = q.popleft() # 하나의 원소를 뽑아서

        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            # 네 방향에 대해서 확인
            if nx < 0 or nx >= n or ny < 0 or ny >= n:
                continue # 범위 벗어나면 continue
            if x <= graph[nx][ny]: # 현재 값이 초깃값보다 크거나 같으면 움직이지 못하니
                continue
            if visited[nx][ny]: # 이미 방문했다면 패스
                continue
            
            visited[nx][ny] = True
            q.append((nx, ny))
            
            '''
            반환 좌표 업데이트 하는 부분을 어렵게 생각해서 복잡하게 짰었음
            '''
            # 반환 좌표 확음
            if cur_max < graph[nx][ny]: # [x보다 작은 숫자 중 최댓값]이 현재 값보다 작으면
                cur_max = graph[nx][ny] # 무조건 업데이트
                result_x, result_y = nx, ny
            elif cur_max == graph[nx][ny]: # 문제는 같을 땐데,
                # 행이 작거나, # 행이 같을 때 열이 작으면
                if nx < result_x or (nx == result_x and ny < result_y):
                    result_x, result_y = nx, ny

    return result_x, result_y

for i in range(k):
    new_x, new_y = bfs(start_x-1, start_y-1)
    if (new_x, new_y) == (start_x-1, start_y-1):
        break
    start_x, start_y = new_x+1, new_y+1

    
print(start_x+1, start_y+1)

# 내 답에서 고친 것
from collections import deque
n, k = map(int, input().split())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]

start_x, start_y = map(int, input().split())

dx = [-1,0,1,0]
dy = [0,-1,0,1]

def bfs(x,y):
    visited =[
        [False for _ in range(n)]
        for _ in range(n)
    ]
    
    q = deque([(x,y)])
    next_x, next_y = x,y
    max_val = -1
    
    while q:
        a, b = q.popleft()
        
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            if 0 <= nx < n and 0 <= ny < n and not visited[nx][ny] and graph[nx][ny] < graph[x][y]:
                visited[nx][ny] = True
                q.append((nx,ny))
                
                if graph[nx][ny] > max_val:
                    max_val = graph[nx][ny]
                    next_x, next_y = nx, ny
                elif graph[nx][ny] == max_val:
                    if nx < next_x or (nx == next_x and ny < next_y):
                        next_x, next_y = nx, ny
    
    return next_x, next_y

for _ in range(k):
    new_x, new_y = bfs(start_x-1, start_y-1)
    
    if (new_x, new_y) == (start_x-1, start_y-1): # 그냥 막바로 리턴해버렸다면
        # 움직일 수 없다는 뜻이니까
        break
    # 그게 아니면
    start_x, start_y = new_x+1, new_y+1
print(start_x, start_y)

## 해설
''' 
시작 위치에 적혀있는 숫자보다 작은 모든 위치 중, 우선순위가 가장 높은 곳으로 이동하는 것을 k번 반복
우선순위 1: 숫자가 큰 것 / 우선순위 2: 행이 작은 것 / 우선순위 3: 행이 같은데 열이 작은 것

--> 특정 기준에 따라 한 물체를 원하는 위치로 계속 움직이기

도달이 가능한 여러 칸 중 (숫자, -행, -열)순으로 가장 큰 위치를 선택 --> tuple형의 비교를 통해 구현


'''
import collections

NOT_EXISTS = (-1, -1)

n, k = tuple(map(int, input().split()))
grid = [
    list(map(int, input().split()))
    for _ in range(n)
]

# 현재 위치
r, c = tuple(map(int, input().split()))
curr_cell = (r-1, c-1) 
bfs_q = collections.deque()
visited = [
    [0 for _ in range(n)]
    for _ in range(n)
]

def in_range(x,y):
    return 0 <= x < n and 0 <= y < n

def can_go(x, y, target_num):
    return in_range(x,y) and not visited[x][y] and grid[x][y] < target_num

# visited 배열을 초기화 --> 새로운 위치에서 bfs 탐색할 떄마다 사용해야 하니까
def initialize_visited():
    for i in range(n):
        for j in range(n):
            visited[i][j] = False

def bfs():
    dxs, dys = [0,1,0,-1], [1,0,-1,0]
    
    curr_x, curr_y = curr_cell
    visited[curr_x][curr_y] = True
    bfs_q.append(curr_cell)
    
    target_num = grid[curr_x][curr_y]
    
    # BFS 탐색 수행
    while bfs_q:
        curr_x, curr_y = bfs_q.popleft()
        
        for dx, dy in zip(dxs, dys):
            new_x, new_y = curr_x + dx, curr_y + dy
            
            if can_go(new_x, new_y, target_num):
                bfs_q.append((new_x, new_y))
                visited[new_x][new_y] = True

# best 위치를 새로운 위치로 바꿔주어야 하는지 우선순위 판단
def need_update(best_pos, new_pos):
    # 첫 도달 가능한 위치라면 update 필요
    # 만약 best_pos가 아직 존재하지 않는 초기 상태라면, 
    # 새 위치가 최선의 위치가 될 수 있기 때문에 업데이트가 필요
    if best_pos == NOT_EXISTS:
        return True
    
    best_x, best_y = best_pos
    new_x, new_y = new_pos
    
    # 숫자, -행, -열 순으로 더 큰 곳이 골라져야 함
    return (grid[new_x][new_y], -new_x, -new_y) > \
        (grid[best_x][best_y], -best_x, -best_y)


# 가장 우선순위가 높은 위치를 찾아 위치 이동
def move():
    global curr_cell
    
    # BFS 탐색을 위한 초기화 작업 수행
    initialize_visited()
    
    # Step1. BFS를 진행하여 갈 수 있는 모든 위치를 탐색
    bfs()
    
    # Step2.
    # 도달할 수 있는 위치들 중 가장 우선순위가 높은 위치를 구함
    best_pos = NOT_EXISTS
    for i in range(n):
        for j in range(n):
            # 도달이 불가능하거나 현재 위치는 건너뜀
            if not visited[i][j] or (i,j) == curr_cell:
                continue
            
            new_pos = (i,j)
            if need_update(best_pos, new_pos):
                best_pos = new_pos
    # Step3. 위치를 이동


    # 만약 움직일 위치가 없다면 종료
    if best_pos == NOT_EXISTS:
        return False
    # 움직일 위치가 있다면 이동
    else:
        curr_cell = best_pos
        return True

# k번에 걸쳐 움직이는 것을 반복
for _ in range(k):
    is_moved = move()
    
    # 움직이지 못했다면 바로 종료
    if not is_moved:
        break

final_x, final_y = curr_cell
print(final_x+1, final_y+1)