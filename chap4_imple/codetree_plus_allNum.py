'''
2023.11.02
이동경로상에 있는 모든 숫자 더하기
https://www.codetree.ai/missions/5/problems/add-all-the-numbers-on-the-path?&utm_source=clipboard&utm_medium=text
'''
N, T = map(int, input().split())    # N: 정사각형 크기, T: 명령 개수
query = list(input())

a = [list(map(int, input().split())) for _ in range(N)]
dirs = ((-1,0),(0,1),(1,0),(0,-1))   # 북,동,남,서
cur_d = 0
x, y = N // 2, N // 2
result = a[x][y]
for i in range(T):
    cmd = query[i]
    if cmd == 'L':
        cur_d = (cur_d -1 + 4)%4
    elif cmd == 'R':
        cur_d = (cur_d+1)%4
    else:
        nx, ny = x+dirs[cur_d][0], y+dirs[cur_d][1]
        if nx < 0 or nx >= N or ny < 0 or ny >= N:
            continue
        x, y = nx,ny
        result += a[x][y]
print(result)

'''
해설
'''

# 변수 선언 및 입력:
n, t = tuple(map(int, input().split()))
commands = input()
board = [
    list(map(int, input().split()))
    for _ in range(n)
]

ans = 0

# 초기 시작 위치를 설정하기
x, y, move_dir = n//2, n//2, 0

def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

def simulate():
    global ans
    global x, y, move_dir
    
    dxs = [-1,0,1,0]
    dys = [0,1,0,-1]
    
    for command in commands:
        # R 명령이 나올 경우 방향을 오른쪽으로 바꿔줌
        if command == 'R':
            move_dir = (move_dir+1) % 4
        # L 명령이 나올 경우 방향을 왼쪽으로 바꿔줌
        elif command == 'L':
            move_dir = (move_dir+3) % 4
        else:
            # 해당 방향으로 돌진
            nx, ny = x + dxs[move_dir], y + dys[move_dir]
            # 이동할 수 있는 칸이면 이동
            # 해당 칸 안에 있는 숫자를 정답에 더해줌
            if in_range(nx,ny):
                ans += board[nx][ny]
                x, y = nx, ny

ans += board[x][y]
simulate()

# 정답을 출력
print(ans)