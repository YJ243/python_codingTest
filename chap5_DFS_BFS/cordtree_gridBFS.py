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
        x, y = q.popleft()
        
        for dx, dy in zip(dxs, dys):
            new_x, new_y = x + dx, y + dy
            
            if can_go(new_x, new_y):
                push(new_x, new_y)
                
push(0,0)
bfs()
    