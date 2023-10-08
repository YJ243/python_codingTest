'''
date: 2023.09.04
name: Yejin
title: factorial
'''

# 반복적으로 구현한 n!

def factorial_iterative(n):
    result = 1
    # 1부터 n까지의 수를 차례대로 곱하기
    for i in range(1, n+1):
        result *= i
    
    return result

print(factorial_iterative(5))

# 재귀적으로 구현한 n!
def factorial_recursive(n):
    if n <= 1:
        #print(n)
        return 1
    return n * factorial_recursive(n-1)

print(factorial_iterative(5))
print(factorial_recursive(0))