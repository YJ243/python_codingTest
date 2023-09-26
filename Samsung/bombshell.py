'''
date: 2023.09.22
'''

from collections import deque
n, m, k = map(int, input().split())
list_bomb = []
attack_time = [[0 for _ in range(m)] for _ in range(n)]

for i in range(n):
    list_bomb.append(list(map(int, input().split())))

attacker = (0,0)
attacker_candidate=[]
target = (0,0)
target_candidate = []

## 공격자 선정
def choose_attacker():
    global attacker
    global attacker_candidate
    attacker_candidate = []
    ###### 1. 공격력이 가장 낮은 포탑
    lowest_power = 5000
    for i in range(n):
        for j in range(m):
            if list_bomb[i][j] != 0 and list_bomb[i][j] < lowest_power:
                lowest_power = list_bomb[i][j]
                attacker = (i,j)

    # 공격력이 가장 낮은 포탑이 여러개인지 확인
    for i in range(n):
        for j in range(m):
            if lowest_power == list_bomb[i][j]:
                attacker_candidate.append((i,j))

    ###### 2. 가장 최근에 공격한 포탄
    if len(attacker_candidate) > 1:
        # 공격력 같은 후보들의 최근 공격 시간을 확인
        time_tmp = []
        time_candidate = []
        for i in range(len(attacker_candidate)):
            time_tmp.append(attack_time[attacker_candidate[i][0]][attacker_candidate[i][1]])

        for i in range(len(time_tmp)):
            cnt = 0
            idx = 0
            
            if max(time_tmp) == time_tmp[i]: # 만약 가장 큰 공격시간과 같다면 카운트 증가
                cnt += 1
                idx = i
                time_candidate.append((attacker_candidate[i][0], attacker_candidate[i][1]))

        if len(time_candidate) == 1: # 그 카운트가 하나면, 공격시간이 가장 최근인게 하나여서 attacker에 저장

            attacker = attacker_candidate[idx][0], attacker_candidate[idx][1]
        else: # 카운트가 여러개라면 time_candi에서 고르기
    ###### 3. 행과 열의합이 가장 큰 포탄

            tmp1 = []
            tmp2 = []
            for candi in time_candidate:
                tmp1.append(candi[0] + candi[1])
            for i in range(len(tmp1)):
                if max(tmp1) == tmp1[i]:
                    tmp2.append((time_candidate[i][0], time_candidate[i][1]))
            if len(tmp2) == 1:

                attacker = tmp2[0][0], tmp2[0][1]
            else: # 행과 열의 합이 가장 큰 포탄이 여러개라면
    ###### 4. 열 값이 가장 큰 포탄

                max_column = 0
                final_index = 0

                for candi in tmp2:
                    if max_column < candi[1]:
                        max_column = candi[1]
                        attacker = candi[0], candi[1]
    list_bomb[attacker[0]][attacker[1]] += (n+m) # 공격력 증가

## 공격 타겟 선정
def choose_target():
    global target
    global target_candidate
    target_candidate = []
    ###### 1. 공격력이 가장 높은 포탑
    highest_power = 0
    for i in range(n):
        for j in range(m):
            # 가장 높은 공격력보다 해당 공격력이 크면
            if list_bomb[i][j] != 0 and list_bomb[i][j] > highest_power:
                highest_power = list_bomb[i][j]
                target = (i,j) # 타겟 저장

    # 공격력이 가장 높은 포탑이 여러개인지 확인
    for i in range(n):
        for j in range(m):
            if highest_power == list_bomb[i][j]:
                target_candidate.append((i,j))

    ###### 2. 가장 예전에 공격한 포탄
    if len(target_candidate) > 1:
        # 공격력 같은 후보들의 최근 공격 시간을 확인
        time_tmp = []
        time_candidate = []
        for i in range(len(target_candidate)):
            # 공격력이 가장 높은 포탑들의 최근 공격 시간을 담기
            time_tmp.append(attack_time[target_candidate[i][0]][target_candidate[i][1]])

        for i in range(len(time_tmp)):
            cnt = 0
            idx = 0
            
            if min(time_tmp) == time_tmp[i]: # 만약 가장 작은 공격시간과 같다면 카운트 증가
                cnt += 1
                idx = i
                time_candidate.append((target_candidate[i][0], target_candidate[i][1]))

        if len(time_candidate) == 1: # 그 카운트가 하나면, 공격시간이 가장 최근인게 하나여서 target에 저장

            target = target_candidate[idx][0], target_candidate[idx][1]
        else: # 카운트가 여러개라면 time_candi에서 고르기
    ###### 3. 행과 열의합이 가장 작은 포탄

            tmp1 = []
            tmp2 = []
            for candi in time_candidate:
                tmp1.append(candi[0] + candi[1])
            for i in range(len(tmp1)):
                if min(tmp1) == tmp1[i]:
                    tmp2.append((time_candidate[i][0], time_candidate[i][1]))
            if len(tmp2) == 1:
                target = tmp2[0][0], tmp2[0][1]
            else: # 행과 열의 합이 가장 큰 포탄이 여러개라면
    ###### 4. 열 값이 가장 작은 포탄

                min_column = 10
                final_index = 0

                for candi in tmp2:
                    if min_column > candi[1]:
                        min_column = candi[1]
                        target = candi[0], candi[1]

# 레이저 공격 시도 (우,하,좌,상 순서로)
dx = [0,1,0,-1]
dy = [1,0,-1,0]
visited = [
        [False for _ in range(m)] 
        for _ in range(n)
]

