'''
date: 2023.09.26
# 오답노트
'''

# 1. N, M 위치를 바꿔씀(자주 하는 실수, 코드 짤 때 집중해서 짜기)
# 2. 우,하,좌,상 위치에서 상을 (-1,1)이라고 함
# 3. in (-1,0,1)인데 in range(-1,0,1)라고 함
# 4. a(list)와 q(큐)를 바꿔씀
# 5. 파이썬 tuple 좌표 지정 헷갈림
# 6. 공격자의 공격력 증가를 타겟 찾기 보다 이전에 수행함

from collections import deque
N, M, K = map(int, input().split()) # N: 행, M: 열, K: 턴 수

INF = 10000000
a = [list(map(int, input().split())) for _ in range(N)] # 격자 정보
attack_time = [[0 for _ in range(M)] for _ in range(N)] # 마지막 공격 시간, 모든 포탑은 시점 0에 모두 공격한 경험이 있음
attack_related = [[False for _ in range(M)] for _ in range(N)] # 이번 턴에 공격에 무관한가?

atk = (0,0) # 공격자 좌표
tgt = (0,0) # 타겟 좌표

# 공격 수행
def do_attack(x,y,power): # (x,y)에 있는 포탑이 power만큼의 공격을 받음
    # 공격력만큼 감소
    return max(a[x][y]-power, 0) # 음수 방지

# 공격자 선정
def choose_attacker():
    minPower, maxTime, minI, minJ = INF, 0, 0, 0 # 가장 낮은 공격력, 가장 최근 공격 시간, 공격자 좌표 (minI, minJ)
    # 행과 열이 가장 큰 포탑 그 중에서도 열 값이 가장 큰 것부터 탐색
    for sum in range(N+M-2, -1, -1):
        for j in range(M-1, -1, -1):
            i = sum - j # 행은 합에서 열을 빼기

            if i < 0 or i >= N: continue # 범위 벗어나는 행은 패스
            if a[i][j] == 0: continue # 부서진 포탑은 패스
            if minPower > a[i][j]: # 공격력이 현재 가장 낮다면
                minPower, maxTime, minI, minJ = a[i][j], attack_time[i][j], i, j
            
            elif minPower == a[i][j] and maxTime < attack_time[i][j]: 
                # 현재 가장 낮은 공격력과 같으면서 더 최근에 공격했다면
                minPower, maxTime, minI, minJ = a[i][j], attack_time[i][j], i, j
    return minI, minJ

# 공격 타겟 선정
def choose_target():
    maxPower, minTime, maxI, maxJ = 0, INF, 0, 0 # 가장 높은 공격력, 가장 예전 공격 시간, 공격 타겟 좌표 (maxI, maxJ)
    # 행과 열이 가장 작은 포탑 그 중에서도 열 값이 가장 작은 것부터 탐색
    for sum in range(N+M-1):
        for j in range(M):
            i = sum - j
            if i < 0 or i >= N: continue # 범위 벗어나는 행은 패스
            if a[i][j] == 0: continue # 부서진 포탑은 패스
            if maxPower < a[i][j]: # 현재 가장 큰 공격력보다 크다면
                maxPower, minTime, maxI, maxJ = a[i][j], attack_time[i][j], i, j
            elif maxPower == a[i][j] and minTime > attack_time[i][j]:
                # 현재 가장 높은 공격력과 같으면서 더 예전에 공격했다면
                maxPower, minTime, maxI, maxJ = a[i][j], attack_time[i][j], i, j
    return maxI, maxJ

