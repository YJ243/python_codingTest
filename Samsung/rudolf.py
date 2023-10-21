'''
2023.10.17
'''
# 풀이 첫번째, TC1, TC3만 맞음
N, M, P, C, D = map(int, input().split())           # N: 격자 크기, M: 게임 턴 수, P: 산타 수, C: 루돌프 힘, D: 산타 힘
maze = [[0 for _ in range(N)] for _ in range(N)]    # 게임판
# 0     : 빈칸
# 양수  : 그 칸에 있는 산타 번호
# -1    : 루돌프
r,c = map(int, input().split())
maze[r-1][c-1] = -1                         # 루돌프 위치 표시
santa_loc = [None for _ in range(P+1)]      # santa_loc[i]: i번 산타의 위치
santa_score = [0 for _ in range(P+1)]       # santa_score[i]: i번 산타의 점수
time_lock = [0 for _ in range(P+1)]         # time_lock[i]: i번 산타의 타임락, 해당 값까지는 움직이지 못함
INF = 5001
for _ in range(P):
    p, r, c = map(int, input().split())
    santa_loc[p] = (r-1, c-1)               # 산타 번호에 위치 담기
    maze[r-1][c-1] = p                      # 해당 산타 번호 격자에 넣기


def isFinish():
    for i in range(N):
        for j in range(N):
            if maze[i][j] > 0:              # 산타가 한 명이라도 발견된다면
                return False
    return True             # P명의 산타가 모두 게임에서 탈락하면 True 리

def find_rudolf():
    for i in range(N):
        for j in range(N):
            if maze[i][j] == -1:
                return (i,j)

def correlate(s_x, s_y, moving_I, moving_J, nextI, nextJ): # (s_x, s_y)부터 시작해서 (nextI, nextJ)까지 (moving_I, moving_J)방향으로 연쇄적으로 1칸씩 산타를 밀어내기
    while True:     # 범위 안에 있으면서도 연속된 산타를 만날때까지
        n_x, n_y = s_x+moving_I, s_y+moving_J
        if not in_range(n_x, n_y) or maze[n_x][n_y]==0:  # 범위 안에 없거나 빈칸이면
            break
        s_x, s_y = n_x, n_y
    # 해당 줄에 연속으로 산타가 있을 때 맨 마지막 산타의 위치는 (s_x, s_y)임
    # 이제 거꾸로 (s_x,s_y)에서 (nextI, nextJ)까지 반대방향으로 한칸씩 이동하고
    # (x,y)에 있는 산타를 (nextI, nextJ)로 옮겨주면 됨
    if s_x == nextI and s_y == nextJ:                 # 만약 밀려난 곳 옆에 산타가 없다면, (nextI,nextJ) 산타만 한칸 옆으로 옮겨주면 됨
        if not in_range(n_x, n_y):                    # 그런데 산타 다음이 범위를 벗어난다면
            # 그 산타는 게임에서 탈락
            time_lock[maze[s_x][s_y]] = INF
            santa_loc[maze[s_x][s_y]] = None
            maze[s_x][s_y] = 0
        else:                                         # 밀려난 곳 옆에 산타가 없고, 범위를 벗어나지 않으면 옮기기
            maze[n_x][n_y] = maze[s_x][s_y]           # 움직이려는 곳으로 이동해주고
            santa_loc[maze[n_x][n_y]] = (n_x, n_y)
    
    else:                                             # 만약 (nextI, nextJ) 옆에도 계속 산타가 있다면
    # 맨 마지막 산타의 위치는 (s_x, s_y)임, 이제 (s_x,s_y)에서 (nextI, nextJ)까지 옮기기
        while (s_x != nextI or s_y != nextJ):
            if not in_range(s_x+moving_I,s_y+moving_J):       # 연속 산타 맨 마지막에서 한칸 더갔을 때 범위를 벗어난다면
                time_lock[maze[s_x][s_y]] = INF
                santa_loc[maze[s_x][s_y]] = None
                maze[s_x][s_y] = 0
            else:
                maze[s_x+moving_I][s_y+moving_J] = maze[s_x][s_y] # 범위를 벗어나지 않으면 옮기기
                santa_loc[maze[s_x+moving_I][s_y+moving_J]] = (s_x+moving_I,s_y+moving_J) # 위치 업데이트해주기
            s_x = s_x-moving_I
            s_y = s_y-moving_J

