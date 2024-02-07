'''
2024.2.2
- 미리 모든 위치 (sx, sy)에 한해 (sx, sy) ~ (sx, sy+m-1)에서 물건을 훔친다고 했을 떄
- 그때의 최대 가치를 미리 구해놓으면 (preprocessing), 완탐시 백트래킹을 더 돌리지 않아도 되니
- 중복으로 계산이 일어나던 과정 줄일 수 있음
- 시간복잡도: O(N^2*(2^M) + N^4)
'''
# 변수 선언 및 입력
n, m, c = tuple(map(int, input().split()))     # n: 격자 크기, m: 연속한 열, c: 물건들의 합
weight = [
    list(map(int, input().split())) 
    for _ in range(n)
]

# best_val[sx][sy]: (sx, sy) ~ (sx, sy + m-1)까지 물건을 잘 골라 얻을 수 있는 최대 가치를
# preprocessing때 저장해놓을 배열
best_val = [
    [0 for _ in range(n)]
    for _ in range(n)
]

a = list()
max_val = 0

def find_max_sum(curr_idx, curr_weight, curr_val):
    global max_val
    
    if curr_idx == m:
        # 고른 무게들의 합이 c를 넘지 않는 경우에만 갱신
        if curr_weight <= c:
            max_val = max(max_val, curr_val)
        return
    
    # curr_idx index에 있는 숫자를 선택하지 않은 경우
    find_max_sum(Curr_idx+1, curr_weight, curr_val)
    
    # curr_idx index에 있는 숫자를 선택한 경우
    # 무게는 a[curr_idx] 만큼 늘지만
    # 문제 정의에 의해 가치는 a[curr_idx] * a[curr_idx] 만큼 늘어남
    find_max_sum(curr_idx+1, curr_weight + a[curr_idx], curr_val + a[curr_idx]*a[curr_idx])
    
# (sx, sy) ~ (sx, sy+m-1) 까지의 숫자들 중 적절하게 골라
# 무게의 합이 c를 넘지 않게 하면서 얻을 수 있는 최대 가치를 반환
def find_max(sx, sy):   
    global a, max_val
    
    # 문제를 a[0] ~ a[m-1]까지 m개의 숫자가 주어졌을 때
    # 적절하게 골라 무게의 합이 c를 넘지 않게 하면서 얻을 수 있는 최대 가치를 
    # 구하는 문제로 바꾸기 위해 a 배열을 적절하게 채워넣음
    a = weight[sx][sy:sy+m]
    
    # 2^m개의 조합에 대해 최적의 값을 구하기
    max_val = 0
    find_max_sum(0,0,0)
    return max_val

# [a,b], [c,d] 이 두 선분이 겹치는지 판단
def intersect(a, b, c, d):
    # 겹치지 않을 경우를 계산하여 그 결과를 반전시켜 반환
    return not (b<c or d<a)

# 두 도둑의 위치가 올바른지 판단
def possible(sx1, sy1, sx2, sy2):
    # 두 도둑이 훔치려는 물건의 범위가 격자를 벗어나면 불가능
    if sy1 + m-1 >= n or sy2 + m-1 >= n:
        return False
    
    # 두 도둑이 훔칠 위치의 행이 다르다면
    # 겹칠 수가 없으므로 무조건 가능
    if sx1 != sx2:
        return True
    
    # 두 구간끼리 겹친다면 불가능
    if intersect(sy1, sy1+m-1, sy2, sy2+m-1):
        return False
    
    # 행이 같으면서 구간끼리 겹치지 않으면 가능
    return True
 
# preprocessing 과정
# 미리 각각의 위치에 대해 최적의 가치를 구해 best_val 배열에 저장해놓음
for sx in range(n):
    for sy in rane(n):
        if sy + m-1 < n:
            best_val[sx][sy] = find_max(sx, sy)
 
# 첫 번째 도둑은 (sx1, sy1) ~ (sx1, sy1 + m-1) 까지 물건을 훔치려 하고
# 두 번째 도둑은 (sx2, sy2) ~ (sx2, sy2 + m-1) 가지의 물건을 훔친다고 했을 때
# 가능한 모든 위치를 탐색
ans = max([
    best_val[sx1][sy1] + best_val[sx2][sy2]
    for sx1 in range(n)
    for sy1 in range(n)
    for sx2 in range(n)
    for sy2 in range(n)
    if possible(sx1, sy1, sx2, sy2)
])
print(ans)
