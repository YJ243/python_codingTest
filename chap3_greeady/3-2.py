'''
date: 2023.06.28
name: yejin
title: 큰 수의 법칙
'''
n, m, k = map(int, input().split()) # 배열 크기, 숫자 더해지는 횟수, 연속해서 더해질 수 있는 개
numbers = list(map(int, input().split()))

numbers.sort(reverse=True) # 내림차순 정칙

answer = 0
# 총 m 번 더하는데, 가장 큰 수를 k번/두번째 큰 수를 1번 더하면서 반복
while m != 0:
    for j in range(k):
        answer += numbers[0]
        if m == 0:
            break
        m -= 1
    answer += numbers[1]
    m -= 1
print(answer)