''' 
date:2023.09.19
'''
## 흐른 시간 계산 
# 
# 1) 시뮬레이션 (2시 5분 -> 4시 1분)
#

h, m = 2, 5
elapsed_time = 0

while True:
    if hour == 4 and min == 1:
        break
    elapsed_time += 1
    m += 1
    
    if m == 60:
        h += 1
        m = 0
print(elapsed_time)
# 
# 2) 차이 빼기 (a시 b분 -> c시 d분)
# 
# 흐른 시간을 계산할 때에는 시뮬레이션X
# 0시 0분부터 각 시간까지 걸리는 시간 재기 
a, b, c, d = map(int, input().split())

print((a*60+b) -(c*60+d)

#######################################################33
## 흐른 날짜 계산
# 
# 1) 시뮬레이션 (2월 5일 -> 4월 1일)
# 
m, d = 2, 5
elapsed_days = 0

num_of_days = [0,31,28,31,30,31,30,31,31,30,31,30,31]

while True:
    if m == 4 and d == 1:
        break
    elapsed_days += 1
    d += 1
    
    if d > num_of_days[m]:
        d = 1
        m += 1
print(elapsed_days)

#
# 2) 날짜 차이 빼기 (m1월 d1일 -> m2월 d2일)
#

m1, d1, m2, d2 = map(int, input().split())

def num_of_days(m,d):
    total_days = 0
    # 1월부터 (m-1)월까지는 전부 채워져 있음
    for i in range(1, m):
        total_days += num_of_days[i]
    # m월의 경우 정확히 d일만 있음
    total_days += d
    return total_days

# 출력
total_days = num_of_days(m2,d2) - num_of_days(m1,d1)
print(total_days)

''' 날짜 계산 내풀이 '''
total_days = 0
for i in range(m1+1, m2):
    total_days += num_of_days[i]
if m1 == m2:
    total = d2-d1+1
else:
    total += (num_of_days[m1]-d1+1)+d2
print(total)

#######################################################33
## 흐른 날짜/시간 계산
# 
# 1) 날짜/시간 차이 빼기
#

a, b, c = tuple(map(int, input().split()))

# 차이 계산
diff = (a*24*60 + b*60 + c) - (11*24*60 + 11*60+ 11)

# 출력
if diff < 0:
    print(-1)
else:
    print(diff)

''' 날짜 시간 계산 내풀이 '''

def num_of_min(a,b,c):
    total_min = 0
    # 11일 0시 0분 ~
    total_min += (a-11)*24*60 + b*60 + c
    return total_min
start_min = num_of_min(11,11,11)
end_min = num_of_min(a,b,c)

if end_min-start_min < 0:
    print(-1)
else:
    print(end_min-start_min)

