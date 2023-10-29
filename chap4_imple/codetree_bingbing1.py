'''
2023.10.29
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