'''
2023.10.10 
문제를 이해하고 자료구조를 디자인하는 것이 어려운 문제
'''

import heapq
from collections import defaultdict
from typing import List, Tuple, Dict, Set, Optional

INF = 1000000001

# task 관리하는 자료구조
setQ: Set[str] = set()                                             # 채점 대기 큐에 있는 url set, url의 존재성을 판단하기 위해
sizeQ: int = 0                                                     # 채점 대기 큐에 있는 task 개수, 채점 대기큐 조회시 바로 출력하기 위해
waitQ: Dict[str, List[Tuple[int, int, str]]] = defaultdict(list)   # 도메인 별로 채점 대기 heapq 관리하는 자료구조. 자료는 (우선순위, 들어온 시각, id) 형태
                                                                   # key: str(domain), value는 task들의 배열이 될텐데, PQ로 관리가 됨
# 채점기 관리하는 자료구조
N = 0                                                       # 채점기 개수
stringLock: Dict[str, int] = defaultdict(int)               # (key: domain, value: time):= time에 domain을 채점할 수 있다
machineList: List[int] = []                                 # 쉬고 있는 채점기 번호들을 가지고 있는 Min Heap
machineStatus: List[Optional[Tuple[int, str]]] = []         # (채점 시작 시각, 채점 domain) 정보를 채점기 별로 가지고 있음


def parseURL(url: str) -> List[str]:    # URL에서 domain 과 id 구분하기
    return url.split('/', 1)

def getDomain(url: str) -> str:     # URL에서 domain 추출하기
    return parseURL(url)[0]

def popQ(domain) -> None:      # domain으로 시작하는 URL을 채점 대기 큐에서 제거하기 
    global sizeQ
    
    # 1. domain으로 시작하는 URL을 큐에서 제거하기, O(logQ)
    _, _, id = heapq.heappop(waitQ[domain])
    
    # 2. 채점 대기 큐 set에서 URL 제거하기, O(1)
    setQ.remove(domain + "/", id)
    
    # 3. sizeQ 관리하기
    sizeQ -= 1 

def judge(time):            # 특정 시간 time에 채점을 시도하는 함수 --> 어떤 task를 채점할지? 어떤 채점기를 사용할 지?-->O(300 + log Q + log N)
    if not machineList:     # 만약 쉬고 있는 채점기가 없다면, 채점 실패
        return
    
    # 1. 조건에 맞는 채점 대상 찾기
    bestPrior, bestTime, bestDomain = INF, 0, ""
    
    for domain, que in waitQ.items():       # Domain 별로 확인하기, O(300)
        if not que: continue        # 해당 Domain으로 시작하는 채점 대기 URL이 없는 경우, 무시하기

        if stringLock[domain] > time: continue      # 해당 Domain이 아직 채점 가능 상태가 아닌 경우, 무시하기

        candPrior, candTime, _ = que[0]             # 해당 Domain에서 가장 우선순위가 높은 것을 가져오기
        if candPrior < bestPrior or (candPrior == bestPrior and candTime < bestTime):
            bestPrior, bestTime, bestDomain = candPrior, candTime, domain
            
    if bestPrior == INF:                        # 채점 가능한 것이 없다면 채점 실패
        return
    
    # 2. 조건에 맞는 채점기 찾기
    machineIdx = heapq.heappop(machienList)         # 쉬고 있는 채점기 중 가장 낮은 번호 찾기 O(logN)
    machineStatus[machineIdx] = (time, bestDomain)  # 채점기 상태 업데이트, time시간에 bestDomain 채점하기 시작했어
    popQ(bestDomain)                                # 선택된 도메인에서 채점할 URL 꺼내오기
    stringLock[bestDomain] = INF                    # domain에 대해 채점 Lock 걸기, 채점에 들어오는 도메인이 현재 채점을 진행중인 도메인 중 하나라면 불가능하도록

def pushQ(time, prior, url) -> None:                # url을 채점 대기 큐에 삽입, 시간은 time이고 우선순위는 prior
    global sizeQ
    
    if url in setQ:      # 이미 동일한 url이 있다면 추가하지 않음, O(1)
        return           # 만약 setQ가 아니라 list였으면 O(Q)이었음
    
    # 1. url 모음집에 url 추가하기, O(1)
    setQ.add(url)
    
    # 2. waitQ에 추가하기, O(log Q)
    domain, id = parseURL(url)
    heapq.heappush(waitQ[domain], (prior, time, id))    # prior -> time 순으로 넣어야 자연스럽게 우선순위가 높은 것을 선택할 수 있음
    
    # 3. sizeQ 관리하기
    sizeQ += 1

def finish(time:int, idx:int)  -> None:             # idx번 채점기의 채점 종료하기
    if machineStatus[idx] == None:                  # 현재 채점 중이 아니라면 무시하기
        return
    
    # 1. 채점에 걸린 시간에 맞춰서 domain lock을 걸어주기
    startTime, domain = machineStatus[idx]
    gap = time - startTime
    stringLock[domain] = startTime + gap*3      # 채점 대기 Lock 시간 걸기
    
    # 2. 채점기가 쉬는 중이라고 표시
    machineStatus[idx] = None
    
    # 3. 쉬고 있는 채점기 리스트에 idx 추가하기
    heapq.heappush(machineList, idx)
    
def init(_N: int, u0: str):           # 초기화
    global N, machineList, machineStatus
    N = _N
    machineList = list(range(1,N+1))                        # 쉬고 있는 채점기의 번호를 setup
    machineStatus = [None for _ in range(N+1)]              # 각 채점기의 상태를 None(쉬고 있는 중)이라고 초기화
    
    pushQ(0,1,u0)           # 0초에 우선순위가 1이고 url이 u0인 채점 요청이 들어왔따


numQ = int(input())
for _ in range(numQ):
    query = input().split()
    if query[0] == "100":
        init(int(query[1]), query[2])
    if query[0] == "200":
        pushQ(int(query[1]), int(query[2]), query[3])   # O(log Q)
    if query[0] == "300":
        judge(int(query[1]))                            # O(300 + log Q + log N)
    if query[0] == "400":
        finish(int(query[1]), int(query[2]))            # O(log N)
    if query[0] == "500":
        print(sizeQ)
# 총 시간 복잡도: O(Q * (300 + log Q + log N))