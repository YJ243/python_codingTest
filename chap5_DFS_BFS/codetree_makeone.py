'''
2023.11.1
4가지 연산을 이용하여 1 만들기
https://www.codetree.ai/missions/2/problems/make-one-using-four-operations?&utm_source=clipboard&utm_medium=text
# 실수 1: 가장 작은 값과 큰 값의 경우를 생각 안함 => TC를 만들 때 가장 작은 경우, 큰 경우를 생각하기
# 실수 2: visited 배열의 크기를 N+1로 해서, 값이 N+1, N+2, N+3으로 커질 때 index 범위 오류 남
'''

from collections import deque

N = int(input())
INF = 10000000                          # viisted 최대 범위 숫자
visited = [False for _ in range(INF)]   # visited[i]: i번 숫자를 만든 적이 있는지
q = deque()

# -1, +1, /2, /3을 한 값을 구해주는 함수
def make_next(cur, i):      # cur숫자에서 i번 연산을 수행
    if i == 0:
        return cur - 1
    elif i == 1:
        return cur + 1
    elif i == 2:
        if cur % 2 != 0:
            return -1
        return cur // 2
    else:
        if cur % 3 != 0:
            return -1
        return cur // 3

result = 0      # 출력값
def bfs():
    next_num = 0
    while q:
        num, cnt = q.popleft()
        if num == 1: return cnt     # 만약 처음 값이 1이라면 아무런 연산을 수행하지 않아야 하므로 바로 리턴
        for i in range(4):
            next_num = make_next(num, i)    # -1, 1, /2, /3 연산을 수행한 뒤의 값
            if next_num == -1:      # 만약 나누는 연산인 경우 나누어 떨어지지 않는다면 무시
                continue
            if next_num == 1:       # 1을 처음으로 만들었다면
                break               # for문 나가기
            
            if not visited[next_num]:   # 해당 숫자를 만든 적이 없다면
                visited[next_num] = True    # 해당 값을 방문했다고 표시
                q.append((next_num, cnt+1))
        if next_num == 1:   # 1을 만들었다면
            return cnt + 1  # 이전 카운트+1을 리턴

visited[N] = True   # 입력값 방문처리
q.append((N,0))     # 입력값과 연산 수행횟수 큐에 넣기
print(bfs())

'''
해설
- 이제까지 BFS를 생각할 때는 위치를 노드, 간선은 인접한 칸으로 가는 선 이정도로 생각했음
- 이 문제에서는 각 숫자들이 노드, 연산이 간선으로 간주하여 그래프를 그릴 수 있음
    => 가중치가 전부 1인 그래프가 주어졌을 때 정점 n으로부터 정점 1까지의 최단거리를 구하는 문제=BFS
- 정점을 1에서 2n-1번까지 사용해 최단거리를 구해야 함
    => n보다 큰 값을 만든 다음 2/3으로 숫자를 나눠 1로 더 빨리 갈 수 있음
    => -1 연산을 n-1번 반복하면 항상 1이 됨(답은 최대 n-1)
    => n에 +1 연산을 n-1번 연산을 했을 때 = 2n-1이 됨, 이 최댓값까지만 정점을 만들어 최단거리를 구하면 됨
- 시간복잡도 = 정점 총 2n-1, 각 정점 당 최대 4개의 정점 = O(2n-1*4)=o(n)
'''

from collections import deque
import sys
import enum

OPERATOR_NUM = 4
INT_MAX = sys.maxsize

class OPERATOR(enum.Enum):
    SUBTRACT = 0
    ADD = 1
    DIV2 = 2
    DIV3 = 3

n = int(input())
ans = INT_MAX

q = deque()
visited = [False for _ in range(2*n)]

# step[i]: 정점 n에서 시작해서 정점 i 지점에 도달하기 위한 최단거리를 기록
step = [0 for _ in range(2*n)]

# num 값에 해당 operator를 사용할 수 있는지 판단
# 2로 나누거나 3으로 나누려는 경우 num이 해당 값으로 나누어 떨어질 때만
# 해당 연산을 사용 가능
def possible(num, op):
    if op == OPERATOR.SUBTRACT.value or op == OPERATOR.ADD.value:
        return True
    elif op == OPERATOR.DIV2.value:
        return num % 2 == 0
    else:
        return num % 3 == 0

# num에 op연산을 수행했을 때의 결과를 반환
def calculate(num, op):
    if op == OPERATOR.SUBTRACT.value:
        return num - 1
    elif op == OPERATOR.ADD.value:
        return num + 1
    elif op == OPERATOR.DIV2.value:
        return num // 2
    else:
        return num // 3

# 1에서 2n-1사이의 숫자만 이용해도 올바른 답을 구할 수 있으므로
# 그 범위 안에 들어오는 숫자인지 확인
def in_range(num):
    return 1 <= num and num <= 2*n-1

# 1에서 2n-1사이의 숫자이면서 아직 방문한 적이 없다면 가야함
def can_go(num):
    return in_range(num) and not visited[num]

# queue에 새로운 위치를 추가하고 방문 여부를 표시
def push(num, new_step):
    q.append(num)
    visited[num] = True
    step[num] = new_step

# BFS를 통해 최소 연산 횟수를 구하기
def find_min():
    global ans
    
    # queue에 남은 것이 없을 때까지 반복
    while q:
        # queue에서 가장 먼저 들어온 원소를 빼기
        curr_num = q.popleft()
        
        # queue에서 뺸 원소의 위치를 기준으로 4가지 연산을 적용
        for i in range(OPERATOR_NUM):
            # 연산을 적용할 수 없는 경우라면 패스
            if not possible(curr_num, i):
                continue
            new_num = calculate(curr_num, i)
            # 아직 방문한 적이 없으면서 갈 수 있는 곳이라면 새로 queue에 넣어줌
            if can_go(new_num):
                # 최단 거리는 이전 최단거리에 1이 증가
                push(new_num, step[curr_num] + 1)
        
        # 1번 정점까지 가는 데 필요한 최소 연산 횟수를 답으로 기록
        ans = step[1]

# BFS를 통해 최소 연산 횟수를 구하기
push(n,0)
find_min()
print(ans)