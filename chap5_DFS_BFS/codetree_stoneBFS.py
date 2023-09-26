'''
2023.09.13 돌 잘 치우기
한 번에 맞은 문제!
'''
from collections import deque
from itertools import permutations, combinations

n, k, m = map(int, input().split())

graph = [
    list(map(int, input().split()))
    for _ in range(n)
]

visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

stone_list = [] # 돌이 어느 좌표에 있는지 저장
combi_list = [] # m개의 돌 조합을 담는 리스트
max_list = [] # 각각의 치우는 돌 위치에 따라 방문 가능한 칸의 수 최댓값을 담는 리스트

# k번마다, 돌 조합마다 새로 탐색하기 위해 visited 배열을 초기화하는 함수
def initialize_visited():
    for i in range(n):
        for j in range(n):
            visited[i][j] = False

# 돌이 있는 격자에서 m개의 돌 조합을 만드는 함수
def make_combi(m):
    global stone_list
    stone_list = [] # stone_list 초기화
    for i in range(n):
        for j in range(n):
            if graph[i][j]: # 돌이 있다면
                stone_list.append((i,j)) # 돌이 있는 좌표 넣기
    '''
    여기서 stone_list를 아래와 같이 초기화 가능
    stone_list = [
        (i, j)
        for i in range(n)
        for j in rangE(n)
        if graph[i][j] == 1
    ]
    '''
    # combinations 이용해서 stone_list에서 m개 뽑아서 리스트로 만들기 (외우기)
    combi_list = list(combinations(stone_list,m))
    return combi_list

dx = [-1,0,1,0]
dy = [0,-1,0,1]

# 탐색하는 함수
def bfs(x,y):
    visited[x][y] = True
    q = deque()
    q.append((x,y))
    
    count = 1 # 탐색 1 초기화
    while q:
        a, b = q.popleft()
        
        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            if nx < 0 or nx >= n or ny < 0 or ny >= n:
                continue
            if graph_mid[nx][ny]: # 만약 돌이 있다면
                continue
            if visited[nx][ny]: # 만약 방문했다면
                continue
            
            if not visited[nx][ny] and not graph_mid[nx][ny]:
                count += 1 # 탐색수 증가
                visited[nx][ny] = True # 방문 표시
                q.append((nx,ny)) # 큐에 넣기
    return count
                
# 각각 돌 조합에 대해서 돌을 치워야 하니까 새로 그래프 만들기
graph_mid = [
    [0 for _ in range(n)] for _ in range(n)
]

# 돌 조합에 대한 그래프 초기화 (원래 그래프 복사)
# 해설을 보니, 그래프를 매번 새로 만들지 않아도, 돌을 치운 곳에 다시 돌을 갖다놓으면 됨
def initialize_midgraph():
    for i in range(n):
        for j in range(n):
            graph_mid[i][j] = graph[i][j] # 일단 원래 그래프 복사
            
combi_list = make_combi(m) # m개의 돌 조합 리스트 만들기
for _ in range(k): # k개의 시작점에 대해서 탐색 시작
    r, c = map(int, input().split()) # start_x, start_y
    
    make_combi(m) # 돌이 있는 곳 치우기 위한 조합 리스트
    for combi in combi_list:
        # 각각 (1,1)-(1,2)에 대해서 반복
        initialize_midgraph() # 각 조합마다 탐색할 그래프 만들기(원래 그래프 복사)
        initialize_visited() # 방문 배열 초기화
        
        # 돌 치우기
        for i in range(len(combi)):
            a, b = combi[i] # (1,1) --> a=1, b=1
            graph_mid[a][b] = 0 # 돌 치움
    
    max_list.append(bfs(r-1, c-1)) # 각각 탐색 수 일단 list에 append
    

print(max(max_list)) # 그 리스트에서 최댓값 출력

# 해설
'''
Intuition
- Backtracking을 이용해 주어진 돌 중 치우게 될 m개의 돌을 선택할 수 있음
- 각 선택마다 k개의 시작점을 처음 queue에 전부 집어넣어 시작점이 여러 개인 경우의 bfs탐색 진행
- 시작점이 여러 개인 BFS의 경우, 처음 모든 시작점을 전부 queue에 넣은 뒤 BFS 한 번 진행하면 해결 가능
'''
# Backtracking, 어제 문제의 dx,dy테크닉 문제 모두 풀기 (현대차 자소서 쓴다음)

# 해설 답
from collections import deque

# 변수 선언 및 입력
n, k, m = tuple(map(int, input().split()))

a = [
    list(map(int, input().split()))
    for _ in range(n)
]

ans = 0
s_pos = []
stone_pos =[
    (i,j)
    for i in range(n)
    for j in range(n)
    if a[i][j] == 1
]

selected_stones = []

# bfs에 필요한 변수들
q = deque()
visited = [
    [False for _ in range(n)]
    for _ in range(n)
]

def in_range(x,y):
    return 0 <= x < n and 0 <= y < n

def can_go(x,y):
    return in_range(x,y) and not a[x][y] and not visited[x][y]

def bfs():
    # queue에 남은 것이 없을 때까지 반복
    while q:
        # queue에서 가장 먼저 들어온 원소를 뺌
        x, y = q.popleft()
        
        dxs, dys = [1,-1,0,0], [0,0,1,-1]
        
        # queue에서 뺸 원소의 위치를 기준으로 4방향을 확인
        for dx, dy in zip(dxs, dys):
            nx, ny = x + dx, y + dy
            
            # 아직 방문한 적이 없으면서 갈 수 있는 곳이라면
            # 새로 queue에 넣어주고 방문 여부를 표시
            if can_go(nx,ny):
                q.append((nx,ny))
                visited[nx][ny] = True

def calc():
    for x, y in selected_stones:
        a[x][y] = 0
        
    for i in range(n):
        for j in range(n):
            visited[i][j] = False
    
    # k개의 시작점을 queue에 넣고 시작
    # BFS는 여러 시작점에서 시작하여
    # 이동 가능한 칸을 전부 탐색하는 것이 가능
    for x, y in s_pos:
        q.append((x,y))
        visited[x][y] = True
        
    bfs()
    
    for x, y in selected_stones:
        a[x][y] = 1
        
    cnt = 0
    for i in range(n):
        for j in range(n):
            if visited[i][j]:
                cnt += 1
    
    return cnt

# 주어진 돌 (stone_pos에 저장된 위치들) 중에서 
# 'm'개를 선택하는 모든 경우의 수를 탐색하는 재귀 함귀 (조합으로 안하고 재귀로)
def find_max(idx, cnt): # idx: 현재 고려 중인 돌 인덱스, cnt: 지금까지 선택한 돌 개수
    global ans
    
    # 재귀 종료 조건
    if idx == len(stone_pos): # 만약 모든 돌을 고려했다면
        if cnt == m: # 그리고 선택한 돌의 수가 정확히 m개라면
            ans = max(ans, calc()) # calc로 결과 계산
        return # 그렇지 않다면 종료
    
    selected_stones.append(stone_pos[idx]) # 현재 위치의 돌을 선택 목록에 추가
    find_max(idx + 1, cnt + 1) # 다음 돌을 고려해 선택한 돌의 개수 하나 늘림
    selected_stones.pop() # 선택 목록에서 마지막에 추가한 돌 제거(선택 취소)
    
    find_max(idx + 1, cnt) # 다음 돌 고려해서 선택한 돌 개수 그대로 유지
    
for _ in range(k):
    r, c = tuple(map(int, input().split()))
    s_pos.append((r-1, c-1))
    
find_max(0,0)
print(ans)