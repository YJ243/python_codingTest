'''
2023.10.14
'''
# 실수 1: if not readyQ[domain]: continue 이 조건을 안써서, 큐에 들어온 domain에 대한 task가 다 나가서 비어있을 때 오류가 뜸
import heapq
from collections import defaultdict

Q = 0   # Q: 명령어 수

'''채점기를 나타내는 자료구조'''
N = 0                       # 채점기 수
restQ = []                  # PQ: 쉬고 있는 채점기를 담는 우선순위 큐, 번호가 가장 작은 것 = 우선순위가 가장 높음
doingQ = defaultdict(list)  # HashMap: 현재 채점을 진행 중인 채점기, key: 채점기 번호, value:(url/ 채점시작시간)이후 종료 채점기를 찾을 때 빠르게 search

'''채점 task를 나타내는 자료구조'''
readyQ = defaultdict(list)                 # HashMap, key: domain/ value: PQ(우선순위 p, 채점 대기큐에 들어온 시간, 문제 ID), 채점 요청이 들어온 task를 담는 자료구조
setQ = set()                # Hashset: url이 현재 readyQ에 있는지 바로 알려주는 자료구조
timeLock = defaultdict(int) # HashMap: 현재 도메인의 timelock, key: 도메인, value: 그 시간까지 채점 불가능
task_cnt = 0
def init(_N, u0):     # 코드트리 채점기 준비
    ''' 채점기 초기화'''
    global N, restQ, task_cnt
    N = _N      # 채점기 수는 _N
    for i in range(1, N+1):                 # 쉬고 있는 채점기에 1~N까지의 수를 저장
        heapq.heappush(restQ, i)

    '''채점 task 초기화'''
    setQ.add(u0)                            # 현재 대기큐에 들어온 url 추가
    domain = u0.split('/', 1)[0]            # 초기 url의 도메인
    u0_id = u0.split('/', 1)[1]            # 초기 url의 문제ID
    heapq.heappush(readyQ[domain], (0,1, u0_id)) # 해당 도메인 문제를 큐에 넣음, value = 우선순위, 큐에 들어온 시간
    task_cnt += 1

def pushQ(t,p,u):    # 채점 요청
    global task_cnt
    if u in setQ: return
    setQ.add(u)
    domain = u.split('/',1)[0]
    u_id = u.split('/', 1)[1]  
    heapq.heappush(readyQ[domain], (p,t, u_id))   # url=u의 도메인을 잘라서 우선순위와 큐에 들어온 시간을 넣기
    task_cnt += 1
def try_grade(t):    # 채점 시도
    global task_cnt
    if not restQ: return    # 만약 쉬고 있는 채점기가 없다면 바로 리턴

    # Step1. 대기큐에서 가장 우선순위가 높은 얘를 뽑기
    min_p, min_t, min_domain = 50001, 1000001, ""

    for domain in readyQ:
        if not readyQ[domain]: continue
        cur_priority, cur_time, _ = readyQ[domain][0]
        if timeLock[domain]> t:                     # 현재 도메인의 타임락보다 현재 시간이 작다면
            continue
        if (min_p > cur_priority) or (min_p == cur_priority and min_t > cur_time):  # 우선순위가 가장 높은 task를 고르기
            min_p, min_t, min_domain = cur_priority, cur_time, domain
    if min_p == 50001 and min_t == 1000001:         # 즉시 채점이 불가능한 경우 리턴
        return
    min_p, min_t, min_id = heapq.heappop(readyQ[min_domain])    # 현재 우선순위가 가장 높은 task의 우선순위와 대기큐에 들어온 시간
    task_cnt -= 1
    setQ.remove(min_domain + "/" + min_id)                      # HashSet에서 현재 url 빼주기
   
   # Step2. 쉬고 있는 채점기 중 가장 번호가 작은 채점기를 고름
    g_id = heapq.heappop(restQ)     # 쉬고 있는 채점기 중 가장 번호가 작은 채점기
    doingQ[g_id] = (min_domain, t)  # 현재 채점중인 채점기의 맵에다가 넣기
    timeLock[min_domain] = 1000001  # 현재 채점중인 도메인이라고 표시

def finish(t, J_id):   # 채점 종료
    if J_id in restQ: return        # J_id번 채점기가 쉬고 있는 중이였다면 바로 리턴

    # t초에 J_id번 채점 종료
    cur_domain, start = doingQ[J_id]    
    gap = t-start
    timeLock[cur_domain] = start + 3*gap
    doingQ.pop(J_id)
    heapq.heappush(restQ, J_id)

Q = int(input())                # 명령어의 수

for time in range(Q):
    query = input().split()                             
    if query[0] == "100":                               # 100 3 codetree.ai/16 : 3개 채점기, 초기문제 u0=co~
        init(int(query[1]), query[2])                   # 코드트리 채점기 준비
    elif query[0] == "200":                             # 200 5 1 codetree.ai/17 : 5초, p우선순위, code~url
        pushQ(int(query[1]), int(query[2]), query[3])   # 채점 요청
    elif query[0] == "300":                             # 300 8 : 8초에 채점 시도
        try_grade(int(query[1]))                        # 채점 시도
    elif query[0] == "400":                             # 400 4 1 : 4초에 1번 채점기의 채점 종료
        finish(int(query[1]), int(query[2]))            # 채점 종료
    elif query[0] == "500":                             
        print(task_cnt)                               # 채점 대기 큐 조회, 대기큐에 있는 채점 task수 출력