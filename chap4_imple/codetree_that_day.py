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