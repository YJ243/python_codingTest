'''
2023.10.09 
- 한 번에 맞았으나 잦은 실수때문에, 마지막에 몇 번 고침
- 실수 1. maze = [list(map(int, input().split()))] 여기서 for _ in range(n) 빼먹음
            maze = [
                list(map(int, input().split()))
                for _ in range(n)
            ]
    차라리 길어지더라도 이렇게 여러 줄에 나누어 써서 실수 줄일까?
- 실수 2. 함수 이름 redo_bomb인데, undo_bomb을 부름
- 실수 3. i,j를 넣어야 하는데 x,y를 넣음
'''
n = int(input())
maze = [list(map(int, input().split())) for _ in range(n)]    # 격자
bomb_loc = []
for i in range(n):
    for j in range(n):
        if maze[i][j]: bomb_loc.append((i,j)) # 폭탄이 놓이는 자리

max_r = 0  # 결과값, 폭발시킬 최대 지역 수

def choose_bomb():  # 현재 결과값과 비교해서 더 크다면 업데이트 하기
    global max_r
    cur_cnt = 0
    for i in range(n):
        for j in range(n):
            if maze[i][j]: cur_cnt += 1
    if max_r < cur_cnt:
        max_r = cur_cnt

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y <n

def do_bomb(idx, i):
    x, y = bomb_loc[idx][0], bomb_loc[idx][1]

    if i == 0: # 위 아래 두개 초토화
        dirs = ((1,0),(-1,0),(2,0),(-2,0))
    elif i == 1: # 십자 모양 초토화
        dirs = ((1,0),(-1,0),(0,1),(0,-1))
    else:       # 대각선 모양 초토화
        dirs = ((-1,-1),(1,-1),(1,1),(-1,1))
    
    for d in range(4): # 네 방향에 대해서 확인
        nx, ny = x + dirs[d][0], y + dirs[d][1]
        if not in_range(nx,ny): continue
        maze[nx][ny] += 1
 

def redo_bomb(idx, i):
    x, y = bomb_loc[idx][0], bomb_loc[idx][1]

    if i == 0: # 위 아래 두개 초토화
        dirs = ((1,0),(-1,0),(2,0),(-2,0))
    elif i == 1: # 십자 모양 초토화
        dirs = ((1,0),(-1,0),(0,1),(0,-1))
    else:       # 대각선 모양 초토화
        dirs = ((-1,-1),(1,-1),(1,1),(-1,1))
    
    for d in range(4): # 네 방향에 대해서 확인
        nx, ny = x + dirs[d][0], y + dirs[d][1]
        if not in_range(nx,ny): continue
        maze[nx][ny] -= 1
    # 근데 그냥 이렇게 돌리면 되는게 아님
    # 겹치는 부분에 대해서는 냅둬야 하기 때문에 -> 그럼 숫자 증/감으로?


def make_bomb(idx):    # bomb_loc[idx]자리의 주변 초토화 영역 고르는 함수
    if idx == len(bomb_loc): # 만약 전체 폭탄이 놓인 자리를 모두 탐색했다면
        choose_bomb()
        return
    
    # 폭탄 자리가 (0,0), (1,1) 이 있다고 하면
    # 각 자리마다 1,2,3 경우의 수 생각
    for i in range(3):
        # idx번 폭탄 자리에 {i번 조합} 지역 초토화
        do_bomb(idx, i)
        make_bomb(idx+1)
        redo_bomb(idx, i)


make_bomb(0)
print(max_r)

## 해설
'''
- 폭탄을 놓아야 하는 위치에 놓이게 될 폭탄 종류에 대해 가능한 모든 순열을 만들기
- 그 중 폭탄에 의해 초토화 되는 영역 중 최대를 구하기
- 각 폭탄 종류마다 영향을 미치는 위치들을 나타내는 배열을 만들기
'''

# 변수 선언 및 입력:
n = int(input())
bomb_type = [
    [0 for _ in range(n)]
    for _ in range(n)
]
bombed = [
    [False for _ in range(n)]
    for _ in range(n)
]

ans = 0
bomb_pos = list()

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

def bomb(x, y, b_type):
    # 폭탄 종류마다 터질 위치를 미리 정의하기
    bomb_shapes = [
        [],
        [[-2,0],[-1,0],[0,0],[1,0],[2,0]],
        [[-1,0],[1,0],[0,0],[0,-1],[0,1]],
        [[-1,-1],[-1,1],[0,0],[1,-1],[1,1]]
    ]
    
    # 격자 내 칸에 대해서만 영역을 표시하기
    for i in range(5):
        dx, dy = bomb_shapes[b_type][i]
        nx, ny = x + dx, y + dy
        if in_range(nx,ny):
            bombed[nx][ny] = True
            
def calc():
    # Step1. 폭탄이 터진 위치를 표시하는 배열을 초기화
    for i in range(n):
        for j in range(n):
            bombed[i][j] = False
            
    # Step2. 각 폭탄의 타입에 따라 초토화되는 영역을 표시
    for i in range(n):
        for j in range(n):
            if bomb_type[i][j]: # 폭탄이 있는 위치
                bomb(i,j,bomb_type[i][j]치
    
    # Step3. 초토화된 영역의 수를 구하기
    cnt = 0
    for i in range(n):
        for j in range(n):
            if bombed[i][j]:
                cnt += 1
    return cnt
    
def find_max_area(cnt):
    global ans
    
    if cnt == len(bomb_pos):
        ans = max(ans, calc())
        return
        
    for i in range(1,4):
        x, y = bomb_pos[cnt]
        
        bomb_type[x][y] = i
        find_max_area(cnt+1)
        bomb_type[x][y] = 0

for i in range(n):
    given_row = list(map(int, input().split()))
    for j, bomb_place in enumerate(given_row):
        if bomb_place:
            bomb_pos.append((i,j))

find_max_area(0)

print(ans)