# 실수 1: tmpMaze[minI][minJ] += maze[i][j]  # 여기에 i, j가 아니라 nx, ny를 씀
# 실수 2: 회전할 때 내구도 감소 안했음, 내구도 감소할때 +가 아니라 -로 함
# 실수 3: 출력할 때 +1씩 안함
# 실수 4:     for i in range(N - minLen+1): for j in range(N - minLen+1): 여기서 범위 설정을 +1 안해줌

N, M, K = map(int, input().split())  # N: 미로 크기, M: 참가자 수, K: 게임 시간
maze = [
    list(map(int, input().split()))  # 미로 입력받기
    for _ in range(N)
]
for i in range(N):
    for j in range(N):
        maze[i][j] *= -1  # 미로의 벽 내구도는 해당 값의 음수값

for _ in range(M):
    x, y = map(int, input().split())
    maze[x - 1][y - 1] += 1  # 참가자 수 추가

x, y = map(int, input().split())
maze[x - 1][y - 1] = -10  # 출구 표시
moved_cnt = 0  # 모든 참가자들의 이동 거리 합


def move_all():  # 모든 참가자를 한 칸씩 움직이는 함수
    global moved_cnt
    tmpMaze = [[0 for _ in range(N)] for _ in range(N)]
    exit_loc = find_exit()
    # 이제 전체 격자를 보면서 참가자를 이동해줄껀데
    for i in range(N):
        for j in range(N):
            if maze[i][j] == 0: continue  # 일단 빈칸이면 무시
            if maze[i][j] < 0:  # 벽이 존재하거나 출구면 그대로 복사
                tmpMaze[i][j] = maze[i][j]
                continue
            ################이제부터 참가자들 옮길 것###################
            # 상하좌우 보면서 최단거리 작은 것을 보기
            dirs = ((-1, 0), (1, 0), (0, -1), (0, 1))  # 상하->좌우 우선순위
            minI, minJ, minLength = i, j, abs(i - exit_loc[0]) + abs(j - exit_loc[1])
            for d in range(4):
                nx, ny = i + dirs[d][0], j + dirs[d][1]
                if nx < 0 or nx >= N or ny < 0 or ny >= N: continue  # 범위 벗어나면 무시
                if -9 <= maze[nx][ny] and maze[nx][ny] <= -1: continue  # 벽이 존재하면 무시

                # 이제 갈 수 있는 곳중 출구와 가까워지는 곳을 찾기
                if minLength > abs(nx - exit_loc[0]) + abs(ny - exit_loc[1]):
                    minI, minJ, minLength = nx, ny, abs(nx - exit_loc[0]) + abs(ny - exit_loc[1])
            if minI == i and minJ == j:
                # 만약 움직일 수 없다면
                tmpMaze[i][j] += maze[i][j]  # 그 칸에 참가자 그대로 복사
                continue
            # 만약 움직일 수 있다면
            moved_cnt += maze[i][j]
            # 만약 그곳이 출구라면
            if maze[minI][minJ] == -10: continue
            tmpMaze[minI][minJ] += maze[i][j]  # 그게 아니라면 이동한 곳에 참가자 수 증가

    # 그다음 tmpMaze 다시 복사
    for i in range(N):
        for j in range(N):
            maze[i][j] = tmpMaze[i][j]


def isFinish():  # 모든 참가자 탈출에 성공했는지 확인(종료 조건)
    for i in range(N):
        for j in range(N):
            if maze[i][j] > 0:
                return False
    return True


def subRotate(r, c, minLen):  # 좌상단 (r,c)에서 시작하면서 길이가 minLen인 정사각형을 시계방향으로 90도 회전
    tmpMaze = [[0 for _ in range(N)] for _ in range(N)]  # 원래 사각형 (r,c) => (0,0)에서 시작하도록
    subMaze = [[0 for _ in range(N)] for _ in range(N)]  # 조그만 사각형을 회전

    for i in range(r, r + minLen):
        for j in range(c, c + minLen):
            tmpMaze[i - r][j - c] = maze[i][j]
    # 시계 방향으로 90도 회전하면서 내구도 감소
    for i in range(minLen):
        for j in range(minLen):
            if -9 <= tmpMaze[i][j] and tmpMaze[i][j] <= -1:
                tmpMaze[i][j] += 1
            subMaze[j][minLen - i - 1] = tmpMaze[i][j]

    for i in range(r, r + minLen):
        for j in range(c, c + minLen):
            maze[i][j] = subMaze[i - r][j - c]


def rotate():  # 한 명 이상의 참가자와 출구를 포함한 가장 작은 정사각형 잡아서 회전
    minLen = 11
    exit_loc = find_exit()
    for i in range(N):
        for j in range(N):
            if maze[i][j] > 0:  # 참가자가 있다면
                cur_min = max(abs(i - exit_loc[0]), abs(j - exit_loc[1])) + 1
                if minLen > cur_min:
                    minLen = cur_min

    r, c = 100, 100     # 가장 작은 정사각형의 최상단 위치
    find_flag = False
    for i in range(N - minLen+1):
        for j in range(N - minLen+1):
            # 현재 위치 (i,j)에서 시작하는 정사각형을 볼 것임
            person_flag, exit_flag = False, False
            for x in range(i, i + minLen):
                for y in range(j, j + minLen):
                    if maze[x][y] > 0: person_flag = True
                    if maze[x][y] == -10: exit_flag = True
            if person_flag and exit_flag:
                find_flag = True
                r, c = i, j
                break
        if find_flag:
            break
    subRotate(r, c, minLen)  # 좌상단 (r,c)에서 시작하면서 길이가 minLen인 정사각형을 시계방향으로 90도 회전


def find_exit():
    for i in range(N):
        for j in range(N):
            if maze[i][j] == -10:
                return (i, j)


# K초 동안 게임 반복
for time in range(1, K + 1):
    # Step1. 모든 참가자는 한 칸씩 움직임
    move_all()
    # Step2. 움직인 후에 모든 참가자 탈출에 성공했는지 확인(종료 조건)
    if isFinish():
        break
    # Step3. 미로 회전
    rotate()

print(moved_cnt)
exit_loc = find_exit()
print(exit_loc[0] + 1, exit_loc[1] + 1)