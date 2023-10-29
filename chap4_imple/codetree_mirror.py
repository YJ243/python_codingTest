'''
2023.10.26 <거울에 레이저 쏘기>
N * N 크기의 격자 안에 각 칸마다 거울이 하나씩 들어 있습니다. 
각 거울은 \나 /의 형태를 띄고있고, 격자 밖 4N개의 위치 중 특정 위치에서 레이저를 쏘았을 때, 거울에 튕기는 횟수를 구하는 프로그램
https://www.codetree.ai/missions/5/problems/shoot-a-laser-in-the-mirror-2?&utm_source=clipboard&utm_medium=text

'''
N = int(input())                                        # 격자 크기
maze = [['*' for _ in range(N)] for _ in range(N)]      # 격자
for i in range(N):                                      # 격자 채우기
    line = input()
    for j in range(N):
        maze[i][j] = line[j]

k = int(input())-1      # 레이저를 쏘는 위치, (0,0) 칸으로 들어오는 곳을 0번으로 하여 시계 방향으로 돌며 가능한 시작 위치에 번호를 붙임
start = [k//N, k % N]   # 몫은 어떤 변인지(상/우/하/좌), 나머지는 몇 번째 칸인지
x, y = 0,0              # 탐색할 좌표

if start[0] == 0:               # 윗변이면
    x, y = 0, start[1]          # x좌표는 0으로 맨 윗줄, y좌표는 나머지
elif start[0] == 1:             # 오른쪽 변이면
    x, y = start[1], y = N-1    # x좌표는 나머지, y좌표는 맨 오른쪽 칸
elif start[0] == 2:             # 아래쪽 변이면
    x, y = N-1, N-1-start[1]    # x는 맨 아래칸, y는 맨 오른쪽에서 한 칸씩 줄어듦
else:                           # 왼쪽 변이면
    x, y = N-1-start[1], 0      # x는 맨 아래에서 한 칸씩 줄어듦, y는 맨 왼쪽 칸

# 상우하좌에서 들어왔을 때 나가는 방향 정의
dirs_for_0 = ((0,1),(-1,0),(0,-1),(1,0))     # 0은 '\'를 위한 네 방향
dirs_for_1 = ((0,-1),(1,0),(0,1),(-1,0))     # 1은 '/'를 위한 네 방향

def in_range(x,y):      # 격자 범위 안에 있는지 확인하는 함수
    return 0 <= x and x < N and 0 <= y and y < N

reflection_cnt = 0      # 거울에 튕기는 횟수
d = k // N              # k를 N으로 나누었을 떄 몫이 어느 방향으로 들어오는지를 나타냄

while in_range(x,y):    # 범위 안에 있을 때까지
    if maze[x][y] == "\\":      # '\'를 만났을 때(\는 Escape String이어서 \\로 검사하기)
        x, y = x + dirs_for_0[d][0], y + dirs_for_0[d][1]
        # 상->우(0->1), 우->상(1->0), 하->좌(2->3), 좌->하(3->2)
        if d % 2 == 0: d += 1
        else: d -= 1
    else:                       # '/'를 만났을 때
        x, y = x + dirs_for_1[d][1], y + dirs_for_1[d][1]
        # 상->좌(0->3), 우->하(1->2), 하->우(2->1), 좌->상(3->0)
        if d % 2 == 0: d = (d-1+4)%4
        else: d = (d+1)%4
    reflection_cnt += 1         # 반사 횟수 증가
    # 상으로 나가면 하로 들어오고, 하->상, 오->왼, 왼->오
    d = (d + 2)%4

print(reflection_cnt)
        
