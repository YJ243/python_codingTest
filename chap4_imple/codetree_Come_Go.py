'''
2023.09.21
'''
# 내가 푼 답
# R: 시작점 표시, 끝점 표시X
# L: 시작점 표시X, 끝점 표시

n = int(input())
cur = 1000
line = [ 0 for _ in range(2000)]

for i in range(n):
    x, d = input().split()
    x = int(X)
    
    if d == 'R':
        line[cur] += 1 # 시작점 표시
        for i in range(x-1):
            cur += 1
            line[cur] += 1
        cur += 1 # 다 끝나고 cur점 오른쪽으로 옮겨줌 (끝점표시X)
    else:
        # 시작점 표시 안하고 바로 for문으로, 끝점까지 표시
        for i in range(x):
            cur -= 1
            line[cur] += 1

result = 0
# 각 점에 1이 있다는 건 그 점을 시작점으로 길이가 1인 선분이 있다는 것
for i in range(len(line)):
    if line[i] >= 2:
        result += 1
print(result)


## 해설
OFFSET = 1000
MAX_R = 2000

# 변수 선언 및 입력
n = int(input())
segments = []

# 현재 위치
cur = 0

for _ in range(n):
    distance, direction = tuple(input().split())
    distance = int(distance)
    
    if direction == 'L':
        # 왼쪽으로 이동할 경우: cur-distance ~ cur까지 경로 이동
        section_left = cur-distance
        section_right = cur
        cur -= distance
    else:
        # 오른쪽으로 이동할 경우: cur ~ cur+distance까지 경로 이동
        section_left = cur
        section_right = cur+distance
        
    segments.append([section_left, section_right])

checked = [0] * (MAX_R + 1)

for x1, x2 in segments:
    # offset을 더해줌
    x1, x2 = x1+OFFSET, x2+OFFSET
    
    # 구간을 칠해줌
    # 구간 단위로 진행하는 문제니 x2에 등호가 들어가지 않음
    for i in range(x1, x2):
        checked[i] += 1
        
        
# 2번 이상 지나간 영역의 크기를 구함
cnt = 0
for elem in checked:
    if elem >= 2:
        cnt += 1
print(cnt)