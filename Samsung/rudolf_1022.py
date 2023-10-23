N, M, P, C, D = map(int, input().split())           # N: 게임판 크기, M: 게임 턴 수, P: 산타 수, C: 루돌프 힘, D: 산타 힘
maze = [[0 for _ in range(N)] for _ in range(N)]    # 0: 빈칸, -1: 산타, 양수: 산타 번호
r, c = map(int, input().split())                    # 산타 위치
maze[r-1][c-1] = -1                                 # 산타 위치 격자에 저장
santa_score = [0 for _ in range(P+1)]                # santa_score[i]: i번 산타의 점수
santa_loc = [None for _ in range(P+1)]               # santa_loc[i]: i번 산타의 위치, 만약 None이면 탈락
santa_lock = [0 for _ in range(P+1)]                 # snata_lock[i]: 해당 값까지는 움직이지 못함

for _ in range(P):
    idx, r, c = map(int, input().split())
    santa_loc[idx] = (r-1, c-1)             # 산타 위치
    maze[r-1][c-1] = idx                    # 산타 위치 격자에 저장

def print_maze():
    for i in range(N):
        for j in range(N):
            print(maze[i][j], end=' ')
        print()

def rudolf_and_santa_len(rudolf_x, rudolf_y, santa_x, santa_y):
    return (rudolf_x-santa_x)**2 + (rudolf_y-santa_y)**2

def find_rudolf():
    for i in range(N):
        for j in range(N):
            if maze[i][j] == -1:
                return (i,j)

dirs = ((-1,0),(0,1),(1,0),(0,-1),(-1,-1),(-1,1),(1,1),(1,-1))

def in_range(x,y):
    return 0 <= x and x < N and 0 <= y and y < N

def interact(firstX, firstY, diX, diY): # (firstX,firstY)부터 시작해서 diX, diY 방향으로 연쇄적으로 산타 옮기기

    # 연속적으로 이어져 있는 마지막 산타 찾기
    LastX, LastY = firstX, firstY
    while maze[LastX][LastY] > 0:
        # 한칸 옆으로 옮기기
        LastX += diX
        LastY += diY
        if not in_range(LastX, LastY):  # 만약 끝에 있는 산타가 격자 마지막 칸에 있다면
            LastX -= diX
            LastY -= diY
            break
    
    if maze[LastX][LastY] == 0: # 제일 마지막 산타 다음으로 넘어갔다면
        LastX -= diX
        LastY -= diY
    # (LastX, LastY)부터 -diX, -diY 방향으로 탐색하며 (firstX, firstY) 연쇄적으로 옮기기
    while LastX != firstX or LastY != firstY:
        if not in_range(LastX+diX, LastY+diY):  # 만약 맨 마지막 산타 옆이 범위를 벗어난다면
            santa_loc[maze[LastX][LastY]] = None
            maze[LastX][LastY] = 0
        else:
            maze[LastX+diX][LastY+diY] = maze[LastX][LastY]
            santa_loc[maze[LastX+diX][LastY+diY]] = (LastX+diX,LastY+diY)
            maze[LastX][LastY] = 0
        LastX -= diX
        LastY -= diY
    if not in_range(firstX+diX,firstY+diY):
        santa_loc[maze[firstX][firstY]] = None
        maze[firstX][firstY] = 0
    else:
        maze[firstX+diX][firstY+diY] = maze[firstX][firstY]
        santa_loc[maze[firstX+diX][firstY+diY]] = (firstX+diX,firstY+diY)
        maze[firstX][firstY] = 0


def bump(x,y, di, rudolf_flag):   # 루돌프/산타가 (x,y)위치에 di방향으로 와서 부딪혔을 때
    Length,diX,diY = 0, dirs[di][0], dirs[di][1]
    santaX, santaY = x,y
    if rudolf_flag:
        Length = C
    else:
        Length = D
        santaX = x-dirs[di][0]
        santaY = y-dirs[di][1]
        diX *= -1
        diY *= -1
    santa_score[maze[santaX][santaY]] += Length
    santa_lock[maze[santaX][santaY]] = turn+1
    # 이제 (x,y)에서 di 방향으로 Length만큼 옮겨야 함
    firstX, firstY = x + diX*Length, y + diY*Length

    if not in_range(firstX, firstY):    # 만약 포물선으로 밀려난 곳이 게임판 밖이라면 탈락
        santa_loc[maze[santaX][santaY]] = None
        maze[santaX][santaY] = 0
    else:       # 게임판 안이라면
        if maze[firstX][firstY] == maze[santaX][santaY]:
            return
        if maze[firstX][firstY] != 0:   # 밀려난 곳에 산타가 있다면
            interact(firstX, firstY, diX, diY)  # 상호작용하기
        
        # 산타를 first 자리에 옮기기
        maze[firstX][firstY] = maze[santaX][santaY]
        maze[santaX][santaY] = 0
        santa_loc[maze[firstX][firstY]] = (firstX, firstY)



