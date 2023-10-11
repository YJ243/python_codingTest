'''
실수가 왜이렇게 많지?
1) query[0]을 가지고 비교해야 하는데, 그 뒤에 query[1], query[2], query[3], ... 이렇게 비교했다..
2) INF인데 INT라고 함
3) 전역변수인데 함수 내부에서 사용할 때 global 키워드를 안씀
4) 소문자 j인데 J라고 씀
5) query[1], query[2]인데 query[1]을 두 개 넣음
6) restList = [i for i in range(1, N+1)]을 range(1 + N+1)이라고 함...
'''

import heapq
from collections import defaultdict
from typing import List, Dict, Tuple, Set

INF = 1000000001
# 채점 task를 나타내는 자료구조 (1. 대기큐 태스크 개수, 2. url모음집 3. 대기큐)
setQ: Set[str] = set()                                              # 대기큐에 있는 url 모음집
cntQ:int  = 0                                                        # 대기큐에 있는 task 개수
readyQ = defaultdict(list)   # 채점대기큐: [key]domain별 [value]task(PQ)들을 모아놓은 해쉬맵, {: List[str, List[Tuple[int, int, str]]]}

# 채점기를 나타내는 자료구조 (1. 쉬고 있는 채점기 목록, 2. 채점 중인 채점기 상태, 3. 각 도메인 별 이후 채점 Lock 타임)
N:int = 0                                   # 채점기 개수
restList: List[int] = []                 # 쉬고 있는 채점기들, PQ로 구현하여 제일 숫자가 적은 채점기가 빠르게 나오도록
machineStatus: List[Tuple[int, str]] = []   # 채점기 상태를 저장하는 배열, [idx]는 채점기 idx, (채점 시작시간,채점 domain)
timeLock = defaultdict(int) # 해당 도메인이 언제까지 채점을 못하는지 저장, {: List[str, int] }

def init(_N, u0):       # _N개 채점기, 초기 url
    global N, restList, machineStatus
    N = _N                                      # 채점기 개수
    restList = [i for i in range(1,N+1)]     # 쉬고 있는 채점기에 추가
    machineStatus = [None for _ in range(N+1)]  # 채점기 초기 상태 None으로 저장
    pushQ(0, 1, u0)

def pushQ(t, p, u):
    global cntQ
    if u in setQ: 
        return                                 # 만약 똑같은 u가 있다면 무시

    setQ.add(u)                                            # url 모음지에 추가
    domain = u.split('/',1)[0]                             # 도메인 나누기
    p_id = u.split('/',1)[1]                               # 문제 번호 나누기
    heapq.heappush(readyQ[domain], (p, t, p_id))     # domain을 key로 하고 (p, t, p_id)를 value로 하는 원소 추가
    cntQ += 1                                              # 대기큐 개수 추가

def try_judge(t):
    global cntQ                     # 대기 큐에 있는 task 개수
    # 만약 쉬고 있는 채점기가 하나도 없다면
    if not restList: return         # 채점 종료하기

    # Step1. 채점할 task 찾기
    bestPrior, bestTime, bestDomain = INF, INF, ""
    # readyQ에서 domain별로 우선순위 확인
    for domain in readyQ:
        if not readyQ[domain]: continue             # 해당 도메인에 해당하는 대기 문제가 없다면 무시
        if timeLock[domain] > t: continue               # 현재 시간이 timeLock보다 작으면 무시
        curPrior, curTime, _ = readyQ[domain][0]

        if (bestPrior > curPrior) or (bestPrior == curPrior and bestTime > curTime):
            bestPrior, bestTime, bestDomain = curPrior, curTime, domain
    
    # 만약 채점할 task가 없다면 리턴
    if bestPrior == INF: 
        return

    _, _, p_id = heapq.heappop(readyQ[bestDomain]) # 채점 대기큐에서 채점할 도메인의 가장 우선순위 높은 task 반환
    setQ.remove(bestDomain + '/' + p_id)           # 대기큐에 있는 url 모음집에서 제거
    cntQ -= 1                                      # 대기큐 task 개수 감소

    # Step2. 채점기 찾기
    machineIdx = heapq.heappop(restList)     # 가장 번호가 작은 머신 출력
    machineStatus[machineIdx] = (t, bestDomain)
    timeLock[bestDomain] = INF


def finish(t, j):
    # 만약 J번 채점기가 채점중이 아니라면 리턴
    if j in restList: return         # 쉬고 있는 채점기에 잇으면 return
    if machineStatus[j] == None: return
    start, domain = machineStatus[j]
    gap = t-start
    timeLock[domain] = start + 3 * gap      # 타임락 업데이트
    machineStatus[j] = None                 # 머신 상태 None으로 돌리기
    heapq.heappush(restList,j)           # 쉬고있는 채점기에 추가


# 명령에 따른 채점 시작
Q = int(input())
for _ in range(Q):
    query = input().split()
    if query[0] == "100":
        init(int(query[1]), query[2])
    elif query[0] == "200":
        pushQ(int(query[1]), int(query[2]), query[3])
    elif query[0] == "300":
        try_judge(int(query[1]))
    elif query[0] == "400":
        finish(int(query[1]), int(query[2]))
    else:
        print(cntQ)