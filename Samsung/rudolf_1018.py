'''
2023.10.18
'''
N, M, P, C, D = map(int, input().split())  # N: 격자 크기, M: 게임 턴 수, P: 산타 수, C: 루돌프 힘, D: 산타 힘
maze = [[0 for _ in range(N)] for _ in range(N)]  # 게임판
# 0     : 빈칸
# 양수  : 그 칸에 있는 산타 번호
# -1    : 루돌프
r, c = map(int, input().split())
maze[r - 1][c - 1] = -1  # 루돌프 위치 표시
santa_loc = [None for _ in range(P + 1)]  # santa_loc[i]: i번 산타의 위치
santa_score = [0 for _ in range(P + 1)]  # santa_score[i]: i번 산타의 점수
time_lock = [0 for _ in range(P + 1)]  # time_lock[i]: i번 산타의 타임락, 해당 값까지는 움직이지 못함
INF = 5001
for _ in range(P):
    p, r, c = map(int, input().split())
    santa_loc[p] = (r - 1, c - 1)  # 산타 번호에 위치 담기
    maze[r - 1][c - 1] = p  # 해당 산타 번호 격자에 넣기


def isFinish():
    for i in range(N):
        for j in range(N):
            if maze[i][j] > 0:  # 산타가 한 명이라도 발견된다면
                return False
    return True  # P명의 산타가 모두 게임에서 탈락하면 True 리턴

def find_rudolf():
    for i in range(N):
        for j in range(N):
            if maze[i][j] == -1:
                return (i, j)

def correlate(s_x, s_y, moving_I, moving_J, nextI, nextJ):  # (nextI, nextJ)는 착지하는 칸
    # (s_x, s_y)부터 시작해서 (nextI, nextJ)까지 (moving_I, moving_J)방향으로 연쇄적으로 1칸씩 산타를 밀어내기
    while True:  # 범위 안에 있으면서도 연속된 산타를 만날때까지
        n_x, n_y = s_x + moving_I, s_y + moving_J
        if not in_range(n_x, n_y) or maze[n_x][n_y] == 0:  # 범위 안에 없거나 빈칸이면
            break
        s_x, s_y = n_x, n_y  # 그 다음 칸 탐색

    # 해당 줄에 연속으로 산타가 있을 때 맨 마지막 산타의 위치는 (s_x, s_y)임
    # 이제 거꾸로 (s_x,s_y)에서 (nextI, nextJ)까지 반대방향으로 한칸씩 이동하고
    # (x,y)에 있는 산타를 (nextI, nextJ)로 옮겨주면 됨
    if s_x == nextI and s_y == nextJ:  # 만약 밀려난 곳 옆에 산타가 없다면, (nextI,nextJ) 산타만 한칸 옆으로 옮겨주면 됨
        if not in_range(s_x + moving_I, s_y + moving_J):  # 그런데 산타 다음이 범위를 벗어난다면
            # 그 산타는 게임에서 탈락
            time_lock[maze[s_x][s_y]] = INF
            santa_loc[maze[s_x][s_y]] = None
            maze[s_x][s_y] = 0
        else:  # 밀려난 곳 옆에 산타가 없고, 범위를 벗어나지 않으면 옮기기
            maze[s_x + moving_I][s_y + moving_J] = maze[s_x][s_y]  # 움직이려는 곳으로 이동해주고
            santa_loc[maze[s_x + moving_I][s_y + moving_J]] = (s_x + moving_I, s_y + moving_J)

    else:  # 만약 (nextI, nextJ) 옆에도 계속 산타가 있다면
        # 맨 마지막 산타의 위치는 (s_x, s_y)임, 이제 (s_x,s_y)에서 (nextI, nextJ)까지 옮기기
        while (s_x != nextI or s_y != nextJ):
            if not in_range(s_x + moving_I, s_y + moving_J):  # 연속적으로 줄지어 있는 산타 맨 마지막에서 한칸 더갔을 때 범위를 벗어난다면
                time_lock[maze[s_x][s_y]] = INF
                santa_loc[maze[s_x][s_y]] = None
                maze[s_x][s_y] = 0
            else:
                maze[s_x + moving_I][s_y + moving_J] = maze[s_x][s_y]  # 범위를 벗어나지 않으면 옮기기
                maze[s_x][s_y] = 0
                santa_loc[maze[s_x + moving_I][s_y + moving_J]] = (s_x + moving_I, s_y + moving_J)  # 위치 업데이트해주기
            # 반대로 탐색하면서 (nextI, nextJ)까지 가기
            s_x = s_x - moving_I
            s_y = s_y - moving_J
        maze[s_x + moving_I][s_y + moving_J] = maze[s_x][s_y]  # 범위를 벗어나지 않으면 옮기기
        maze[s_x][s_y] = 0
        santa_loc[maze[s_x + moving_I][s_y + moving_J]] = (s_x + moving_I, s_y + moving_J)  # 위치 업데이트해주기