def in_range(x,y):
    return 0 <= x and x < N and 0 <= y and y < N

def bump(x,y,toI,toJ,moving_rudolf):      # (x,y)로 (toI, toJ) 방향으로 옮겨 왔을 때 충돌 처리
    # bump(santa_x, santa_y, bestX, bestY, 0) # 해당 좌표와 방향을 인자로 받는 충돌함수로 보내기
    rudolf_x, rudolf_y = find_rudolf()
    moving_len, moving_I, moving_J = 0,0,0

    
    if moving_rudolf:   # 만약 움직인 것이 루돌프라면                                     
        moving_len = C
        moving_I, moving_J = toI, toJ                           # 루돌프가 움직인 방향으로 밀려나기
        nextI, nextJ = x+moving_I*moving_len, y+moving_J*moving_len # 3. (x,y)에 있는 산타가 (movingI, movingJ) 방향으로 moving_len만큼 이동할 좌표
    else:               # 만약 움직인 것이 산타라면                                             
        moving_len = D
        moving_I, moving_J = -toI, -toJ                          # 산타가 움직인 방향 반대로 밀려나기
        nextI, nextJ = rudolf_x+moving_I*moving_len, rudolf_y+moving_J*moving_len
    santa_score[maze[x][y]] += moving_len                       # 1. (x,y)에 있는 산타 점수 플러스
    time_lock[maze[x][y]] = turn+1                              # 2. (x,y)에 있는 산타 (turn+1)까지 기절

    
    # Step1. 루돌프와 부딪혀 밀려난 곳이 게임 밖이라면
    if not in_range(nextI, nextJ):
        # (x,y) 위치에 있는 산타는 게임에서 탈락
        time_lock[maze[x][y]] = INF         # 락을 최대로 걸어서 더이상 게임 진행 못하도록 함
        santa_loc[maze[x][y]] = None        # 산타 위치는 없는 곳으로
        maze[x][y] = 0                      # 격자 빈칸으로 만들기
        return
    
    # Step2. 루돌프와 부딪혀 밀려난 곳이 게임 안인데, 다른 산타가 없다면
    if maze[nextI][nextJ] == 0:             
        maze[nextI][nextJ] = maze[x][y]                 # 밀려난 곳으로 산타 옮기기
        santa_loc[maze[nextI][nextJ]] = (nextI, nextJ)  # 좌표 업데이트
        maze[x][y] = 0                                  # 원래 있던 좌표를 0으로 만들기
        return

    # Step3. 루돌프와 부딪혀 밀려난 곳이 게임 안인데, 그 위치에 다른 산타가 있다면
    else:
        if maze[nextI][nextJ] == maze[x][y]:
            # 안옮기면 되니까 리턴
            return
        else:
            s_x, s_y = nextI, nextJ   # 처음 산타가 밀려날 곳
            # 3-1. 상호작용하기: 해당 방향에서 연속된 산타 1칸씩 밀려나기
            correlate(s_x, s_y, moving_I, moving_J, nextI, nextJ)

            # 1번째 산타 옮겨주기
            maze[nextI][nextJ] = maze[x][y]     # 밀려난 곳으로 산타 옮기기
            santa_loc[maze[nextI][nextJ]] = (nextI, nextJ)  # 좌표 업데이트
            maze[x][y] = 0
        


