'''
2024.2.2 내 풀이
'''
n, m, c = map(int, input().split())     # n: 격자 크기, m: 연속한 열, c: 물건들의 합

grid = [list(map(int, input().split())) for _ in range(n)]  # 격자 입력받기
selected = []  # 선택한 방들의 무게

ans = 0     # 가치의 총 합 중 최댓값
cur_sum = 0
cur_value = 0
def Possible(a, b, c, d):     # (a,b),(c,d)에서 시작하는게 가능한지 판별하는 함수
    if a == c:  # 행이 같은 경우
        for i in range(m):
            # 범위 벗어나면 false
            if b+i >= n or d+i >= n:
                return False
            # 겹치면 false
            if b+i >= d:
                return False
    else:       # 행이 같지 않은 경우
        for i in range(m):
            if b+i >= n or d+i >= n:
                return False
    return True

def Choose(x, y, idx):           # (x,y)점을 선택하는지 결정하는 함수
    global cur_sum, cur_value
    if idx == m:    # m개가 되었다면
        if sum(selected) <= c:
            if cur_sum < sum(selected):
                cur_sum = sum(selected)
                cur_value = 0
                for num in selected:
                    cur_value += num*num
        return
    
    selected.append(grid[x][y])
    Choose(x, y+1, idx+1)
    selected.pop()

    Choose(x, y+1, idx+1)


def Find_Max_value(x, y):   # (x,y)점에서 연속한 m개의 열 중 합이 C를 넘지 않는 한에서 최댓값을 구해주는 함수
    global cur_sum, cur_value
    cur_sum = 0
    Choose(x,y, 0)

    ret = cur_value
    return ret
    

for i in range(n):
    for j in range(n):
        for k in range(n):
            for l in range(n):
                # A 도둑은 (i,j)에서 시작, B 도둑은 (k,l)에서 시작
                if Possible(i,j,k,l):
                    for idx in range(m):
                        curr = Find_Max_value(i,j) + Find_Max_value(k,l)
                        ans = max(ans, curr)

print(ans)