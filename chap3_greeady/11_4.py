'''
date: 2023.07.26
name: Yejin
title: can't make
'''
from itertools import combinations 
n = int(input())
numbers = list(map(int, input().split()))
numbers.sort()
answer = 0
k = 0

while True:
    answer += 1 # 1부터 증가시키면서 확인
    for i in numbers: 
        if answer == i: # 만약 같은 원소를 가지고 있다면
            break
    if i == numbers[len(numbers)-1]:
        # 끝까지 비교했는데, 가지고 있지 않다면
        for k in range(2, len(numbers)+1): # i==2,3,4,... 개씩 뽑으면서 비교
            data = list(combinations(numbers, k))
            for num in data:
                tmp = 0 # 더한값
                for j in range(k):
                    tmp += num[j]    
                if tmp == answer: # 조합해서 만들 수 있다면
                    break
            if tmp == answer:
                break    
    if k == len(numbers):
        break # 조합으로 만든 경우의 수 안에 있지 않다면 답
       
print(answer)
