'''
date: 2023.07.25
name: Yejin
title: adventurer

'''

n = int(input()) # N명
data = list(map(int, input().split())) # 각 공포도

data.sort() # 입력받은 공포도 정렬하기
answer = 0
tmp = 0
guild = 0
for i in data:
    if i == 1:
        answer += 1
    elif i > 1:
        #guild = i-1 # 필요한 수, 공포가 2이면 1명만 더 있으면 됨
        tmp += 1 # 현재 파티원
        # 이제 tmp 이상만 되면 됨
        # 그 다음이 tmp 이상이고 
        if tmp < i: # 만약 현재 파티원수가 현재 공포도보다 작다면
            continue
        else: # 크거나 같다면
            answer += 1
            tmp = 0

print(answer)
            
        