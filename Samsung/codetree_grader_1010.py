'''
2023.10.10
<부족한 점>
- 자료구조 사용법은 이미 전에 공부했지만, 또 까먹어서 복기하는데 시간이 걸리고
  실수가 있으니 계속 코드를 짜는데 딜레이가 됨
- 저번보다 나아진 점: 1) 문제를 이해함 2) 완성은 못해도 함수 로직을 구현함
'''
import heapq
N = 0
Q = int(input()) # 명령의 수
#grader = dict()  # N개의 채점기를 표현할 해쉬맵
grader=[]
'''
    grader:=
    1) 현재 채점 중인지
        1-1) 어떤 task를 채점 중인함
    2) 현재 쉬고 있는 중인지
    이것들을 표시해야 함--> hash map으로? 왜냐면 하나의 채점기는 하나의 task만 채점할 수 있기 때문
    
'''
# 큐는 세 개가 있어야 함: {대기큐, 현재 채점중인 큐, 채점이 끝난 큐}
ready_q = []        # 채점 대기 큐: 우선순위/큐에 들어온 시간/url 같이 넣기
ing_q = []          # 채점 중인 큐: 채점 시작 시간, url, 채점기 같이 넣기
fin_q = []          # 채점이 끝난 큐: 채점 시작 시간, 채점 끝난 시간, url, 채점기 같이 넣기

def prepare(n, url):      # 채점기 준비, N:= 채점기 개수, url: 초기 문제 url
    global grader
    grader = [0 for _ in range(N+1)]  # 0이면 쉬고있음, 1이면 현재 채점 중
    # 초기 url에 해당하는 task를 대기 큐에 집어넣기
    heapq.heappush(ready_q, (1, 0, url))     # 대기큐: 우선순위/큐에 들어온 시간/url 같이 넣기

def request(t, p, url):      # 채점 요청, t:= t초, p:= 우선순위 p, url:= 문제 도메인/번호
    # 대기큐에 넣어야 하는데, 만약 대기큐에 있는 task중 u와 일치하는 url이 있다면 pass
    # 대기큐에 있는 모든 task들의 url 확인
    for task in ready_q:
        if task[2] == url: continue
    heapq.heappush(ready_q, (p, t, url))
    
def try_score(time):    # 채점 시도
    cur_grader=0
    # Step 1. 채점할 채점기 고르기
    for i in range(N):
        # 쉬고 있지 않은 N개의 채점기 중에서 번호가 가장 작은 것
        if not grader[i]: 
            cur_grader = grader[i]
            break   

    # Step 2. 채점할 task 고르기
    # 제일 먼저 우선순위가 가장 높은 task 고르기 
    best_priority_t = heapq.heappop(ready_q)

    # 만약 현재 채점이 진행중이 도메인 중 하나이면: continue
    for task in ing_q: 
        if task[1] == best_priority_t[2]:
            heapq.heappush(ready_q, best_priority_t)
            continue
    # 현재 시각 t가 < start + 3*gap: continue
    if fin_q:
        last_task = fin_q.pop()
        fin_q.append(last_task)
        last_start_t = int(last_task[0])
        last_end_t = int(last_task[1])
        print(last_task)
        if (last_start_t+3*(last_end_t-last_start_t)) > time: 
            heapq.heappush(ready_q,best_priority_t)
            return

    # 현재 채점 진행 중인 큐에다가 집어넣기
    heapq.heappush(fin_q,(time, best_priority_t[2], i))
    grader[i] = 1
    

def finish_score(t, j): # 채점 종료
    # t초에 Jid번 채점기 종료
    for idx, task in enumerate(ing_q):
        if task[2] == j: # 만약 종료시킬 채점기가 현재 채점중이라면
            # 종료하고, 채점 진행중인 task는 fin_q에다가 넣기
            # 그 task를 어떻게 빼지?
            # 현재 ing_q에는 (채점 중인 큐: 채점 시작 시간, url, 채점기)가 들어있
            ing_q.pop(idx)
            ###############################################################3
            fin_q.append(task[0], t, task[1], j) # 채점 시작시간, 채점 종료시간, url, 채점기
            grader[j] = 0 # 채점기에서 채점 종료하기

def print_queue(time):  # 채점 대기 큐 출력
    # time 시간에 채점 대기큐에 있는 task수 출력
    print(len(ready_q))



for i in range(Q):
    req = list(input().split())
    if req[0] == '100':         # 채점기 준비
        N = int(req[1])
        prepare(int(req[1]), req[2])    # 채점기 수와 초기 url 저장
    elif req[0] == '200':       # 채점 요청
        request(int(req[1]), int(req[2]), req[3])   # t초, 우선순위, url 저장
    elif req[0] == '300':       # 채점 시도
        try_score(int(req[1]))
    elif req[0] == '400':       # 채점 종료
        finish_score(int(req[1]), int(req[2])) # t초에 Jid번 채점기 종료
    else:                       # 채점대기큐 조회 후 출력
        print_queue(int(req[1]))