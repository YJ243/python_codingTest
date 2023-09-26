# 2023.09.11 해설

from collections import deque
grid = [
    [1,0,1,1,1],
    [1,0,1,0,1],
    [1,1,1,0,1],
    [1,1,1,1,1],
    [0,0,1,0,1]
]

answer =[
    [0 for _ in range(5)]
    for _ in range(5)
]

visited =[
    [False for _ in range(5)]
    for _ in range(5)
]

order = 1
q = deque()

def in_range(x,y):
    return 0 <= x and x < 5 and 0 <= y and y < 5

def can_go(x, y):
    if not in_range(x,y):
        return False
    if visited[x][y] or grid[x][y] == 0:
        return False
    return True

def push(x,y):
    global order
    
    answer[x][y] = order
    order += 1
    visited[x][y] = True
    q.append((x,y))
    
def bfs():
    dxs = [1,0]
    dys = [0,1]
    
    while q:
        x, y = q.popleft() # 현재 방문한 위치 가져오기
        
        # 아래 및 오른쪽 방향에 대해 탐색
        for dx, dy in zip(dxs, dys): 
            new_x, new_y = x + dx, y + dy
            
            if can_go(new_x, new_y):
                # 각 위치로 이동할 수 있는지 여부 확인 후
                push(new_x, new_y) # queue에 삽입
                
push(0,0) # root vertex를 queue에 삽입
bfs()
    