# 레이저 공격 시도
def try_laser(atk, tgt):
    global attack_related
    visited = [[False for _ in range(M)] for _ in range(N)] # 방문 정보 담는 배열
    coordinate_from = [[None for _ in range(M)] for _ in range(N)] # 어느 좌표에서 왔는가? 최단 경로 우선 순위를 찾기 위한 배열
    
    # 우,하,좌,상 우선순위
    dx = [0,1,0,-1]
    dy = [1,0,-1,0]
    
    visited[atk[0]][atk[1]] = True # 공격자 좌표 방문 표시
    q=deque() # 큐 생성
    q.append((atk)) # 공격자 좌표 큐에 넣기
    
    while q:
        x, y = q.popleft()
        
        for i in range(4):
            # 가장자리에서 막힌 방향 이동했을 때 처리
            nx = (x + dx[i] + N) % N
            ny = (y + dy[i] + M) % M
            
            if visited[nx][ny]: continue # 방문한 위치 패스
            if a[nx][ny] == 0: continue # 부서진 포탑 패스
            
            visited[nx][ny] = True # 방문 표시
            coordinate_from[nx][ny] = (x,y) # 역추적을 위한 이전 좌표 저장
            
            q.append((nx,ny))
    
    # 탐색이 끝난 후 공격 대상 포탑까지 최단 경로가 존재하지 않으면
    if not visited[tgt[0]][tgt[1]]: return False # false 반환하고 포탄 공격

    from_cor = tgt # 타겟 좌표 담기
    # 이후 경로를 따라 올라가면서 공격 진행
    while from_cor[0] != atk[0] or from_cor[1] != atk[1]: # 공격자 좌표가 아닐 때까지
        attack_related[from_cor[0]][from_cor[1]] = True # 공격에 관련 있다 표시, 이후 포탑 정비를 위함
        power = a[atk[0]][atk[1]] // 2 # 공격자 공격력의 절반
        if from_cor[0] == tgt[0] and from_cor[1] == tgt[1]: # 만약 현재 좌표가 공격 타겟이라면
            power = a[atk[0]][atk[1]] # 공격자의 공격력 담기
            
        a[from_cor[0]][from_cor[1]] = do_attack(from_cor[0], from_cor[1], power)
        from_cor = coordinate_from[from_cor[0]][from_cor[1]] # 다음 좌표 담기
    return True

# 포탄 공격
def do_bomb(atk, tgt):
    # 공격 대상과 주위 8개 방향에 있는 포탑 공격
    for i in (-1,0,1):
        for j in (-1,0,1):
            
            power = a[atk[0]][atk[1]] // 2
            x, y = (tgt[0]+i+N)%N, (tgt[1]+j+M)%M
            
            if a[x][y] == 0: continue # 부서진 포탑은 패스
            if x == atk[0] and y == atk[1]: continue # 공격자면 패스
            attack_related[x][y] = True # 나머지면 공격에 관련있따 표시
            
            # 만약 공격 대상에 위치하면
            if x == tgt[0] and y == tgt[1]:
                power = a[atk[0]][atk[1]] # 공격력은 공격자 파워
            a[x][y] = do_attack(x,y,power) # 공격 수행

# 프로그램 시작
for time in range(1, K+1): # 시점 1부터 시점 K까지
    # 종료 조건
    cnt = 0
    for i in range(N):
        for j in range(M):
            if a[i][j] > 0:
                cnt += 1
    if cnt == 1: break # 부서지지 않는 포탑이 1개가 되면 그 즉시 중지
    
    attack_related = [[False for _ in range(M)] for _ in range(N)] # 매 턴마다 공격 관련 여부 초기화
    atk = choose_attacker() # 공격자 선정
    tgt = choose_target() # 공격 타겟 선정

    a[atk[0]][atk[1]] += N+M # 공격력 증가
    attack_time[atk[0]][atk[1]] = time # 현재 시점을 공격자의 공격 시점으로 저장
    attack_related[atk[0]][atk[1]] = True # 공격자 공격에 관련있다 표시
    
    if not try_laser(atk, tgt): # 레이저 공격을 먼저 시도하고, 그게 안된다면
        do_bomb(atk, tgt) # 포탄 공격 시도
        
    
    # 포탑 정비
    for i in range(N):
        for j in range(M):
            if not attack_related[i][j] and a[i][j] != 0:
                # 만약 이번 턴에 공격에 연관되지 않았고, 부서지지 않은 포탑이라면
                a[i][j] += 1

result = choose_target() # 남아 있는 포탑 중 가장 강한 포탑
print(a[result[0]][result[1]]) # 그 포탑의 공격력 출력
