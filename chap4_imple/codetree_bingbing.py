'''
2023.10.27 빙빙돌며 숫자 사각형 채우기2
'''

n, m = map(int, input().split())                    # n: 행, m: 열
maze = [[0 for _ in range(m)] for _ in range(n)]    # 채울 숫자 사각형
dirs = ((1,0),(0,1),(-1,0),(0,-1))                  # 하/우/상/좌

r_cnt, c_cnt = n, m-1       # 채울 행과 열의 개수
cur_direction = 0           # 하 방향부터 시작
x, y = -1, 0                # 시작점
num = 0                     # 채우는 값

def write_num():
    global num, x, y, r_cnt, c_cnt
    num += 1    # 숫자 증가
    x, y = x+dirs[cur_direction][0], y+dirs[cur_direction][1]   # 채울 위치
    maze[x][y] = num    # 채우기

while True:
    if num == n*m: break        # 모든 칸을 채웠으면 나가기
    if cur_direction % 2 == 0:  # 하/상 방향이라면
        for _ in range(r_cnt):  # 채울 행의 개수만큼
            write_num()
        r_cnt -= 1              # 다음 행에서는 1만큼 감소한 개수만큼 채우기
    else:                       # 우/좌 방향이라면
        for _ in range(c_cnt):  # 채울 열의 개수만큼
            write_num()
        c_cnt -= 1              # 다음 열에서는 1만큼 감소한 개수만큼 채워야 함   
    cur_direction = (cur_direction+1)%4     # 다음 방향은 1 증가

for i in range(n):
    for j in range(m):
        print(amze[i][j], end=' ')
    print()
    
'''
2023.10.29 해설
'''

n, m = tuple(map(int, input().split()))
answer = [
    [0] * m
    for _ in range(n)
]

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < m

dxs, dys = [0,1,0,-1], [1,0,-1,0]
x, y = 0,0      # 시작은 (0,0)
dir_num = 1     # 0: 오른쪽, 1: 아래쪽, 2: 왼쪽, 3: 위쪽


# 처음 시작 위치에 초깃값을 적음
answer[x][y] = 1

# n*m번 진행
for i in range(2, n*m+1):
    # 나아갈 수 있을 때까지 방향을 바꿔가며 확인
    while True:
        # 현재 방향 dir을 기준으로 그 다음 위치값을 계산
        nx, ny = x + dxs[dir_num], y + dys[dir_num]
        
        # 그 위치로 나아갈 수 있는지 확인
        if in_range(nx,ny) and answer[nx][ny] == 0:
            # 나아갈 수 있다면 위치를 갱신하고 배열에 올바른 값을 채워넣음
            x, y = nx, ny
            answer[x][y] = i
            break
        else:
            # 나아갈 수 없다면 반시계 방향으로 90도 회전
            # 그 다음 방향을 확인해봐야 함
            dir_num = (dir_num+3)%4
# 출력:
for i in range(n):
    for j in range(m):
        print(answer[i][j], end=' ')
    print()