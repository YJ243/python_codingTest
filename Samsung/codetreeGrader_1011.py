'''
2023.10.11
- 시간이 줄어들었는가
 1) 2시간 안에 문제 이해 + 코드짜기까지 완성했지만, 답이 틀림
    (그래서 시간이 줄어들었지만 아직 부족함)
- 실수가 줄어들었는가?
 1) heapq 우선순위 큐 사용은 잘함
 2) 코드를 완성하기까지 중간에 자잘자잘한 실수가 너무 잦음
    (ex, 범위 체크, 처음 init 등)
    
- 막히던 부분이 해결되었는가?
 1) 출력까지는 가게 됨
 2) 채점하는 로직은 잘 짜게 된거 같긴한데...
'''
from collections import defaultdict
import heapq
from typing import List, Dict, Tuple, Set, Optional
INF = 1000000001        # 최댓값

# 채점 task를 나타낼 자료구조
setQ: Set[str] = set()                                              # 현재 채점 대기큐에 있는 url만 모아놓는 자료구조 (큐에 u를 추가할때 있으면 빠르게 패스하기 위해)
readyQ: Dict[str, List[Tuple[int, int, str]]] = defaultdict(list)   # 채점 대기 큐, (key: domain, value(PQ): tuple(p우선순위, t큐에 들어온 시간, id문제 번호)
cntQ: int = 0                                                       # 채점 대기 큐에 있는 task 개수

# 채점기를 나타낼 자료구조
N = 0                   # 채점기의 수
timeLock: Dict[str, int] = defaultdict(int)                   # 각 도메인 별로 언제까지 채점을 할 수 없는지 담아놓는 HashMap
restQ: List[int] = []                          # 현재 쉬고 있는 채점기의 index를 모아놓은 배열 (PQ로 구현하여 가장 번호가 작은 채점기가 빨리 반환되도록)
infoQ: List[Optional[Tuple[str, int]]] = []    # 현재 채점 중인 채점기의 정보를 모아놓은 배열(ex. 2번 채점기는 (url, s) 채점중인 문제, 시작 시간)

Q = int(input())        # 명령의 수

def init(grader_cnt, u0):                 # 초기 채점기 준비, 초기 태스크 큐에 넣기
    global N, cntQ, restQ, infoQ
    N = grader_cnt                  # 채점기 개수
    for i in range(1,N+1):
        restQ.append(i)             # 쉬고 있는 채점기 추가
    domain = u0.split('/',1)[0]     # 도메인만 담기
    p_id = u0.split('/',1)[1]       # 문제 id 담기

    heapq.heappush(readyQ[domain], (1, 0, p_id)) # readyQ의 [domain]에다가 tuple 원소 집어넣기
    setQ.add(u0)
    cntQ += 1
    infoQ = [() for _ in range(N+1)]
def pushQ(time, prior, url):    # 채점대기큐에 task 넣기
    global cntQ
    if url in setQ:         # 만약 채점 요청에 들어온 url과 똑같은 것이 이미 대기큐에 있다면
        return              # 큐에 추가하지 않고 넘어가기
    domain = url.split('/',1)[0]     # 도메인만 담기
    p_id = url.split('/',1)[1]       # 문제 id 담기
    heapq.heappush(readyQ[domain], (prior, time, p_id)) # readyQ의 [url]에다가 tuple 원소 집어넣기
    setQ.add(url)
    timeLock[domain] = 0
    cntQ += 1

def popQ(time):                 # time초에 채점 시도
    global cntQ
    # Step 0. 쉬고있는 채점기가 있는지 보기
    if not restQ: return        # 쉬고 있는 채점기가 하나도 없으면 바로 리턴
    bestPrior, bestTime, bestId = INF, INF, ""
    curPrior, curTime, curId = 0,0,""
    # Step 1. 우선순위가 높은 task 고르기
    for domain in readyQ:
        #print(timeLock[domain])
        if not timeLock[domain]: continue
        if timeLock[domain] > time: continue # 1-1 각 도메인별로 pop하기, 현재 채점이 진행 중이거나, lock 시간보다 현재 시간이 작으면 pass
        curPrior, curTime, curId= heapq.heappop(readyQ[domain]) # 그게 아니면 pop하기

        if (bestPrior > curPrior) or (bestPrior == curPrior and bestTime > curTime): # 만약 우선순위가 제일 높다면
            bestPrior, bestTime, bestId = curPrior, curTime, curId  # best변수들에 담기

        else:                                                       # 우선순위가 높지 않다면
            heapq.heappush(readyQ[domain], (curPrior, curTime, curId))  # 다시 큐에 집어넣기
    if bestPrior == INF:
        return
    cntQ -= 1

    # Step2. 쉬고 있는 채점기 중 가장 번호가 작은 채점기 빼기
    grader_idx = heapq.heappop(restQ)
    infoQ[grader_idx] = (domain, time)    # 현재 채점 중인 채점기의 정보 업데이트
    timeLock[domain] = INF  
def finish(time, J):            # time초에 J번 채점기 종료
    if J not in restQ:
        url, start = infoQ[J]                       # J번 채점기가 채점하고 있던 url과 start 시간
        start = int(start)
        time_gap = time-start                           # 시간 갭
        timeLock[url.split('/', 1)[0]] = start + 3 * time_gap   # Lock 다시 설정
        restQ.append(J)             # 쉬고 있는 채점기로 돌리기
        infoQ[J] = ()
    
# 요청에 따라 코드 제출 처리
for _ in range(Q):
    query = input().split()
    if query[0] == "100":   # 초기 100 3 codetree.ai/16 (N, url)
        init(int(query[1]), query[2])
    elif query[0] == "200": # 요청 200 5 1 codetree.ai/17
        pushQ(int(query[1]), int(query[2]), query[3])
    elif query[0] == "300": # 시도 300 1
        popQ(int(query[1]))
    elif query[0] == "400": # 종료 400 4 1
        finish(int(query[1]), int(query[2]))
    else:                   # 조회 500 7
        print(cntQ)