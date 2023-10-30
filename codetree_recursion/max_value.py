'''
2023.10.29
https://www.codetree.ai/missions/5/problems/maximum-value-with-recursive-function?&utm_source=clipboard&utm_medium=text
n개의 원소 중 최댓값을 구하는 프로그램을 작성해보세요. 
단, 재귀함수를 이용하여 문제를 해결해주세요.
'''
# 내 풀이
n = int(input())
a = list(map(int, input().split()))
cur_max = 0
def get_max(i): # i번째까지 인덱스를 봤을 때 최댓값을 반환
    global cur_max
    if i < 0:
        return
    if cur_max < a[i]:
        cur_max = a[i]
    return get_max(i-1)

get_max(n-1)
print(cur_max)

'''
해설
'''
# 변수 선언 및 입력
n = int(input())
arr = list(map(int, input().split()))

# a번째까지 인덱스의 숫자 중에 가장 큰 값을 반환
def max_value(a):
    if a == 0:
        return arr[0]
    return max(max_value(a-1), arr[a])

print(max_value(n-1))