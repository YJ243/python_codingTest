'''
2023.10.13
- maxheap에서 해당 pid에 해당하는 튜플을 빼서 그 튜플 4번째에 있는 얘에 해당하는 점수를 해쉬맵에서 찾아서 더해주어야 하는데 
그거를 못함, 그냥 빼서 --> 이후에 문제에서 주어진 제한사항(개수)보고 map으로 바꿈
- 2시간 30분안에 전체 로직을 다 짜기는 했지만 답은 틀림
- 이후에 TC1에 대해 정답이 나오도록 했지만, 이동할때 한칸씩 계산해서 시간초과 뜸
- 한 칸씩 안가도록 해도 시간초과가 떴음
'''
import heapq
from collections import defaultdict
Q = int(input())                # 명령어 수
N, M, P = 0,0,0                      # N: 행, M: 열, P: 토끼 마리 수

# 토끼를 관리할 자료구조
min_rabbit = []  # value는 minHeap: 우선순위가 낮은 순으로 (1. 총 점프 횟수 2. 행+열 3. 행 4. 열 5. 고유번호)
score = set()                   # maxHeap: 토끼 점수들만 모음
rabbit_info = defaultdict(list) # HashMap: key=PIDi, value = [거리, 점수]
max_rabbit = defaultdict(list)  # HashMap: key=PIDi, value = [1. 행+열 2. 행 3. 열 4. 고유번호]

def init_run(query):     # 경주 시작 준비
    global N, M, P
    N, M, P = query[1], query[2], query[3]                  # N: 행, M: 열, P: 토끼 마리 수
    for i in range(0,P*2,2):                                # 토끼 마리 수만큼 반복
        pid, d = query[4+i], query[5+i]                     # 토끼 고유 번호, 꼭 이동해야할 거리 & 초기에 행, 열 = (0,0), 점수 = 0
        heapq.heappush(min_rabbit, (0, 2, 1, 1, pid))       # (1. 총 점프 횟수 2. 행+열 3. 행 4. 열 5. 고유번호)
        max_rabbit[pid] = [2,1,1,pid]
        score.add(0)                                        # 단순히 점수들 모음집, 처음이니 0        
        rabbit_info[pid] = [d, 0]                           # key:pid, value:[거리, 점수]

def go_up(X,Y,x_dist):  # (X,Y)에 있는 토끼를 y_dist만큼 위로 이동해야 함
    c_x, c_y, distance = X,Y,x_dist
    if N - 1 >= x_dist:
        distance = 0 # 다 이동함
        c_x -= x_dist
    else:
        distance -= N-1
        c_x = 1
    return c_x, c_y, distance

def go_down(X,Y,x_dist):
    c_x, c_y, distance = X,Y,x_dist
    if N - c_x >= x_dist:
        distance = 0 # 다 이동함
        c_x += x_dist
    else:
        distance -= N-c_x
        c_x = N
    return c_x, c_y, distance

def go_right(X,Y,y_dist):
    c_x, c_y, distance = X,Y,y_dist
    if M - c_y >= y_dist:
        distance = 0 # 다 이동함
        c_y += y_dist
    else:
        distance -= M-c_y
        c_y = M
    return c_x, c_y, distance

def go_left(X,Y,y_dist):
    c_x, c_y, distance = X,Y,y_dist
    if M - 1 >= y_dist:
        distance = 0 # 다 이동함
        c_y -= y_dist
    else:
        distance -= M-1
        c_y = 1
    return c_x, c_y, distance

def compare_high(X,Y,maxXY,maxX,maxY):
    # Step3. 가장 우선순위가 높은 칸을 골라 그 위치로 해당 토끼 이동시킴
    ret_xy, ret_x, ret_y = maxXY,maxX,maxY
    if ret_xy < X+Y:   # 행 번호 + 열 번호가 큰 칸
        ret_xy, ret_x, ret_y = X+Y, X, Y
    elif ret_xy == X+Y and ret_x < X: # 행 번호가 큰 칸
        ret_xy, ret_x, ret_y = X+Y, X, Y
    elif ret_xy == X+Y and ret_x == X and ret_y < Y: # 열 번호가 큰 칸
        ret_xy, ret_x, ret_y = X+Y, X, Y
    return ret_xy, ret_x, ret_y

