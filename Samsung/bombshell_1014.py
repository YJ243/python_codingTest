# 실수 1: maze = [list(map(int, input().split())) for _ in range(N)]    여기서 for _ in range(N) 빼먹음
# 실수 2: if (maxP < maze[i][j]) or (maxP == maze[i][j] and minT > atk_time[i][j]): 여기서 시간 비교할때 atk_time인데 maze로 함..
# 실수 3: if nx == atk[0] and ny == atk[1]: continue ### 포탄 공격 시 공격자를 제외하지 못함
from collections import deque

N, M, K = map(int, input().split())         # N:행, M:열, K: 턴수
maze = [list(map(int, input().split())) for _ in range(N)]    # 포탑을 나타내는 격자
atk_time = [[0 for _ in range(M)] for _ in range(N)]    # 최근 공격 시간을 나타내는 배열
atk = (0,0)     # 공격자 좌표
tgt = (0,0)     # 공격대상 좌표

def isFinish():
    cnt = 0
    for i in range(N):
        for j in range(M):
            if maze[i][j] > 0:
                cnt += 1
    if cnt == 1:
        return True
    else:
        return False

def choose_attacker():      # 공격자 선정
    maxI, maxJ, minP, maxT = -1,-1,5001,0
    for sum in range(N+M-2, -1, -1):
        for j in range(M-1, -1, -1):
            i = sum - j
            if i < 0 or i >= N: continue        # 범위를 벗어나면 무시
            if maze[i][j] == 0: continue        # 부서진 포탑이면 무시
            if (minP > maze[i][j]):
                maxI, maxJ, minP, maxT = i, j, maze[i][j], atk_time[i][j]   # 공격력이 작거나, 공격력은 같은데 시간이 작으면
            elif (minP == maze[i][j] and maxT < atk_time[i][j]):   
                maxI, maxJ, minP, maxT = i, j, maze[i][j], atk_time[i][j]
    return (maxI, maxJ)
                    

def choose_target():        # 공격 타겟 선정
    minI, minJ, maxP, minT = 11,11,0,1001
    for sum in range(N+M):
        for j in range(M):
            i = sum - j
            if i < 0 or i >= N: continue        # 범위를 벗어나면 무시
            if maze[i][j] == 0: continue        # 부서진 포탑이면 무시
            if (maxP < maze[i][j]) or (maxP == maze[i][j] and minT > atk_time[i][j]):
                minI, minJ, maxP, minT = i, j, maze[i][j], atk_time[i][j]
    return (minI, minJ)

def do_attack(x, y, atk_power):
    maze[x][y] = max(maze[x][y] - atk_power, 0)
    isRelated[x][y] = True

def try_laser():            # 레이저 공격 시도
    visited = [[False for _ in range(M)] for _ in range(N)]
    visited[atk[0]][atk[1]] = True  # 공격자 방문했다 표시
    from_which = [[None for _ in range(M)] for _ in range(N)]   # 어디에서 왔다고 표시
    q = deque()
    q.append((atk[0], atk[1]))

    while q:
        cur = q.popleft()
        dirs = ((0,1),(1,0),(0,-1),(-1,0))     # 우/하/좌/상 우선순위

        for d in range(4):
            nx, ny = (cur[0] + dirs[d][0]+N)%N, (cur[1]+dirs[d][1]+M)%M
            if maze[nx][ny] == 0: continue
            if visited[nx][ny]: continue

            visited[nx][ny] = True
            from_which[nx][ny] = (cur[0], cur[1])
            q.append((nx,ny))
    if not visited[tgt[0]][tgt[1]]:
        return False
    

    from_x, from_y = tgt[0], tgt[1]
    while from_x != atk[0] or from_y != atk[1]:
        atk_power = maze[atk[0]][atk[1]] // 2
        if from_x == tgt[0] and from_y == tgt[1]:
            atk_power = maze[atk[0]][atk[1]]
        do_attack(from_x, from_y, atk_power)
        from_x, from_y = from_which[from_x][from_y]
    return True
    

def bomb():                 # 포탄 공격 시도
    for i in (-1,0,1):
        for j in (-1,0,1):
            nx, ny = (tgt[0] + i + N)%N, (tgt[1]+j+M)%M     # 추가적으로 주위 8개 방향에 있는 포탑에 대해
            if nx == atk[0] and ny == atk[1]: continue      # 공격자는 해당 공격에 영향을 받지 않음
            atk_power = maze[atk[0]][atk[1]] // 2           # 공격자 공격력의 절반만큼의 피해를 입음
            if nx == tgt[0] and ny == tgt[1]:           # 공격 대상은
                atk_power = maze[atk[0]][atk[1]]        # 공격자 공격력만큼의 피해
            do_attack(nx,ny,atk_power)                  # 포탑 공격 


def repair():               # 포탄 정리
    for i in range(N):
        for j in range(M):
            if maze[i][j] != 0 and not isRelated[i][j]: # 부서지지 않은 포탑 중 공격과 무관했던 포탑
                maze[i][j] += 1     # 공격력 1씩 증가

# K번의 턴 시뮬레이션 시작
for time in range(1, K+1):
    # Step 1. 종료 조건 확인 == 공격력이 0인 포탑이 1개
    if isFinish(): break
    # Step2. 공격자 선정
    atk = choose_attacker()

    # Step3. 공격 타겟 선정
    tgt = choose_target()

    # Step4. 공격자 핸디캡 적용
    maze[atk[0]][atk[1]] += N+M
    # 공격 시도
    isRelated = [[False for _ in range(M)] for _ in range(N)]   # 이번 턴에 공격에 관련이 되어있는가?
    isRelated[atk[0]][atk[1]] = True        # 공격자 이번 턴에 공격과 관련있다 표시
    atk_time[atk[0]][atk[1]] = time         # 공격자의 공격 시간 표시

    if not try_laser():     # 레이저 공격을 시도하고 
        bomb()              # 만약 그게 안 된다면 포탄 공격 시도
    
    # 포탑 정비
    repair()


result = choose_target()
print(maze[result[0]][result[1]])
