'''
2023.10.04 
되돌아오기 1
'''
# 내 풀이
n = int(input())
a = [[-1 for _ in range(2001)] for _ in range(2001)] 
x, y = 1000,1000 # 초기 좌표
cur_val = 0
a[x][y] = cur_val

dirs = ((0,-1),(1,0),(-1,0),(0,1)) # W, S, N, E
mapping = {
    'W': 0,
    'S': 1,
    'N': 2,
    'E': 3
}

result = -1
flag = 0

for i in range(n):
    n, l = input().split()
    cur_dir = mapping[d]
    l = int(l)
    nx, ny = x + dirs[cur_dir][0], y+dirs[cur_dir][1] # 방향 이동
    if a[nx][ny] == 0 and flag == 0: # 만약 이동하려는 방향이 0이면
        result = cur_val
        flag = 1
    x, y = nx,ny
    a[x][y] = cur_val

print(result)

# 해설
# 변수 선언 및 입력
n = int(input())

# 시작 위치를 기록
x, y = 0,0

# 동,서,남,북 순(좌표계)으로 dxs, dys 정의
dxs, dys = [1,-1,0,0], [0,0,-1,1]

# 답을 저장
ans = -1

# 지금까지 걸린 시간을 기록
elapsed_time = 0

# dir 방향으로 dist만큼 이동하는 함수
# 만약 시작지에 도달하면 true를 반환
def move(move_dir, dist):
    global x, y
    global ans, elapsed_time
    
    for _ in range(dist):
        x, y = x + dxs[move_dir], y + dys[move_Dir]
        
        # 이동한 시간 기록
        elapsed_time += 1
        
        # 시작지로 다시 돌아오면 답 갱신
        if x == 0 and y == 0:
            ans = elapsed_time
            return True
    return False

# 움직이는 것을 진행
for _ in range(n):
    c_dir, dist = tuple(input().split())
    dist = int(dist)
    
    # 각 방향에 맞는 번호를 붙여줌
    if c_dir == 'E':
        move_dir = 0
    elif c_dir == 'W':
        move_dir = 1
    elif c_dir == 'S':
        move_dir = 2
    else:
        move_dir = 3
    
    # 주어진 방향대로 dist만큼 위치를 이동
    done = move(move_dir, dist)
    if done:
        break
print(ans)

'''
2023.10.05 
되돌아오기 2
'''

# 내 풀이
cmd_list = list(input())
x,y = 0,0 # 초기 좌표
cur_d = 0 # 초기 방향, 북쪽
time = 0
result = -1
dirs = ((0,1),(-1,0),(0,-1),(1,0)) # 반시계방향으로 0, 1, 2, 3 (북, 서, 남, 동)

for i in range(len(cmd_list)):
    time += 1 # 시간 증가
    d = cmd_list[i] # 명령 저장
    if d == 'L':
        cur_d = (cur_d+1)%4
    elif d == 'R':
        cur_d = (cur_d-1+4)%4
    else:
        x, y = x+dirs[cur_d][0], y+dirs[cur_d][1]
    #print(x,y)
    if x == 0 and y == 0:
        result = time
        break
print(result)
