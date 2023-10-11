import sys
import heapq
from collections import defaultdict
from typing import List, Tuple, Dict, Set, Optional
INF = sys.maxsize
si = sys.stdin.readline
setQ: Set[str] = set()                                              # 채점 대기 큐에 있는 url set
sizeQ: int = 0                                                      # 채점 대기 큐에 있는 task 개수
waitQ: Dict[str, List[Tuple[int, int, str]]] = defaultdict(list)    # 도메인 별로 채점 대기 heapq 관리하는 자료구조. 자료는 (우선순위, 들어온 시각, id) 형태
N = 0
stringLock: Dict[str, int] = defaultdict(int)           # (key: domain, value: time) := time 에 domain을 채점할 수 있다
machineList: List[int] = []                             # 사용 가능한 채점기 번호들을 가지고 있는 Min Heap
machineStatus: List[Optional[Tuple[int, str]]] = []     # (채점 시작 시각, 채점 domain) 정보를 채점기 별로 들고 있다.


def parseURL(url: str) -> List[str]:    # URL에서 domain 과 id 구분하기
    return url.split('/', 1)
def getDomain(url: str) -> str:     # URL에서 domain 추출하기
    return parseURL(url)[0]




def pushQ(time: int, prior: int, url: str) -> None:  # url을 채점 대기 큐에 삽입한다. 시간은 time이며, 우선순위는 prior 이다. O(log Q)
    global sizeQ
    if url in setQ:  # 이미 동일한 url이 있다면 추가하지 않음, O(1)
        return
    # 1. 채점 대기 큐에 url 추가하기, O(1)
    setQ.add(url)
    # 2. waitQ에 추가하기, O(log Q)
    domain, id = parseURL(url)
    heapq.heappush(waitQ[domain], (prior, time, id))
    # 3. sizeQ 관리하기
    sizeQ += 1                                  



def judge(time:int) -> None:                 # time초에 즉시 채점이 가능한 경우 우선순위가 가장 높은 task 채점 시도
    if not machineList: 
        return        # 쉬고 있는 채점기가 하나도 없으면 바로 리턴

    # Step 1. 우선순위가 높은 task 고르기, 현재 큐에는 {(key)domain:(value)p,t,id}
    bestPrior, bestTime, bestDomain = INF, INF, "" # best task는 우선순위 숫자가 작고, 큐에 들어온 time이 작음
    
    for domain, que in waitQ.items():  # Domain 별로 확인하기, O(300)
        if not que: continue  # 해당 Domain으로 시작하는 채점 대기 URL이 없는 경우, 무시하기
        if stringLock[domain] > time: continue  # 해당 Domain이 아직 채점 가능 상태가 아닌 경우, 무시하기
        candPrior, candTime, _ = que[0] # 해당 Domain에서 제일 우선순위가 높은 것 가져오기
        if candPrior < bestPrior or (candPrior == bestPrior and candTime < bestTime):
            bestPrior, bestTime, bestDomain = candPrior, candTime, domain

    
    if bestPrior == INF:            # 만약 모든 도메인에 대해서 확인했는데, 채점 가능한 task가 없다면
        return                      # 바로 리턴

    machineIdx = heapq.heappop(machineList)       # 1) 쉬고 있는 채점기 중 가장 번호가 작은 채점기 빼기
    machineStatus[machineIdx] = (time, bestDomain)  # 2) 현재 채점 중인 채점기의 정보 업데이트 (채점 도메인, 채점 시작 시간)
    
    global sizeQ                 # 현재 대기큐에 들어있는 task 개수
    _, _, c_id = heapq.heappop(waitQ[bestDomain])       # 2) 대기큐에서 pop
    setQ.remove(bestDomain + "/" + c_id)  # 1) 현재 대기큐 목록에서 해당 url 빼기
    sizeQ -= 1                               # 3) 현재 큐에 있는 task 개수 감소
    
    stringLock[bestDomain] = INF                  # 3) 타임락에 INF를 넣어서 현재 채점 중이다 표시

def init(_N: int, u0: str) -> None:   # 초기화
    global N, machineList, machineStatus
    N = _N
    machineList = list(range(1, N + 1))             # 쉬고 있는 채점기 번호들 setup
    machineStatus = [None for _ in range(N + 1)]    # 각 채점기의 상태
    pushQ(0, 1, u0) # 0초에 우선순위 1이고 url이 u0 인 채점 요청이 들어왔다.


def finish(time: int, idx: int) -> None:  # idx번 채점기의 채점 종료하기, O(log N)
    if machineStatus[idx] == None:  # 채점 중이 아니라면 무시하기
        return
    
    # 1. 채점에 걸린 시간에 맞춰서 domain lock 걸기
    startTime, domain = machineStatus[idx]
    gap = time - startTime
    stringLock[domain] = startTime + gap * 3    # 채점 대기 Lock 제한 시간 걸기
    # 2. 채점기 쉬는 중이라고 표기하기
    machineStatus[idx] = None   
    # 3. 쉬고 있는 채점기 리스트에 idx 추가하기, O(log N)
    heapq.heappush(machineList, idx)
    

# 요청에 따라 코드 제출 처리
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