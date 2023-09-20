'''
date: 2023.09.19
'''

# 1월 1일 기준으로 각 날짜까지 일수 구하기
# 그 차이 구하기

# 변수 선언 및 입력
m1, d1, m2, d2 = map(int, input().split())

num_of_days = [0,31,28,31,30,31,30,31,31,30,31,30,31]
day = ["Mon", "Tue", "Wed", "Thr", "Fri", "Sat", "Sun"]
def num_of_days(m,d):
    total_days = 0
    # 1월부터 (m-1)월 까지는 전부 꽉 채워져 있음
    for i in range(1, m):
        total_days += num_of_days[i]
    
    # m월의 경우에는 정확히 d일만 있음
    total_days += d
    return total_days

# 두 날짜간의 차이가 몇 일인지 구하기
diff = num_of_days(m2,d2) - num_of_days(m1,d1)

# 음수인 경우, 양수를 넘겨 계산
while diff < 0:
    diff += 7

print(day[diff % 7])

''' 내 처음 답..'''
plus_days = 0
if m1>m2:
    for i in range(m1-m2):
        plus_days += num_of_days[m2+i]
    plus_days += d1-d2
    plus_days %= 7
    print(date[-plus_days])
else:
    for i in range(m2-m1):
        plus_days += num_of_days[m1+i]
    plus_days += d2-d1
    plus_days %= 7
    
    print(date[plus_days])