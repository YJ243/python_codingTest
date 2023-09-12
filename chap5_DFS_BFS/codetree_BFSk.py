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

def dfs(x,y):
    visited = [
        [False for _ in range(n)]
        for _ in range(n)
    ]
    q = deque([(x,y)])
    next_x, next_y = x, y
    max_val = -1
    
    while q:
        a, b = q.popleft()
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            # 범위 안에 있고, 방문하지 않았고, x인 초깃값보다 작으면 이동 가능
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
    
    if (new_x, new_y) == (start_x-1, start_y-1):
        break
    # 그게 아니다?
    start_x, start_y = new_x+1, new_y+1
print(start_x, start_y)
                