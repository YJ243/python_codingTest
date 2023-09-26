import sys
from collections import deque
INF = 10000000
si = sys.stdin.readline

# N, M, K := 행, 열, 턴 수
N, M, K = map(int, si().split())

# a := 지도의 정보
a = [list(map(int, si().split())) for _ in range(N)]

# isAttacked := 이번 턴에 공격과 관련이 있었는가?
isAttacked = [[False for _ in range(M)] for _ in range(N)]

# lastAttack := 마지막에 공격한 턴은 언제인가?
# 모든 포탑은 시점 0에 모두 공격한 경험이 있다고 가정
lastAttack = [[0 for _ in range(M)] for _ in range(N)]

def attack(x, y, power): # (x, y)에 있는 포탑이 power만큼의 공격을 받는다.
    isAttacked[x][y] = True # 공격에 가담했다
    a[x][y] = max(0, a[x][y] - power) # 음수 방지

def isFinish(): # 만약 종료 조건을 만족했다면, true return, O(NM)
    # 부서지지 않은 포탑이 1개가 된다면 그 즉시 중지
    cnt = 0
    for i in range(N):
        for j in range(M):
            if a[i][j] != 0:
                cnt += 1
    return cnt == 1 # 부서지지 않은 포탑(살아남은 포탑)이 1개가 되면 그 즉시 중지

def select_attacker() -> tuple: # 공격자를 선정하는 함수
    minPower, latestTime, minI, minJ = INF, -1, 0, 0 # 가장 약한 공격력, 가장 최근 공격 시간, 공격자 열
    for sum in range(N+M-2, -1, -1): # sum(행+열)을 최대부터 최소까지 순회
        for j in range(M-1, -1, -1): # 같은 sum에 대해서는 높은 열부터 탐색
            i = sum - j # 행은 합에서 열을 빼기
            # 현재 보고 있는 좌표: (i,j)
            if i < 0 or i >= N: continue # 격자를 벗어나는 위치는 무시

            if a[i][j] == 0: 

                continue # 부서진 포탑이면 무시
           
            if minPower > a[i][j]: # 현재 최소 공격력보다 더 작으면
                # 현재 탐색 좌표의 공격력, 마지막 공격시간, 좌표 넣기
                minPower, latestTime, minI, minJ = a[i][j], lastAttack[i][j], i, j

            elif minPower == a[i][j] and latestTime < lastAttack[i][j]:
                # 현재 최소 공격력과 같으면 시간을 비교
                # 가장 최근에 공격한 포탑으로 저장

                minPower, latestTime, minI, minJ = a[i][j], lastAttack[i][j], i, j

    return minI, minJ


def select_target() -> tuple: # 공격 대상을 선정하는 함수 O(NM) <<< O(NM log (NM))
    maxPower, minTime, maxI, maxJ = -1, INF, 0, 0

    for sum in range(N+M-1): # 거꾸로, 열과 행의 합이 가장 작은 포탑부터
        for j in range(M): # 열이 가장 작은 포탑부터
            i = sum - j
            if i < 0 or i >= N: continue


            if maxPower < a[i][j]:

                maxPower, minTime, maxI, maxJ = a[i][j], lastAttack[i][j], i, j

            elif maxPower == a[i][j] and minTime > lastAttack[i][j]:

                maxPower, minTime, maxI, maxJ = a[i][j], lastAttack[i][j], i, j

    return maxI, maxJ


