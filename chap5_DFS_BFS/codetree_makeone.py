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