def in_range(x, y):
    return 0 <= x and x < N and 0 <= y and y < N

def bump(x, y, toI, toJ, moving_rudolf):  # 루돌프가 (x,y)로 (toI, toJ) 방향으로 왔을 때/(x,y)의 산타가 (toI,toJ)방향으로 루돌프 충돌 처리
    # bump(santa_x, santa_y, bestX, bestY, 0) # 해당 좌표와 방향을 인자로 받는 충돌함수로 보내기
    rudolf_x, rudolf_y = find_rudolf()
    moving_len, moving_I, moving_J = 0, 0, 0

    if moving_rudolf:  # 만약 움직인 것이 루돌프라면
        moving_len = C  # 산타는 루돌프가 이동해온 방향으로 moving_len만큼 밀려남
        moving_I, moving_J = toI, toJ  # 루돌프가 움직인 방향으로 밀려나기
        nextI, nextJ = x + moving_I * moving_len, y + moving_J * moving_len  # (x,y)에 있는 산타가 (movingI, movingJ) 방향으로 moving_len만큼 이동할 좌표

    else:  # 만약 움직인 것이 산타라면
        moving_len = D  # 산타는 이동해온 반대방향으로 moving_len만큼 밀려남
        moving_I, moving_J = -toI, -toJ  # 산타가 이동해온 반대 방향으 밀려나기
        nextI, nextJ = rudolf_x + moving_I * moving_len, rudolf_y + moving_J * moving_len  # rudolf 위치에 온 산타는 반대방향으로 moving_len만큼 이동

    santa_score[maze[x][y]] += moving_len  # 1. (x,y)에 있는 산타 점수 플러스
    time_lock[maze[x][y]] = turn + 1  # 2. (x,y)에 있는 산타 (turn+1)까지 기절

    # Step1. 루돌프와 부딪혀 밀려난 곳이 게임 밖이라면
    if not in_range(nextI, nextJ):
        # (x,y) 위치에 있는 산타는 게임에서 탈락
        time_lock[maze[x][y]] = INF  # 락을 최대로 걸어서 더이상 게임 진행 못하도록 함
        santa_loc[maze[x][y]] = None  # 산타 위치는 없는 곳으로
        maze[x][y] = 0  # 격자 빈칸으로 만들기
        return

    # Step2. 루돌프와 부딪혀 밀려난 곳이 게임 안인데, 다른 산타가 없다면
    if maze[nextI][nextJ] == 0:
        maze[nextI][nextJ] = maze[x][y]  # 밀려난 곳으로 산타 옮기기
        santa_loc[maze[nextI][nextJ]] = (nextI, nextJ)  # 좌표 업데이트
        maze[x][y] = 0  # 원래 있던 좌표를 0으로 만들기
        return

    # Step3. 루돌프와 부딪혀 밀려난 곳이 게임 안인데, 그 위치에 다른 산타가 있다면
    else:
        if maze[nextI][nextJ] == maze[x][y]:  # 밀려난 곳에 산타가 자기 자신이면
            # 안옮기면 되니까 리턴
            return
        else:  # 밀려난 곳에 다른 산타가 있다면
            s_x, s_y = nextI, nextJ  # 밀려난 곳을 처음 start로 잡기

            # 3-1. 상호작용하기: 해당 방향에서 연속된 산타 1칸씩 밀려나기
            correlate(s_x, s_y, moving_I, moving_J, nextI, nextJ)

            # 1번째 산타 옮겨주기
            maze[nextI][nextJ] = maze[x][y]  # 밀려난 곳으로 산타 옮기기
            santa_loc[maze[nextI][nextJ]] = (nextI, nextJ)  # 좌표 업데이트
            maze[x][y] = 0

