'''
date: 2023.07.25
name: Yejin
title: flip
'''

data = input()
result = int(data[0])

first = 0
flag_first = 0 # 같은게 언제 끝나니? 1이면 아직 안끝남
second = 1
flag_second = 1
target = int(data[0])

# 첫번째 숫자로 통일
for i in range(1, len(data)):
    if int(data[i]) == target:
        flag_first = 0
        continue
    else:
        if flag_first == 0:
            first += 1
            flag_first = 1

# 두번째 숫자로 통일
for i in range(1, len(data)):
    if int(data[i]) == target:
        if flag_second == 0: # 같은데 plus 안했어
            second += 1
            flag_second = 1
        else:
            continue # 이미 plus했어
    else: # 다르면
        flag_second = 0        
        continue # 안뒤집고 넘어가기


# 둘 중 적은 걸로 답
print(min(first, second))
print(first)
print(second)