# bfs 함수
def tryRaser(atk, tgt) -> bool: # 레이저 공격 시도, 실패하면 False return, O(NM)
    # visit[x][y] := (x, y)에 대한 방문 여부
    visit = [[False for _ in range(M)] for _ in range(N)]

    # come[x][y] := (x,y)가 어디로부터 왔는가?
    come = [[None for _ in range(M)] for _ in range(N)]

    q = deque()
    visit[atk[0]][atk[1]] = True
    q.append(atk)

    # 우/하/좌/상 우선순위
    dirs = ((0,1),(1,0),(0,-1),(-1,0))
    while q:
        x, y = q.popleft()
        for dx, dy in dirs:
            nx, ny = (x + dx + N) % N, (y + dy + M) % M # 모듈러 연산으로 삐져나오는 경우 처리

            if a[nx][ny] == 0: continue
            if visit[nx][ny]: continue

            come[nx][ny] = (x,y) # 어디로부터 왔는지 기록하기 (이 한 줄만 추가하면 역추적 가능)
            visit[nx][ny] = True
            q.append((nx,ny))
    
    if not visit[tgt[0]][tgt[1]]: # 만약 레이저가 도달하지 못했다면, False return
        return False

    # 역추적 하면서 공격
    x, y = tgt[0], tgt[1] # x, y = tgt
    while x != atk[0] or y != atk[1]:
        # power 공격력 정하기
        power = a[atk[0]][atk[1]] // 2
        if x == tgt[0] and y == tgt[1]:
            power = a[atk[0]][atk[1]]
        # 공격하기
        attack(x,y,power)
        # 역추적하기
        x, y = come[x][y]
    return True
        




# 포탄 공격 함수
def bomb(atk, tgt):
    '''
    # 타겟에 대한 공격 파워
    power = a[atk[0]][atk[1]]
    attack(tgt[0], tgt[1], power)

    dx = [-1,1,0,0,-1,-1,1,1]
    dy = [0,0,-1,1,-1,1,-1,1]
    power = a[atk[0]][atk[1]] // 2
    for i in range(8):
        nx = (tgt[0]+dx[i]+N) % N
        ny = (tgt[1]+dy[i]+N) % N
        if a[nx][ny] == 0: continue
        if nx == atk[0] and ny == atk[1]: continue
        attack(nx,ny,power)
    '''
    for dx in (-1,0,1):
        for dy in (-1,0,1):
            nx, ny = (tgt[0]+dx + N)%N, (tgt[1]+dy+M)%M
            if nx == atk[0] and ny == atk[1]: continue # 공격자면 패스
            power = a[atk[0]][atk[1]] // 2 # 공격력 정하기
            if nx == tgt[0] and ny == tgt[1]: power = a[atk[0]][atk[1]]
            # 공격하기
            attack(nx,ny,power)


# 시뮬레이션 -> 시키는 것 하기! (삼성은 순서를 알려줬기 때문에 그대로 하면 된다)

for time in range(1, K+1):
    if isFinish(): # 만약 종료 조건을 만족했다면, 턴을 수행하지 않고 종료
        break
    
    # 1. 공격자 선정
    atk = select_attacker()

    # 2. 공격 대상 선정
    tgt = select_target()

    # 3. 공격자에게 핸디캡 적용
    a[atk[0]][atk[1]] += N+M

    # 4. 공격자에 대해 "마지막 공격 턴" 정보 갱신
    lastAttack[atk[0]][atk[1]] = time

    # 5. 공격 수행
    # 매 턴마다 공격을 받았는지에 대한 배열 초기화
    isAttacked = [[False for _ in range(M)] for _ in range(N)]
    isAttacked[atk[0]][atk[1]] = True # 공격자 공격에 가담했다 표시

    if not tryRaser(atk, tgt): # 레이저 공격을 시도하기
        bomb(atk, tgt) # 공격에 실패했다면 포탄 공격
    # 6. 정비 수행
    for i in range(N):
        for j in range(M):
            if not isAttacked[i][j] and a[i][j] != 0: # 공격에 가담하지 않은 포탑이라면
                a[i][j] += 1



'''
max_power = 0
for i in range(N):
    for j in range(M):
        if a[i][j] > max_power:
            max_power = a[i][j]
print(max_power)
'''

# 이미 가장 강한 포탑을 뽑는 함수를 정의했으니, 위의 주석처럼 다시 안구해도 됨
res = select_target()
print(a[res[0]][res[1]])
print(a)