def move_rudolf():
    rudolf_x, rudolf_y = find_rudolf()
    # Step1. 가장 가까운 산타, (r->c) 우선순위로 선택
    bestI, bestJ, bestIdx, minLen = 0,0,0,INF
    for i in range(N-1, -1, -1):
        for j in range(N-1, -1, -1):                # r->c가 큰 순으로 탐색
            if maze[i][j] <= 0: continue            # 만약 산타가 없다면 무시
            if santa_loc[maze[i][j]] == (-1,-1):    # 만약 산타가 탈락했다면 무시
                continue
            curL = (i-rudolf_x)*(i-rudolf_x) + (j-rudolf_y)*(j-rudolf_y)
            if minLen > (i-rudolf_x)*(i-rudolf_x) + (j-rudolf_y)*(j-rudolf_y):  # 가장 가까운 산타를 선택
                bestI, bestJ, bestIdx, minLen = i, j, maze[i][j], (i-rudolf_x)*(i-rudolf_x) + (j-rudolf_y)*(j-rudolf_y)

    # Step2. 1칸 전진
    minI, minJ, minL, toI,toJ = 0,0,INF,0,0
    for i in (-1,0,1):
        for j in (-1,0,1):
            nx, ny = i+rudolf_x, j+rudolf_y
            if nx < 0 or nx >= N or ny < 0 or ny >= N: continue  # 범위를 벗어나면 무시
            curL = (nx-bestI)*(nx-bestI) + (ny-bestJ)*(ny-bestJ) # 현재 위치에서 가장 가까운 산타까지의 거리
            if minL > curL:
                minI, minJ, minL, toI, toJ = nx, ny, curL,i,j                    # 현재 값을 가장 작다고 업데이트

    # Step3. 만약 부딪히면: bump
    if maze[minI][minJ] > 0:    # 만약 움직인 곳에 산타가 있으면
        bump(minI, minJ, toI, toJ, 1)        # 해당 좌표와 방향을 인자로 받는 충돌함수로 보내기
    maze[minI][minJ] = maze[rudolf_x][rudolf_y]     # 옮겨간 좌표에 루돌프 표시
    maze[rudolf_x][rudolf_y] = 0                    # 원래 있던 자리는 빈칸으로 만들기

def move_santa(idx):    # idx번 산타를 움직임
    rudolf_x, rudolf_y = find_rudolf()  # 루돌프 위치
    santa_x, santa_y = santa_loc[idx][0], santa_loc[idx][1]
    bestI, bestJ, bestX, bestY,minLen = 0,0,0,0,(santa_x-rudolf_x)*(santa_x-rudolf_x)+(santa_y-rudolf_y)*(santa_y-rudolf_y)
    dirs = ((-1,0),(0,1),(1,0),(0,-1))   # 상우하좌 우선순위에 맞춰 움직이기
    # Step1. 루돌프랑 가장 가까워지는 방향으로 이동하기

    for d in range(4):
        nx, ny = santa_loc[idx][0]+dirs[d][0], santa_loc[idx][1]+dirs[d][1]
        if not in_range(nx,ny): continue    # 범위를 벗어나면 무시
        if maze[nx][ny] > 0: continue       # 루돌프가 있다면 무시
        curL = (nx-rudolf_x)*(nx-rudolf_x)+ (ny-rudolf_y)*(ny-rudolf_y)
        if curL < minLen:   # minLen보다 현재 길이가 작다면
            bestI, bestJ, bestX, bestY, minLen = nx, ny, dirs[d][0], dirs[d][1], curL
    
    if minLen == (santa_x-rudolf_x)*(santa_x-rudolf_x)+(santa_y-rudolf_y)*(santa_y-rudolf_y):   # 만약 움직일 수 있는 칸이 없다면
        return

    if maze[bestI][bestJ] == -1:    # 만약 움직인 곳에 루돌프가 있으면
        bump(santa_x, santa_y, bestX, bestY, 0) # 해당 좌표와 방향을 인자로 받는 충돌함수로 보내기
    else:

        maze[santa_loc[idx][0]][santa_loc[idx][1]] = 0                    # 원래 있던 자리는 빈칸으로 만들기
        maze[bestI][bestJ] = idx                                          # 산타 옮기기
        santa_loc[idx] = (bestI, bestJ)



for turn in range(1,M+1):   # 1부터 M번의 턴을 돌면서
    # Step0. 종료 조건 확인
    if isFinish(): break

    # Step1. 루돌프 이동
    move_rudolf()

    # Step2. 1번부터 P번까지 산타 순서대로 이동

    for i in range(1, P+1):
        if santa_loc[i] == None: continue       # 탈락한 산타는 넘어가기
        if time_lock[i] >= turn: continue       # 아직 타임락이 걸려있다면 넘어가기
        move_santa(i)

    # Step3. 매 턴 이후 아직 탈락하지 않은 산타에게 1점씩 부여
    for i in range(1, P+1):
        if santa_loc[i] != None:
            santa_score[i] += 1


for i in range(1, P+1):
    print(santa_score[i], end=' ')