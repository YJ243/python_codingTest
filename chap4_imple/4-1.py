# N을 입력받기
n = int(input())
plan = input().split()

x, y = 1, 1

# L R U D
dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]
move_types = ['L','R','U','D']

# 이동 계획을 하나씩 확인
for p in plan:
    # 이동 후 좌표 구하기   
    for i in range(len(move_types)):
        if p == move_types[i]:
            nx = x + dx[i]
            ny = y + dy[i]
            
            # 공간을 벗어나는 경우 무시
            if nx < 1 or nx > n or ny < 1 or ny > n:
                break
            # 이동 수행
            x = nx
            y = ny

print(x, y)