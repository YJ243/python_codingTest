'''
2023.10.12
- 시간이 줄어들었는가?
    1시간

- 실수가 줄어들었는가?
    1) 배열 옮길 때 tmpMaze를 그냥 maze라고 쓰면서 잘못 옮김
       이것때문에 찾느라 또 많이 시간 잡아먹음..=> 반복되는 실수!!!!
    2) 중간 중간에 자잘한 실수를 또 많이 했음
    3) 중간에 내가 하나의 함수를 잘 짰는지 계속 체크해야함. 하나 만들고 하나 체크하고
       안그러면 나중에 다 짜고 어떤 함수에서 로직을 잘못 구현했는지 한번에 확인하려고 하면 어려움
    4) 그래도 입력이 (1,1)로 들어왔을 때 격자 범위(0,0)에서 시작하도록 하였고,
       나중에 바꿔줘야하는건 계속 생각하다보니 범위가 틀리지는 않았음
    5) 다 이동하고 종료조건을 확인해야하는데, 이동하고 돌고 종료조건을 확인하니
       이동했을 때 출구로 다 빠져나가고! 그러다보니 참가자가 없는 상태에서 돌도록 하여 범위가 초과하였음
    6) 시뮬레이션이면 종료 조건을 어디다가 걸어야되는지도 잘 확인하기!!
    7) 참가자들 한꺼번에 움직일 떄 만약 벽이 나왔으면 벽만 옮기고 continue를 했어야 하는데 continue를 안해서 또 그 벽에서 뭘 이동하고 그렇게 됨
    8)             if minI == i and minJ == j: # 그런데 바뀌지 않았다면
                tmpMaze[i][j] += maze[i][j]     # 원래 자리에 있는 참가자수 그대로 복사
                continue
                여기서도 continue 뺴먹음!
    9) 그리고 마지막에 회전할 때 -1을 안해줌!!! (조건 빼먹은거 없는지 풀면서, 그리고 풀고 나서 확인!!!)
    10) 사각형 찾아나갈 떄 범위를 N-minLength까지 해야하는데 그냥 N까지 간다고해서 범위에서 오류남
    11) 옮겨갈 떄 바로 대입이 아니라 +=으로 더해주어야 함!!!!
'''
N, M, K = map(int, input().split())                         # N: 미로 크기, M: 참가자 수, K: 게임 시간
maze = [list(map(int, input().split())) for _ in range(N)]  # 격자
for i in range(N):
    for j in range(N):
        maze[i][j] *= -1            # 미로의 내구도는 각 격자 값의 음수값

for _ in range(M):                  # 참가자 수 증가
    x, y = map(int, input().split())
    maze[x-1][y-1] += 1
x, y = map(int, input().split())
maze[x-1][y-1] = -10                # 출구는 -10

moved_cnt = 0                       # 모든 참가자들의 이동 거리 합

def find_exit():        # 출구 좌표 찾는 함수
    for i in range(N):
        for j in range(N):
            if maze[i][j] == -10:
                return (i,j)
    return (-1,-1)

def isFinish():         # 종료 조건 확인 함수
    for i in range(N):
        for j in range(N):
            if maze[i][j] > 0: return False     # 참가자가 한 명이라도 발견되면 아직 안끝남
    return True