def move_rudolf():
    # 1. 가장 가까운 산타 찾기
    rudolf = find_rudolf()
    bestI, bestJ, minLen = 0,0,5001
    for idx in range(1,P+1):
        if santa_loc[idx] == None: continue
        curLen = rudolf_and_santa_len(rudolf[0], rudolf[1], santa_loc[idx][0], santa_loc[idx][1])
        if minLen > curLen:
            bestI, bestJ, minLen = santa_loc[idx][0], santa_loc[idx][1], curLen
        if minLen == curLen:
            if bestI < santa_loc[idx][0] or (bestI == santa_loc[idx][0] and bestJ < santa_loc[idx][1]):
                bestI, bestJ, minLen = santa_loc[idx][0], santa_loc[idx][1], curLen
    # 2. 1칸 이동

    moveI, moveJ, moveD, moveLen = 0,0,0,minLen
    for d in range(8):
        nx, ny = rudolf[0]+dirs[d][0], rudolf[1]+dirs[d][1]
        if not in_range(nx,ny): continue
        curL = rudolf_and_santa_len(nx,ny,bestI,bestJ)
        if moveLen > curL:
            moveI, moveJ, moveD, moveLen = nx, ny, d, curL
    return moveI, moveJ, moveD


def move_santa(i):
    rudolf = find_rudolf()
    bestI, bestJ, minLen= 0,0,rudolf_and_santa_len(rudolf[0], rudolf[1], santa_loc[i][0], santa_loc[i][1])
    moveD = 0
    for d in range(4):  # 상우하좌 우선순위
        nx, ny = santa_loc[i][0]+dirs[d][0], santa_loc[i][1]+dirs[d][1]
        if not in_range(nx,ny): continue    # 범위 벗어나면 무시
        if maze[nx][ny] > 0: continue       # 산타가 있으면 무시
        curL = rudolf_and_santa_len(nx,ny,rudolf[0],rudolf[1])
        if minLen > curL:
            bestI, bestJ, minLen, moveD = nx, ny, curL, d
    
    # 네 방향 모두 탐색했는데 움직일 수 없다면 움직이지 않음
    if minLen == rudolf_and_santa_len(rudolf[0], rudolf[1], santa_loc[i][0], santa_loc[i][1]):
        return -1,-1,-1
    return bestI, bestJ, moveD


def isFinish():
    for s in range(1,P+1):
        if santa_loc[s] != None:
            return False
    return True

# 시뮬레이션 시작
for turn in range(1, M+1):

    # Step 1. 루돌프 이동
    rudolfI, rudolfJ, rudolfD = move_rudolf()
    # Step 1-1. 충돌 여부 확인
    if maze[rudolfI][rudolfJ] > 0:      # 움직인 곳에 산타가 있다면
        bump(rudolfI, rudolfJ, rudolfD, 1) # 충돌 처리
    # Step 1.2 원래 있던 루돌프 위치 바꾸기
    x,y = find_rudolf()
    maze[x][y] = 0                  
    maze[rudolfI][rudolfJ] = -1     # 루돌프 표시

    # Step 2. 1번부터 P번까지 산타 이동
    for i in range(1, P+1):
        if santa_loc[i] == None: continue           # 탈락한 산타 무시
        if santa_lock[i] >= turn: continue          # 산타의 타임락이 현재 turn수보다 크거나 같다면 무시
        santaI,santaJ,santaD = move_santa(i)        # i번 산타 움직임
        if santaI == -1 and santaJ == -1: continue  # 움직일 수 없다면 무시
        # Step 2-1. 충돌 여부 확인
        if maze[santaI][santaJ] == -1:              # 움직인 곳에 루돌프가 있으면
            bump(santaI, santaJ, santaD, 0)            # 충돌 처리
        else:
            x,y = santa_loc[i]
            maze[x][y] = 0                          # 원래 있던 산타 위치 바꾸기
            maze[santaI][santaJ] = i                # 산타 표시
            santa_loc[i] = (santaI,santaJ)

    # Step 3. 살아남은 산타들 점수 ++1 추
    for santa_idx in range(1, P+1):
        if santa_loc[santa_idx] == None: continue
        santa_score[santa_idx] += 1       # idx번 산타 점수 1 증가
        
    # Step 4. 종료 조건 확인
    if isFinish(): break


for i in range(1, P+1):
    print(santa_score[i], end=' ')