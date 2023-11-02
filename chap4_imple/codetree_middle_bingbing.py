'''
2023.11.02
https://www.codetree.ai/missions/5/problems/snail-start-from-center?&utm_source=clipboard&utm_medium=text
직사각형 가운데에서 시작해서 빙빙 돌며 숫자 채우기
'''
n = int(input())

a = [[1 for _ in range(n)] for _ in range(n)]
num = 1
x, y = n//2, n//2
r_cnt, c_cnt = 1,1
cur_d = 0
dirs = ((0,1),(-1,0),(0,-1),(1,0))     # 오,위,왼,아
while True:
    if num == n*n: break
    if cur_d % 2 == 0:
        for _ in range(c_cnt):
            num += 1
            x, y = x + dirs[cur_d][0], y + dirs[cur_d][1]
            a[x][y] = num
            if num == n*n: break
        c_cnt += 1
    else:
        for _ in range(r_cnt):
            num += 1
            x, y = x + dirs[cur_d][0], y + dirs[cur_d][1]
            a[x][y] = num
            if num == n*n: break
        r_cnt += 1
    
    cur_d = (cur_d+1)%4

for i in range(n):
    for j in range(n):
        print(a[i][j], end=' ')
    print()
    
'''
해설
'''

# 변수 선언 및 입력:
n = int(input())
grid = [
    [0 for _ in range(n)]
    for _ in range(n)
]

# 시작 위치와 방향,
# 해당 방향으로 이동할 횟수를 설정
curr_x, curr_y = n // 2, n // 2
move_dir, move_num = 0, 1
def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

# 한 칸 움직이면서 청소를 진행
def move():
    global curr_x, curr_y   # 현재 위치
    
    # 문제에서 원하는 진행 순서대로
    # 오른쪽, 위, 왼쪽, 아래 방향이 되도록 정의하기
    dxs, dys = [0,-1,0,1], [1,0,-1,0]
    curr_x, curr_y = curr_x+dxs[move_dir], curr_y+dys[move_dir]

def end():
    return not in_range(curr_x, curr_y)

# 시작 위치와 방향,
# 해당 방향으로 이동할 횟수를 설정
cnt = 1

while not end():
    # move_num만큼 이동 
    for _ in range(move_num):
        grid[curr_x][curr_y] = cnt
        cnt += 1
        move()
        
        # 이동하는 도중 격자를 벗어나면 종료
        if end(): break
    
    # 방향을 바꿈
    move_dir = (move_dir+1)%4
    
    # 만약 현재 방향이 왼쪽/오른쪽이 된 경우
    # 특정 방향으로 움직여야 할 횟수를 1 증가
    if move_dir == 0 or move_dir == 2:
        move_num += 1

# 출력:
for i in range(n):
    for j in range(n):
        print(grid[i][j], end=' ')
    print()