def move_all():         # 모든 참가자를 한 칸씩 움직임
    global moved_cnt
    tmp_maze = [[0 for _ in range(N)] for _ in range(N)]        # 이동을 위해 임시 미로 만들기
    exit_l = find_exit()    # 출구 좌표
    # 원래 미로에서 하나씩 보면서 탐색할 것인데, 바뀔 수 있는 것은
    for i in range(N):
        for j in range(N):
            if maze[i][j] == 0: continue        # 빈칸이면 패스
            if -9 <= maze[i][j] and maze[i][j] <= -1:
                tmp_maze[i][j] = maze[i][j]      # 벽이면 복사
                continue
            # 이제 사용자가 있는 칸임
            dirs = ((-1,0),(1,0),(0,-1),(0,1))        # 상하->좌우 우선순위
            minI, minJ, minD = i, j, abs(i-exit_l[0])+abs(j-exit_l[1])  # 최단거리 확인
            for d in range(4):      # 상하좌우 우선순위로 확인
                nx, ny = i+dirs[d][0], j + dirs[d][1]
                if nx < 0 or nx >= N or ny < 0 or ny >= N: continue     # 만약 범위를 넘어가면 무시
                if -9 <= maze[nx][ny] and maze[nx][ny] <= -1: continue  # 벽이면 무시
                curD = abs(nx-exit_l[0])+abs(ny-exit_l[1])              # 현재 출구까지 거리
                if minD > curD: # 만약 현재 거리가 더 작다면
                    minI, minJ, minD = nx, ny, curD
            # 네 방향 모두 탐색했어
            if minI == i and minJ == j: # 그런데 바뀌지 않았다면
                tmp_maze[i][j] += maze[i][j]     # 원래 자리에 있는 참가자수 그대로 복사
                continue
            moved_cnt += maze[i][j]             # 해당 칸에 있는 참가자 수만큼 움직임
            if maze[minI][minJ] == -10: continue# 출구라면 복사하지 않고 바로 넘어가기
            tmp_maze[minI][minJ] = maze[i][j]    # 그게 아니면 해당 칸에 복사
    # tmp_maze를 maze로 옮기기
    for i in range(N):
        for j in range(N):
            maze[i][j] = tmp_maze[i][j]

def subRotate(r, c, minLength): # 안에 있는 정사각형 회전하는 함수
    # 출구와 참가자 최소 한 명을 포함한 가장 작은 정사각형 회전하기
    subMaze = [[0 for _ in range(minLength)] for _ in range(minLength)] # (r,c) => (0,0)
    tmpMaze = [[0 for _ in range(minLength)] for _ in range(minLength)]
    
    
    for i in range(r, r+minLength):
        for j in range(c, c+minLength):
            if -9 <= maze[i][j] and maze[i][j] <= -1:
                subMaze[i-r][j-c] = maze[i][j] + 1
            elif maze[i][j] == 0: continue
            else: 
                subMaze[i-r][j-c] = maze[i][j]
    
    for i in range(minLength):
        for j in range(minLength):
            tmpMaze[j][minLength-i-1] = subMaze[i][j]
    for i in range(r, r+minLength):
        for j in range(c, c+minLength):
            maze[i][j] = tmpMaze[i-r][j-c]
            
def rotate():           # 회전하는 함수
    exit_l = find_exit()        # 출구 좌표
    minLength = 21              # 출구와 참가자 최소 1명을 포함한 가장 작은 정사각형 한 변의 길이
    for i in range(N):
        for j in range(N):
            if maze[i][j] > 0:  # 만약 참가자가 있다면
                curLength = max(abs(i-exit_l[0]), abs(j-exit_l[1]))+1      # 둘 중 한 변이 큰 쪽이 정사각형의 한 변이 됨
                if minLength > curLength:
                    minLength = curLength           # 현재 최소 길이를 넣기
    # 이제 그 정사각형의 왼쪽 최상단 좌표를 찾아야 함
    square_flag = False
    r, c = 100, 100
    for i in range(N-minLength+1):
        for j in range(N-minLength+1):
            person_flag, exit_flag = False, False
            # 현재 왼쪽 최상단 좌표는 (i,j)
            for x in range(i, i+minLength):
                for y in range(j, j+minLength):
                    if maze[x][y] == -10: exit_flag = True # 출구 있고
                    if maze[x][y] > 0: person_flag = True   # 참가자 있고
            if person_flag and exit_flag:
                r, c = i,j
                square_flag = True
                break
        if square_flag:
            break
    subRotate(r, c, minLength)
        

# 시뮬레이션 시작
for time in range(1, K+1):
    # Step1. 1초마다 모든 참가자는 한 칸씩 움직임
    move_all()
    # Step2. 종료 조건 확인
    if isFinish(): break
    # Step3. 미로 회전
    rotate()
    
print(moved_cnt)                        # 이동 거리 합 출력
final_exit = find_exit()
print(final_exit[0]+1, final_exit[1]+1) # 출구 좌표 출력