def move_rudolf():  # 루돌프의 움직임
    rudolf_x, rudolf_y = find_rudolf()
    # Step1. 게임에서 탈락하지 않은 산타 중 가장 가까운 산타를 (r->c)이 큰 우선순위로 선택
    bestI, bestJ, bestIdx, minLen = 0, 0, 0, INF
    for i in range(N - 1, -1, -1):
        for j in range(N - 1, -1, -1):  # r->c가 큰 순으로 탐색
            if maze[i][j] <= 0: continue  # 만약 산타가 없다면 무시
            curL = pow(i - rudolf_x, 2) + pow(j - rudolf_y, 2)  # 현재 루돌프 위치에서 탐색하는 산타까지의 거리
            if minLen > curL:  # 가장 가까운 길이보다 더 가까운 곳에 산타가 위치한다면
                bestI, bestJ, bestIdx, minLen = i, j, maze[i][j], curL  # 현재 산타의 위치 담기

    # Step2. 가장 가까운 산타를 향해 1칸 전진
    minI, minJ, minL, toI, toJ = 0, 0, INF, 0, 0
    for i in (-1, 0, 1):  # 인접한 8방향 중 하나로 돌진
        for j in (-1, 0, 1):
            nx, ny = i + rudolf_x, j + rudolf_y
            if nx < 0 or nx >= N or ny < 0 or ny >= N: continue  # 범위를 벗어나면 무시
            curL = pow(nx - bestI, 2) + pow(ny - bestJ, 2)  # 현재 위치에서 가장 가까운 산타까지의 거리
            if minL > curL:  # 현재 이동한 곳이 산타까지 더 가깝다면
                minI, minJ, minL, toI, toJ = nx, ny, curL, i, j  # 이동할 좌표, 길이, 방향을 업데이트

    # Step3. 만약 부딪히면: bump
    if maze[minI][minJ] > 0:  # 만약 움직인 곳에 산타가 있으면
        bump(minI, minJ, toI, toJ, 1)  # 해당 좌표와 방향을 인자로 받는 충돌함수로 보내기
    maze[minI][minJ] = -1  # 옮겨간 좌표에 루돌프 표시
    maze[rudolf_x][rudolf_y] = 0  # 원래 루돌프가 있던 자리는 빈칸으로 만들기

def move_santa(idx):  # idx번 산타를 움직임
    rudolf_x, rudolf_y = find_rudolf()  # 루돌프 위치
    santa_x, santa_y = santa_loc[idx][0], santa_loc[idx][1]  # idx번 산타 위치
    bestI, bestJ, bestX, bestY, minLen = 0, 0, 0, 0, pow(santa_x - rudolf_x, 2) + pow(santa_y - rudolf_y, 2)
    dirs = ((-1, 0), (0, 1), (1, 0), (0, -1))  # 상우하좌 우선순위에 맞춰 움직이기
    # Step1. 루돌프랑 가장 가까워지는 방향으로 이동하기

    for d in range(4):
        nx, ny = santa_x + dirs[d][0], santa_y + dirs[d][1]
        if not in_range(nx, ny): continue  # 범위를 벗어나면 무시
        if maze[nx][ny] > 0: continue  # 다른 산타가 있다면 무시
        curL = pow(nx - rudolf_x, 2) + pow(ny - rudolf_y, 2)
        if curL < minLen:  # minLen보다 현재 길이가 작다면
            bestI, bestJ, bestX, bestY, minLen = nx, ny, dirs[d][0], dirs[d][1], curL

    if minLen == pow(santa_x - rudolf_x, 2) + pow(santa_y - rudolf_y, 2):  # 만약 움직일 수 있는 칸이 없다면
        return  # 움직이지 않음

    if maze[bestI][bestJ] == -1:  # 만약 움직인 곳에 루돌프가 있으면
        bump(santa_x, santa_y, bestX, bestY, 0)  # 해당 좌표와 방향을 인자로 받는 충돌함수로 보내기
    else:  # 바로 움직일 수 있는 곳이라면
        maze[santa_x][santa_y] = 0  # 원래 있던 자리는 빈칸으로 만들기
        maze[bestI][bestJ] = idx  # 산타 옮기기
        santa_loc[idx] = (bestI, bestJ)  # 산타 위치 업데이트

for turn in range(1, M + 1):  # 총 M개의 턴에 걸쳐 진행
    # Step0. 종료 조건 확인
    if isFinish(): break

    # Step1. 루돌프 이동
    move_rudolf()

    # Step2. 1번부터 P번 산타까지 순서대로 이동
    for i in range(1, P + 1):
        if time_lock[i] >= turn: continue  # 기절해 있는 산타는 움직이지 않음
        if santa_loc[i] == None: continue  # 탈락한 산타는 움직이지 않음
        move_santa(i)

    # Step3. 매 턴 이후 아직 탈락하지 않은 산타에게 1점씩 부여
    for i in range(1, P + 1):
        if santa_loc[i] != None:
            santa_score[i] += 1

for i in range(1, P + 1):
    print(santa_score[i], end=' ')