'''
2023.10.11 - 첫번째 시도
- 시간이 줄어들었는가
 1) 2시간 안에 문제 이해 + 코드짜기까지 완성했지만, 답이 틀림
    (그래서 시간이 줄어들었지만 아직 부족함)
- 실수가 줄어들었는가?
 1) heapq 우선순위 큐 사용은 잘함
 2) 코드를 완성하기까지 중간에 자잘자잘한 실수가 너무 잦음
    (ex, 범위 체크, 처음 init 등)
 3) bestDomain인데 그냥 domain으로 해서 맨 마지막에 선택된 domain에다가 잘못 대입했음
    이것때문에 3시간을 날림...후...실수 안하게 집중해서 문제 풀기!!!!!!!!!!
    
- 막히던 부분이 해결되었는가?
 1) 출력까지는 가게 됨
 2) 채점하는 로직은 잘 짜게 된거 같긴한데...
'''
from collections import defaultdict
import heapq
from typing import List, Dict, Tuple, Set, Optional
INF = 1000000001        # 최댓값

# 채점 task를 나타낼 자료구조 (대기큐에 있는 url HashSet, 채점 대기큐, 대기큐 원소 개수)
setQ: Set[str] = set()                                              # 현재 채점 대기큐에 있는 url만 모아놓는 자료구조 (큐에 u를 추가할때 있으면 빠르게 패스하기 위해)
readyQ: Dict[str, List[Tuple[int, int, str]]] = defaultdict(list)   # 채점 대기 큐, (key: domain, value(PQ): (p우선순위, t큐에 들어온 시간, id문제 번호)
cntQ: int = 0                                                       # 채점 대기 큐에 있는 task 개수

# 채점기를 나타낼 자료구조 (채점기 개수, 타임락, 쉬고있는 채점기PQ, 채점 중 채점기 정보)
N = 0                                          # 채점기의 수
timeLock: Dict[str, int] = defaultdict(int)    # 각 도메인 별로 언제까지 채점을 할 수 없는지 담아놓는 HashMap
# 0     := 아직 채점 안한 초기 도메인
# INF   := 현재 채점 중
# s+3*g := 종료시간이 s+g이었을 때 s+3*g까지는 채점 못
restQ: List[int] = []                          # 현재 쉬고 있는 채점기의 index를 모아놓은 PQ (가장 번호가 작은 채점기가 빨리 반환)
infoQ: List[Optional[Tuple[str, int]]] = []    # 현재 채점 중인 채점기의 정보를 모아놓은 배열
# (ex. 2번 채점기는 (domain, start) 채점중인 문제, 채점 시작 시간)

Q = int(input())        # 명령의 수

def init(grader_cnt, u0):                       # 초기 채점기 준비, 초기 태스크 큐에 넣기
    global N, cntQ, restQ, infoQ                # 채점기 개수, 태스크 수, 쉬고 있는 채점기, 채점기 정보
    N = grader_cnt                              # 1) 채점기 개수
    for i in range(1,N+1):                      # 채점기는 1 ~ N 번호
        heapq.heappush(restQ, i)                # 2) 쉬고 있는 채점기 PQ에 모두 추가
    infoQ = [() for _ in range(N+1)]            # 3) 현재 채점 중인 채점기 정보, 타임락은 지금 init 안함
    #************************************************************************************************************#
    setQ.add(u0)                                # 1) 현재 채점 대기큐 목록에 u0 넣기
    domain = u0.split('/',1)[0]                 # 도메인만 담기
    p_id = u0.split('/',1)[1]                   # 문제 id 담기
    heapq.heappush(readyQ[domain], (1, 0, p_id))# 2) 대기큐의 [domain]에다가 (우선순위, 큐에 들어온 시간, 문제id) 넣기
    cntQ += 1                                   # 3) 현재 대기큐에 들어있는 task 개수


