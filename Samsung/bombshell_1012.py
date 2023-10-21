'''
date: 2023.10.12
# 오답노트
- 실수를 너무너무 많이 한다. 진짜 모든 조건을 빼먹지 않고 하나하나 잘 구현해야한다. 
  정성스럽게 키보드를 쳐야한다.
- 그리고 이제까지 했던 실수를 반복하지 않게, 계속 반복되는 실수를 하지 않도록 생각하면서 코드 짜기
- 문제에서 틀린 부분이 내가 생각하지 못했던 부분이라면 그 부분을 복습하도록!!!!
'''
# 실수 1: 최근 공격 시간을 저장할때 그냥 +1이라고만 해서 0에서 1, 1에서 2로 증가했지, 
#         만약 0에서 3초에 공격했다라는 정보를 저장하지 않았음!!!!! 시뮬레이션에서 time을 넣어주어야 함!!

# 실수 2: 공격자 선정하고 바로 핸디캡 적용해서, 최댓값으로 되어버려 공격 대상에서도 선정이 되어버림!!!
#         공격자의 공격력 증가를 타겟 찾기 이후에 선정해야함!!! (두번째 반복한 실수)

# 실수 3: 종료 조건을 넣지 않아서 포탑이 하나 남았는데도 계속 더해져서 답을 틀리게 출력함

# 실수 4: 행과 열의 합이 가장 큰 포탑-> 열이 큰 포탑 순으로 찾는 것에서 개수를 정할 때
#         min(sum, sum-N~~)이런식으로 해서 틀림: i범위만 체크하면 끝남!!!

# 실수 5: attacker 스펠링을 attakcer 이렇게 씀. 자동완성 안되니까 제대로 보고 쓰기

# 실수 6: nx, ny = (cur[0] + dirs[i][0] + N)%N, (cur[1] + dirs[i][1] + M)%M
#         격자를 삐져나왔을 때 반대로 가는 것을 +N, %N으로 안하고 다 +4, %4로 함..

# 실수 7: if nx == attacker[0] and ny == attacker[1]: continue 여기서 bomb에 공격자 좌표가 포함되었을 때 제외 안시킴
# 실수 8: choose_target을 choose_attacker 복사하고 고치다보니 안고친 변수들, 범위가 있음
# 실수 9: in (-1,0,1)인데 in range(-1,0,1)라고 함 또 반복함!!!
##### 문제에서 나와있는 조건을 빠짐없이 보아야 한다!!!

from collections import deque
INF = 50001
N, M, K = map(int, input().split())                         # 격자의 행, 열, K번 턴
a = [list(map(int, input().split())) for _ in range(N)]     # 격자 정보, 공격력을 가짐
attack_time = [[0 for _ in range(M)] for _ in range(N)]     # 최근 공격 시간 배열
is_related = [[False for _ in range(M)] for _ in range(N)]  # 이번 턴에 공격에 가담했는가?

attacker = (0,0)  # 공격자 좌표
target = (0,0)    # 공격대상 좌표

def choose_attacker():    # 1. 공격자 선정
  global attacker
  # 가장 약한 포탑 선정
  minI, minJ, minPower = 0,0,INF
  
  for sum in range(N+M-2, -1, -1):    # 행과 열의 합이 가장 큰 순
    for j in range(M-1, -1, -1):      # 열 값이 가장 큰 순으로 탐색
      i = sum - j
      if i < 0 or i >= N: continue    # 범위 넘어가면 무시
      if a[i][j] == 0: continue       # 부서진 포탑은 지나가기
      # 현재 최소 공격력보다 더 작거나, 공격력은 같은데 공격 시간은 더 나중인 경우
      if (minPower > a[i][j]) or (minPower == a[i][j] and attack_time[minI][minJ] < attack_time[i][j]):
        minI, minJ, minPower = i, j, a[i][j]
  
  attacker = minI, minJ               # 공격자 좌표 담기
#a[minI][minJ] += N+M 이렇게 하면 안된다!!!

def choose_target():      # 2. 공격 대상 선정
  global target
  # 가장 강한 포탑 선정
  maxI, maxJ, maxPower = 11,11, -1
  
  for sum in range(N+M-1):    # 행과 열의 합이 가장 큰 순
    for j in range(M):      # 열 값이 가장 큰 순으로 탐색
      i = sum - j
      if i < 0 or i >= N: continue    # 범위 넘어가면 무시
      if a[i][j] == 0: continue       # 부서진 포탑은 지나가기
      # 현재 최대 공격력보다 더 크거나, 공격력은 같은데 공격 시간은 더 이전인 경우
      if (maxPower < a[i][j]) or (maxPower == a[i][j] and attack_time[maxI][maxJ] > attack_time[i][j]):
        maxI, maxJ, maxPower = i, j, a[i][j]
  
  target = maxI, maxJ               # 공격 대상 좌표 담기

def attack(target_x, target_y, power):# laser, bomb에서 공격을 실제로 시행하는 함수
  a[target_x][target_y] = max(a[target_x][target_y]-power, 0)
  
