answer = [
    [0 for _ in range(5)]
    for _ in range(5)
]

visited = [
    [0 for _ in range(5)]
    for _ in range(5)
]

order = 1

def in_range(x,y):
    return 0 <= x and x < 5 and 0 <= y and y < 5

def can_go(x,y):
    if not in_range(x,y):
        return False
    if visited[x][y] or grid[x][y] == 0:
        return False
    return True

def dfs(x,y):
    global order
    
    dxs, dys = [1, 0], [0, 1]
    
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        
        if can_go(new_x, new_y):
            answer[new_x][new_y] = order
            order += 1
            visited[new_x][new_y] = 1
            dfs(new_x, new_y)
            
answer[0][0] = order
order += 1
visited[0][0] = 1
dfs(0,0)


## DFS-2

def dfs(x,y):
    global order
    
    dxs, dys = [1,0], [0,1]
    
    answer[x][y] = order
    order += 1
    visited[x][y] = 1
    
    for dx, dy in zip(dxs, dys):
        new_x, new_y = x + dx, y + dy
        
        if can_go(new_x, new_y):
            dfs(new_x, new_y)
            
dfs(0,0)