def pushQ(time, prior, url):        # time초에 우선순위 prior이면서 url인 문제 채점 요청 들어옴
    global cntQ                     # 현재 대기큐에 들어있는 task 개수
    if url in setQ:                 # url과 정확히 일치하는 url이 단 하나라도 존재하면
        return                      # 큐에 추가하지 않고 넘어가기
    
    # 만약 똑같은 url이 대기큐에 없다면
    setQ.add(url)                                       # 1) 현재 대기큐 목록에 url 넣기
    domain = url.split('/',1)[0]                        # 도메인만 담기
    p_id = url.split('/',1)[1]                          # 문제 id 담기
    heapq.heappush(readyQ[domain], (prior, time, p_id)) # 2) 대기큐의 [domain]에다가 (우선순위, 큐에 들어온 시간, 문제id) 넣기
    cntQ += 1                                           # 3) 현재 대기큐에 들어있는 task 개수 추가

def popQ(time):                 # time초에 즉시 채점이 가능한 경우 우선순위가 가장 높은 task 채점 시도
    global cntQ                 # 현재 대기큐에 들어있는 task 개수

    # Step 0. 쉬고있는 채점기가 있는지 보기
    if not restQ: return        # 쉬고 있는 채점기가 하나도 없으면 바로 리턴

    # Step 1. 우선순위가 높은 task 고르기, 현재 큐에는 {(key)domain:(value)p,t,id}
    bestPrior, bestTime, bestId = INF, INF, "" # best task는 우선순위 숫자가 작고, 큐에 들어온 time이 작음
    curPrior, curTime, curId = 0, 0, ""        # 현재 우선순위, 현재 큐에 들어온 시간, 현재 문제 id
    bestDomain = ""
    for domain in readyQ:                      # 현재 대기큐에 있는 domain을 확인
        if timeLock[domain] > time: continue   # lock 시간보다 현재 시간이 작으면 무시
        if not readyQ[domain]: continue
        curPrior, curTime, curId= readyQ[domain][0] # 현재 보고 있는 domain에서 가장 우선순위가 높은 얘를 가져오기
        cur_domain = domain
        if (bestPrior > curPrior) or (bestPrior == curPrior and bestTime > curTime): # 만약 우선순위가 제일 높다면
            bestPrior, bestTime, bestId = curPrior, curTime, curId                   # best변수들에 담기
            bestDomain = cur_domain                                                  # 현재 도메인을 베스트 도메인으로
    
    if bestPrior == INF:            # 만약 모든 도메인에 대해서 확인했는데, 채점 가능한 task가 없다면
        return                      # 바로 리턴

    setQ.remove(bestDomain + '/' + bestId)  # 1) 현재 대기큐 목록에서 해당 url 빼기
    heapq.heappop(readyQ[bestDomain])           # 2) 대기큐에서 pop
    
    cntQ -= 1                               # 3) 현재 큐에 있는 task 개수 감소

    # Step2. 채점할 채점기 고르기
    grader_idx = heapq.heappop(restQ)       # 1) 쉬고 있는 채점기 중 가장 번호가 작은 채점기 빼기
    infoQ[grader_idx] = (bestDomain, time)  # 2) 현재 채점 중인 채점기의 정보 업데이트 (채점 도메인, 채점 시작 시간)
    timeLock[bestDomain] = INF                  # 3) 타임락에 INF를 넣어서 현재 채점 중이다 표시

def finish(time, J):            # time초에 J번 채점기 종료
    if J not in restQ:                              # 현재 채점 중인 채점기라면 (쉬고 있는 채점기 목록에 없다면)
        domain, start = infoQ[J]                    # J번 채점기가 채점하고 있던 url과 start 시간
        start = int(start)
        time_gap = time-start                       # 시간 갭 구하기
        timeLock[domain] = start + 3 * time_gap     # 1) Lock을 s+3*g으로 다시 설정
        heapq.heappush(restQ,J)                     # 2) 쉬고 있는 채점기로 돌리기
        infoQ[J] = ()                               # 3) 채점 중인 채점기 정보를 ()으로 지우기

# 요청에 따라 코드 제출 처리
for _ in range(Q):
    query = input().split()
    if query[0] == "100":   # 초기 100 3 codetree.ai/16 (N, url)
        init(int(query[1]), query[2]) # 채점기 개수, url
    elif query[0] == "200": # 요청 200 5 1 codetree.ai/17
        pushQ(int(query[1]), int(query[2]), query[3])
    elif query[0] == "300": # 시도 300 1
        popQ(int(query[1]))
    elif query[0] == "400": # 종료 400 4 1
        finish(int(query[1]), int(query[2]))
    else:                   # 조회 500 7
        print(cntQ)