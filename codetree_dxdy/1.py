'''
2023.09.26
'''

# 변수 선언 및 입력
n = int(input())
x,y = 0,0

# 동, 서, 남, 북 순으로 dx, dy 정의
dx = [1,-1,0,0]
dy = [0,0,-1,1]

# 이동 진행
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
    x += dx[move_dir]*dist
    y += dy[move_dir]*dist

print(x,y)