def get_goal(curXY, curX, curY, curDistance):
    maxXY, maxX, maxY = 0,0,0       # 네 방향중 가장 큰 행+열번호, 행번호, 열번호
    x_dist = curDistance % ((N-1)*2)
    y_dist = curDistance % ((M-1)*2)
    #print("가야할 양을 (N-1)*2로 나눈 나머지: ", curDistance, "%", (N-1)*2, curDistance%((N-1)*2))
    #print("가야할 양을 (M-1)*2로 나눈 나머지: ", curDistance, "%", (M-1)*2, curDistance%((M-1)*2))
    #print("가야할 양", x_dist, y_dist, curDistance)
    # 위로 이동
    XY, X, Y, Dis = curXY, curX, curY, curDistance
    X,Y,Dis = go_up(X,Y,x_dist)
    X,Y,Dis = go_down(X,Y,Dis)
    X,Y,Dis = go_up(X,Y,Dis)
    maxXY,maxX, maxY = compare_high(X,Y,maxXY,maxX,maxY)
    #print("up으로: ", X, Y)
    # 아래로 이동
    XY, X, Y, Dis = curXY, curX, curY, curDistance
    X,Y,Dis = go_down(X,Y,x_dist)
    X,Y,Dis = go_up(X,Y,Dis)
    X,Y,Dis = go_down(X,Y,Dis)
    maxXY,maxX, maxY = compare_high(X,Y,maxXY,maxX,maxY)
    #print("down으로: ", X, Y)
    # 오른쪽으로 이동

    XY, X, Y, Dis = curXY, curX, curY, curDistance
    X,Y,Dis = go_right(X,Y,y_dist)
    X,Y,Dis = go_left(X,Y,Dis)
    X,Y,Dis = go_right(X,Y,Dis)
    maxXY,maxX, maxY = compare_high(X,Y,maxXY,maxX,maxY)
    #print("right으로: ", X, Y)
    # 왼쪽으로 이동
    XY, X, Y, Dis = curXY, curX, curY, curDistance
    X,Y,Dis = go_left(X,Y,y_dist)
    X,Y,Dis = go_right(X,Y,Dis)
    X,Y,Dis = go_left(X,Y,Dis)
    maxXY,maxX, maxY = compare_high(X,Y,maxXY,maxX,maxY)
    #print("left으로: ", X, Y)
    return maxX, maxY

def do_run(query):        # 경주 진행
    K, S = query[1], query[2]    # K번 반복, K번 턴 끝난 후 더해줄 점수 S
    is_related = set()           # 이번 K번의 턴동안 한번이라도 뽑혔던 적이 있는지 확인하는 해쉬셋
    for _ in range(1,K+1):           # 우선순위가 높은 토끼를 뽑아 멀리 보내주는 것 K번 반복
        # Step1. 가장 우선순위가 높은 토끼를 선정, 이번에 점프할 토끼 선정
        curJump, curXY, curX, curY, curP = heapq.heappop(min_rabbit)    # 1. 총 점프 횟수 2. 행+열 3. 행 4. 열 5. 고유번호
        curDistance, curScore = rabbit_info[curP]                       # 현재 pid의 이동거리, 점수
        
        # Step2. 상/하/좌/우 네 방향으로 d만큼 이동했을 때 가장 우선순위값
        r, c = get_goal(curXY, curX, curY, curDistance)
        #print(r,c)
        # Step4. 우선순위 큐, 해쉬셋에 다시 토끼 넣어주기
        is_related.add(curP)
        heapq.heappush(min_rabbit, (curJump+1, r+c, r, c, curP))
        max_rabbit[curP] = [r+c,r,c,curP]    # HashMap: key=PIDi, value = [1. 행+열 2. 행 3. 열 4. 고유번호]


        # Step5. curP 토끼 제외 P-1 토끼에게 모두 r+c 점수 더해주기
        for PID in rabbit_info:
            rabbit_info[PID][1] += r+c
            score.add(rabbit_info[PID][1])
        rabbit_info[curP][1] -= r+c

    # Step6. 행+열 큰칸 -> 행번호가 큰칸->열 번호가 큰 칸 골라서 점수 S를 더해주기
    
    # 한 번이라도 뽑혔던 적이 있는 토끼 중에서 고르기
    maxXY, maxX, maxY, max_pid = 0,0,0,0
    for pidT in is_related:
        XY, X, Y, pid_cur = max_rabbit[pidT]
        if maxXY < XY:
            maxXY, maxX, maxY, max_pid = XY, X, Y, pid_cur
        elif maxXY == XY and maxX < X:
            maxXY, maxX, maxY, max_pid = XY, X, Y, pid_cur
        elif maxXY == XY and maxX == X and maxY < maxY:
            maxXY, maxX, maxY, max_pid = XY, X, Y, pid_cur
        elif maxXY == XY and maxX == X and maxY == maxY and max_pid < pid_cur:
            maxXY, maxX, maxY, max_pid = XY, X, Y, pid_cur
    
    rabbit_info[max_pid][1] += query[2]
    score.add(rabbit_info[max_pid][1])


def change_len(query):   # 이동거리 변경
    pid_t, L = query[1], query[2]
    pid_distance = rabbit_info[pid_t][0]
    rabbit_info[pid_t][0] = pid_distance * L

# Q번에 걸쳐 명령 수행
for turn in range(1,Q+1):
    query = list(map(int, input().split()))
    if query[0] == 100:     # 경주 시작 준비, 100 3 5 2 10 2 20 5
        init_run(query)
    elif query[0] == 200:   # 경주 진행, 200 6 100
        score = set()
        do_run(query)
    elif query[0] == 300:   # 이동거리 변경, 300 10 2
        change_len(query)
    else:                   # 최고 토끼 선정, 400
        print(max(score))