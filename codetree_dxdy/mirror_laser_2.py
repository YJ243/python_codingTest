'''
2023.10.26
'''
N = int(input())    # 격자 크기
maze = [['*' for _ in range(N)]
        for _ in range(N)]

for i in range(N):
    line = input()
    for j in range(N):
        maze[i][j] = line[j]

k = int(input())
k -= 1
start = [k//N, k%N] # 1 ~ 4N까지 N개씩 집합
x, y = 0,0          # 좌표

# 시작 위치 정하기
if start[0] == 0:
    x, y = 0, start[1]
elif start[0] == 1:
    x, y = start[1], N-1
elif start[0] == 2:
    x, y = N-1, N-1-start[1]
else:
    x, y = N-1-start[1],0

# 위(0), 오른쪽(1), 아래(2), 왼쪽(3)에서 들어왔을 때 나가는 방향
dirs_for_0 = ((0,1),(-1,0),(0,-1),(1,0))     # \를 위한 네 방향 정의
dirs_for_1 = ((0,-1),(1,0),(0,1),(-1,0))     # /를 위한 네 방향 정의

def in_range(x,y):
    return 0 <= x and x < N and 0 <= y and y < N

reflection_cnt = 0
d = k // N      # k를 N으로 나눴을 때 몫이 방향의 인덱스

while in_range(x,y):
    if maze[x][y] == '\\':
        x, y = x+dirs_for_0[d][0], y+dirs_for_0[d][1]
        d = 3-d
    else:
        x, y = x+dirs_for_1[d][1], y+dirs_for_1[d][1]
        if d % 2 == 0: d = (d-1+4)%4
        else: d = (d+1)%4
    reflection_cnt += 1
    d = (d+2)%4

print(reflection_cnt)
