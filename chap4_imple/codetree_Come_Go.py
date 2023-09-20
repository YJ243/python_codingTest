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