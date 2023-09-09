'''
date: 2023.09.04/2023.09.09
name: Yejin
title: recursive condition
'''

'''
- 점화식: 재귀함수에서 어떤 함수를 호출해야 하는지 힌트를 줌
- 초깃값: 종료조건에 대한 정보 줌
'''
def recursive_function(i):
    # 100번째 출력했을 때 종료되도록 조건 명시
    if i == 100:
        return
    print(i, '번째 재귀 함수에서', i+1, '번째 재귀 함수를 호출합니다')
    recursive_function(i+1)
    print(i, '번째 재귀 함수를 종료합니다')
    
recursive_function(1)