def try_laser():          # 3. 레이저 공격 실시
  global attacker, target
  
  # 공격자부터 공격 대상까지 최단 거리가 있는지 확인
  dirs = ((0,1),(1,0),(0,-1),(-1,0))      # 우/하/좌/상 우선순위
  visited = [[False for _ in range(M)] for _ in range(N)]   # 방문 체크 배열 초기화
  from_which = [[None for _ in range(M)] for _ in range(N)] # 어디에서 왔는지 체크, 우선순위에 따른 최단 경로를 보기 위해!
  
  q = deque()
  q.append((attacker[0], attacker[1]))
  visited[attacker[0]][attacker[1]]                         # 공격자 방문 표시
 
  while q:      # 큐가 빌 때까지
    cur = q.popleft()
    for i in range(4):
      nx, ny = (cur[0] + dirs[i][0] + N)%N, (cur[1] + dirs[i][1] + M)%M
      if a[nx][ny] == 0: continue           # 이미 부서진 곳이라면 무시
      if visited[nx][ny]: continue          # 이미 방문했따면 무시
      
      visited[nx][ny] = True                # 방문 처리
      from_which[nx][ny] = (cur[0],cur[1])  # 어디에서 왔는지 표시: (nx,ny)는 (cur[0],cur[1])에서 왔다
      q.append((nx,ny))                     # 큐에다가 좌표 넣기
    
  if not visited[target[0]][target[1]]:     # 만약 최단경로가 없으면 레이저 공격이 불가능하다고 False 리턴
    return False
  
  # 만약 최단경로가 있다면 from_which 따라가면서 레이저 공격 실시
  from_x, from_y = target[0], target[1]     # 공격대상 좌표 담기
  
  while from_x != attacker[0] or from_y != attacker[1]:     
    # 좌표가 공격자 좌표랑 같지 않을 때까지
    is_related[from_x][from_y] = True               # 이번 턴에 공격에 가담했다고 표시
    attackP = a[attacker[0]][attacker[1]] // 2      # 경로에 있는 애들은 공격력의 절반만큼 공격
    if from_x == target[0] and from_y == target[1]: # 만약 공격대상이라면
      attackP = a[attacker[0]][attacker[1]]          # 공격자의 공격력
    attack(from_x, from_y, attackP)
    from_x, from_y = from_which[from_x][from_y]
  return True


def bomb():               # 4. 포탄 공격 실시
  global attacker, target
  dirs = ((-1,0),(1,0),(0,-1),(0,1),(-1,-1),(-1,1),(1,1),(1,-1))  # 8방향에 대해서 확인
  # 공격대상 공격
  attack(target[0], target[1], a[attacker[0]][attacker[1]])
  is_related[target[0]][target[1]] = True
  # 공격대상 주위 8개 방향에 대해 공격
  for i in range(8):
    nx, ny = (dirs[i][0]+target[0]+N)%N, (dirs[i][1]+target[1]+M)%M
    if a[nx][ny] == 0: continue                           # 만약 부서진 곳이라면 무시
    if nx == attacker[0] and ny == attacker[1]: continue  # 만약 공격대상이 있으면 무시
    attackP = a[attacker[0]][attacker[1]] // 2            # 주위에 있는 애들은 공격력의 절반만큼 공격
    attack(nx, ny, attackP)                               # 공격 시행
    is_related[nx][ny] = True                             # 이번 턴에 공격에 가담했다고 표시
  

def repair():             # 5. 포탄 정비
  for i in range(N):
    for j in range(M):
      if a[i][j] == 0: continue
      if is_related[i][j]: continue
      a[i][j] += 1

# 시뮬레이션 시작, K번 반복
for time in range(1, K+1):  
  
  # 1. 공격자 선정
  choose_attacker()
  
  # 2. 공격 대상 선정
  choose_target()
  
  # 3-0. 공격자의 공격력 증가
  # 공격 대상을 선정하고나서 증가시켜야 공격 대상에 공격자가 선택되지 않음!!!!
  a[attacker[0]][attacker[1]] += N+M            # 핸디캡으로 공격력 증가
  is_related = [[False for _ in range(M)] for _ in range(N)]    # 이번 턴에 공격에 가담했는지 배열 초기화
  is_related[attacker[0]][attacker[1]] = True   # 공격자 이번 턴에 공격에 가담했다 표시
  attack_time[attacker[0]][attacker[1]] = time  # 공격 시간 업데이트(+1이 아니라 time을 대입!!)
  
  # 3. 공격 실시
  if not try_laser():                           # 만약 레이저 공격이 안된다면
    bomb()
  # 4. 포탑 정비
  repair()
  
  # 5. 종료 조건 확인
  cnt = 0
  for i in range(N):
    for j in range(M):
      if a[i][j] > 0: cnt += 1
  if cnt == 1: break
  
choose_target()   # 최대 공격력을 가지는 좌표
print(a[target[0]][target[1])