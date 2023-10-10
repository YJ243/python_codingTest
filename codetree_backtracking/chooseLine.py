'''
2023.10.10
겹치지 않게 선분 고르기
- 나는 시간 초과가 뜸
- 왜냐면 1번->2번 순서대로 선분을 선택하기도 하지만, 2번->!번 순서대로 
  똑같은 조합을 만들어 내기도 하기 때문에 시간복잡도 = O(N!)
'''
n = int(input())
lines = [list(map(int, input().split())) for _ in range(n)]
cur = []
max_r = 0

def verify_lines():
    # 여기서 겹치는지 어떻게 확인하지?
    if len(lines) == 1: return True 
    tmp_line = sorted(cur, key=lambda x : (x[0], x[1]))
    #print(tmp_line)
    
    for i in range(len(cur)-1):
        for j in range(i+1, len(cur)):
            # 두 개의 선분을 잡아서 비교하는데
            # 만약 앞에 있는 선분 끝점이 뒤에 있는 선분이 뒤에 있는 선분 끝점보다 크다면
            if tmp_line[i][1] >= tmp_line[j][0]: return False
    return True

def update_result():        # 현재 최댓값을 비교하여 업데이트하는 함수
    global max_r
    if max_r < len(cur):    # 현재까지 겹치지 않은 선분을 선택한 값과, 지금의 선분 개수를 비교하여
        max_r = len(cur)    # 만약 현재가 크다면 업데이트

def choose_line(num):       # num번째 선분(0,1,...,n-1)을 선택하는지 여부를 결정하는 함수

    if num == n:            # 현재 주어진 선분을 모두 탐색했다면
        if verify_lines():  # 현재 선택된 선분들이 겹치지 않는지 확인
            # 만약 겹치지 않는다면
            update_result() # 결과값 업데이트 하기
        return              # 반환하기
    
    for i in range(n): # 여기서 이전에 뽑힌 원소가 있다면 그걸 빼야 하는데,,,
        if (lines[i][0], lines[i][1]) in cur: continue
        cur.append((lines[i][0], lines[i][1]))
        if verify_lines():
            update_result()
        choose_line(num+1)
        cur.pop()


choose_line(0)
print(max_r)


## 고친 답
'''
    for i in range(n): # 여기서 이전에 뽑힌 원소가 있다면 그걸 빼야 하는데,,,
        if (lines[i][0], lines[i][1]) in cur: continue
        cur.append((lines[i][0], lines[i][1]))
        if verify_lines():
            update_result()
        choose_line(num+1)
        cur.pop()
    이 부분에서 순열이 아니라 조합으로 바꿈->O(2^N)
'''
n = int(input())
lines = [list(map(int, input().split())) for _ in range(n)]
cur = []
max_r = 0

def verify_lines():         # 현재까지 만들어진 선분들이 겹치는지 확인하는 함수
    if len(lines) == 1: return True     # 선분이 하나라면 바로 True 리턴
    tmp_line = sorted(cur, key=lambda x : (x[0], x[1])) # 선분 정렬하는데, 시작점, 끝점 기준으로 정렬

    for i in range(len(cur)-1):
        for j in range(i+1, len(cur)):
            # 두 개의 선분을 잡아서 비교하는데,
            # 만약 앞에 있는 선분 끝점이 뒤에 있는 선분의 시작점보다 크다면
            if tmp_line[i][1] >= tmp_line[j][0]: return False
    return True

def update_result():        # 현재 최댓값을 비교하여 업데이트하는 함수
    global max_r
    if max_r < len(cur):    # 현재까지 겹치지 않은 선분 개수의 최댓값과, 지금의 선분 개수를 비교하여
        max_r = len(cur)    # 만약 현재가 크다면 업데이트

def choose_line(num):       # num번째 선분(0, 1, ..., n-1)을 선택하는지 여부를 결정하는 함수
    if num == n:            # 현재 주어진 선분을 모두 탐색했다면
        if verify_lines():  # 현재 주어진 선분들이 겹치는지 확인
            update_result() # 만약 겹치지 않는다면 결과값 업데이트하기
        return
    
    cur.append((lines[num][0], lines[num][1]])  # 주어진 선분 num번째 추기 => 선택O
    choose_lines(num+1)     # num+1번째 선분을 선택하는지 여부 결정하러 가기
    cur.pop()               # num번째 선분을 빼기                          => 선택X
    choose_line(num+1)      # num번째 선분 선택 안한채로 num+1번째 선분 선택여부 결정하러 가기

choose_line(0)
print(max_r)

## 해설
# 각 선분을 선택하는 가능한 모든 조합을 만든 후,
# 그 중 전혀 겹치지 않는 경우에 해당하는 조합에 대해서만 최대 선분의 수 갱신

# 두 선분이 겹치는지에 대한 여부는 특정 점이 다른 선분과 겹치는 부분이 단 한 곳이라도 있는지 확인
# 2개의 선분 중 각 선분을 이루는 총 4개의 점에 대해 각각 다른 선분 내에 속하는지 확인

# 변수 선언 및 입력:
n = int(input())
segments = [
    tuple(map(int, input().split()))
    for _ in range(n)
]

ans = 0
selected_segs = list()

def overlapped(seg1, seg2):
    (ax1, ax2), (bx1, bx2) = seg1, seg2
    
    # 두 선분이 겹치는지 여부는
    # 한 점이 다른 선분에 포함되는 경우로 판단 가능
    return (ax1 <= bx1 and bx1 <= ax2) or (ax1 <= bx2 and bx2 <= ax2) or \
        (bx1 <= ax1 and ax1 <= bx2) or (bx1 <= ax2 and ax2 <= bx2)
        
def possible():
    # 단 한쌍이라도 선분끼리 겹치면 안됨
    for i, seg1 in enumerate(selected_segs):
        for j, seg2 in enumerate(selected_segs):
            if i < j and overlapped(seg1, seg2):
                return False
    return True

def find_max_segments(cnt):
    global ans
    
    if cnt == n:
        if possible():
            ans = max(ans, len(selected_segs))
        return
    
    selected_segs.append(segmets[cnt])
    find_max_segments(cnt+1)
    selected_segs.pop()
    
    find_max_segments(cnt+1)
    
rind_max_segments(0)
print(ans)