def laser_dfs(attack_x,attack_y):
    visited[attack_x][attack_y] = True
    
    for i in range(4):
        nx = attack_x + dx[i]
        ny = attack_y + dy[i]

        # 가장자리에서 막힌 방향으로 진행 -> 반대편으로 나오기
        # 맨 오른쪽이었는데, 한번더 오른쪽으로 이동했으면
        if attack_y == m-1 and ny == m:
            ny = 0
        
        # 맨 아래였는데, 한번더 아래로 이동했으면
        elif attack_x == n-1 and nx == n:
            nx = 0
            
        # 맨 왼쪽이었는데, 한번 더 왼쪽으로 이동했으면
        elif attack_y == 0 and ny == -1:
            ny = m-1
        
        # 맨 위쪽이었는데, 한번 더 위쪽으로 이동했으면
        elif attack_x == 0 and nx ==-1:
            nx = n-1

        if list_bomb[nx][ny] == 0:
            continue
        if visited[nx][ny]:
            continue
        
        visited[nx][ny] = True
        if nx == target[0] and nx == target[1]:
            return
        laser_dfs(nx,ny)





def laser_bfs(x,y): # bfs 탐색 함수
    global visited
    visited = [
        [False for _ in range(m)]
        for _ in range(n)
    ]
    queue = deque([(x,y)])
    visited[x][y] = True

    # attacker에서 target까지의 최단 경로가 있는지 탐색
    while queue:
        a, b = queue.popleft()

        for i in range(4):
            nx = a + dx[i]
            ny = b + dy[i]
            
            # 가장자리에서 막힌 방향으로 진행 -> 반대편으로 나오기
            # 맨 오른쪽이었는데, 한번더 오른쪽으로 이동했으면
            if b == m-1 and ny == m:
                ny = 0
            
            # 맨 아래였는데, 한번더 아래로 이동했으면
            elif a == n-1 and nx == n:
                nx = 0
                
            # 맨 왼쪽이었는데, 한번 더 왼쪽으로 이동했으면
            elif b == 0 and ny == -1:
                ny = m-1
            
            # 맨 위쪽이었는데, 한번 더 위쪽으로 이동했으면
            elif a == 0 and nx ==-1:
                nx = n-1

            if list_bomb[nx][ny] == 0:
                continue

            if visited[nx][ny]:
                continue
            
            visited[nx][ny] = True
            
            queue.append((nx,ny))

#def do_laser(attack_x, attack_y)

bomb_dx = [-1,1,0,0,-1,1]
bomb_dy = [0,0,-1,1,-1,1]
# 포탄 공격 시도
def do_bomb_attack(target_x,target_y):
    list_bomb[target_x][target_y] -= list_bomb[attacker[0]][attacker[1]]
    for i in range(8):
        nx = bomb_dx[i]+target_x
        ny = bomb_dy[i]+target_y

        if target_y == m-1 and ny == m:
            ny = 0
        
        # 맨 아래였는데, 한번더 아래로 이동했으면
        elif target_x == n-1 and nx == n:
            nx = 0
            
        # 맨 왼쪽이었는데, 한번 더 왼쪽으로 이동했으면
        elif target_y == 0 and ny == -1:
            ny = m-1
        
        # 맨 위쪽이었는데, 한번 더 위쪽으로 이동했으면
        elif target_x == m-1 and ny ==m:
            nx = n
        
        # 맨 왼쪽 위
        elif nx == -1 and ny == -1:
            # 맨 오른쪽 아래로
            nx = n-1
            ny = m-1 
        
        # 맨 오른쪽 위
        elif nx == -1 and ny ==m:
            # 맨 왼쪽 아래로
            nx = n-1
            ny = 0
        
        # 맨 왼쪽 아래
        elif nx == n and ny == -1:
            # 맨 오른쪽 위로 감
            nx = 0
            ny = m-1
        
        # 맨 오른쪽 아래
        elif nx == n and ny ==m:
            #맨 왼쪽 위로
            nx = 0
            ny = 0
        # 주위 8개 방향에 대해 공격력 절반만큼 깎임
        if list_bomb[nx][ny] == 0:
            continue
        if nx == attacker[0] and ny == attacker[1]:
            continue # 만약 공격자라면 공격을 받지않음
        list_bomb[nx][ny] -= list_bomb[attacker[0]][attacker[1]] // 2

# 포탑 부서짐
def do_break():
    global list_bomb
    for i in range(n):
        for j in range(m):
            if list_bomb[i][j] < 0:
                list_bomb = 0

# 포탑 정비
def do_repair():
    # 공격과 무관했던 포탑은 공격력 1씩 올라가기

    # 만약 부서지지 않은 포탑이 하나뿐이면 return False
    pass



### 프로그램 실행
while k > 0:
    choose_attacker()
    choose_target()

    laser_dfs(attacker[0], attacker[1]) # 여기서는 갈 수 있는 경로 탐색했어
    # 최단경로가 여러개인 경우는 어떻게 구분하지?
   
    # 만약 dfs로 짰다면? 최단거리까지 다시 탐색하면서 공격해야하나? 공격력 나누기
    ## dfs로 짜서 탐색해도 마찬가지였음
    if visited[target[0]][target[1]]: # 만약 
        do_break()
    else:
        do_bomb_attack(target[0],target[1])

    if not do_repair(): # 부서지지 않은 포탑이 하나이면
        break

print(max(map(max, list_bomb))) # 가장 강한 포탑의 공격력 출력
print(visited)