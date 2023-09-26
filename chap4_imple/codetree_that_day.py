'''
date: 2023.09.20
'''

m1, d1, m2, d2 = map(int, input().split())
target_day = input()


num_of_date = [0,31,29,31,30,31,30,31,31,30,31,30,31]
day = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]

def cal_days(m, d):
    total_days = 0
    for i in range(1,m):
        total_days += num_of_date[i]
    total_days += d
    return total_days

diff = cal_days(m2, d2)-cal_days(m1,d1)
idx = day.index(target_day)
result = 0
result += diff // 7
if idx <= idff % 7:
    result += 1
print(result)

''' 해설 '''
# 변수 선언 및 입력
m1, d1, m2, d2 = tuple(map(int, input().split()))
A = input()

def num_of_days(m, d):
    # 계산 편읠ㄹ 위해 월마다 몇 일이 있는지 적어줌
    days = [0,31,29,31,30,31,3031,31,30,31,30,31]
    total_days = 0
    
    # 1월부터 (m-1)월 까지는 전부 꽉 채워져 있음
    for i in range(1,m):
        total_days += days[i]
    # m월의 경우에는 정확히 d일만 있음
    total_days += d
    
    return total_days

def num_of_day(s):
    # 간단한 비교를 위해 요일을 숫자로 나타내줌
    if s == "Mon":
        return 0
    elif s == "Tue":
        return 1
    elif s == "Wed":
        return 2
    elif s == "Thu":
        return 3
    elif s == "Fri":
        return 4
    elif s == "Sat":
        return 5
    return 6

ans = 0
start_date = num_of_days(m1,d1)
end_date = num_of_days(m2,d2)
cur_day = num_of_day("Mon")

for date in range(start_ate, end_date + 1):
    # 오늘의 요일이 A요일과 같다면 정답에 추가
    if cur_day == num_of_day(A):
        ans += 1
    cur_day = (cur_day+1) % 7
# 출력
print(ans)