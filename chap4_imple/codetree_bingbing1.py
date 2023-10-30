'''
2023.10.29 내풀이
'''

n, m = map(int, input().split())                    # n: 행, m: 열
maze = [[0 for _ in range(m)] for _ in range(n)]    # 채울 배열

c_cnt, r_cnt, cur_dir = m, n-1, 0       # 채워야 할 열개수, 행개수, 현재 방향
start_num, num_cnt = 64, 0              # 시작 숫자(64+1의 chr은 'A'), 추가되는 수
x, y = 0, -1                            # 처음 좌표
dirs = ((0,1),(1,0),(0,-1),(-1,0))      # 오(0)->아(1)->왼(2)->위(3)

def write_num():
    global start_num ,num_cnt, cur_dir, x, y
    num_cnt += 1        # 하나 증가
    if num_cnt == 27:   # 'Z'를 넘어가면
        num_cnt = 1     # 다시 'A'로 돌아가기 (64+num_cnt = 65)
    x, y = x + dirs[cur_dir][0], y + dirs[cur_dir][1]   # 다음 채울 칸의 좌표
    maze[x][y] = chr(start_num + num_cnt)               # 알파벳 채우기
        

def isFinish():
    for i in range(n):
        for j in range(m):
            if maze[i][j] == 0: # 한 칸이라도 안 채운 것이 있다면
                return False
    return True

while True:
    if isFinish(): break        # 모든 칸을 다 채웠으면 나가기
    if cur_dir % 2 == 0:        # 오/왼 방향일 경우
        for _ in range(c_cnt):  # 열 개수만큼 숫자 채우기
            write_num()
        c_cnt -= 1              # 1만큼 감소
    else:
        for _ in range(r_cnt):  # 아/위 방향일 경우
            write_num()
        r_cnt -= 1
    cur_dir = (cur_dir + 1)%4

for i in range(n):
    for j in range(m):
        print(maze[i][j], end=' ')
    print()
    

'''
2023.10.29 해설
'''

# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))
answer = [
    [0 for _ in range(m)]
    for _ in range(n)
]

visited = [
    [0 for _ in range(m)]
    for _ in range(n)
]

def can_go(new_x, new_y):
    # 나아가려는 위치가 직사각형 안에 들어있는지 확인하고,
    # 들어있다면 아직 방문한 적이 없는 곳인지 확인하기
    if 0 <= new_x and new_x < n and \
        0 <= new_y and new_y < m and visited[new_x][new_y] == 0:
        return True
    else:
        return False

# direction에 따라 바뀌는 (x,y)의 변화량인 dx, dy를 정의
dxs, dys = [0,1,0,-1], [1,0,-1,0]
curr_x, curr_y = 0,0    # 시작은 (0,0)
direction = 0           # 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽

# 처음 시작 위치에 초깃값을 적음
answer[curr_x][curr_y] = 'A'
visited[curr_x][curr_y] = True

# n*m개의 알파베승ㄹ 적어야 함
for i in range(1, n*m):     # i번째 문자를 어디에 적을지 결정
    while True:             # 나아갈 수 있을 때까지 방향을 바꿔가면서 확인하기
        # 현재 방향 dir을 기준으로 그 다음 위치 값을 계산
        next_x, next_y = \
            curr_x + dxs[direction], curr_y + dys[direction]
        # 그 위치로 나아갈 수 있는지 확인
        if can_go(next_x, next_y):
            # 나아갈 수 있다면 위치를 갱신해주고 배열에 올바른 값을 채워넣음
            curr_x, curr_y = next_x, next_y
            visited[curr_x][curr_y] = True
            answer[curr_x][curr_y] = (chr(i%26)+ord('A'))
            break
        else:
            # 나아갈 수 없다면 시계방향으로 90도 회전하여 그 다음 방향을 확인하기
            direction = (direction + 1)%4

# 출력

for i in range(n):
    for j in range(m):
        print(answer[i][j], end=' ')
    print()