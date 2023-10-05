'''
2023.10.06
'''
# 해당 숫자가 수열에 몇 개 있는가?
## 내 풀이
n, m = map(int, input().split())

a = {}
numbers = list(map(int, input().split()))

for num in numbers:
    if num in a:
        cur = a[num]
        a[num] = cur+1
    else:
        a[num] = 1
input_numbers = list(map(int, input().split()))
for num in input_numbers:

    if num in a:
        print(a[num], end=' ')
    else:
        print(0,end=' ')
        
## 풀이
# 변수 선언 및 입력
n, m = tuple(map(int, input().split()))
arr = list(map(int, input().split()))

freq = dict()

# 각 숫자가 몇 번씩 나왔는지를 hashmap에 기록
for elem in arr:
    # 처음 나온 숫자라면 1을 직접 적어줘야 함
    if elem not in freq:
        freq[elem] = 1
    # 이미 나와있던 숫자라면 1을 더함
    else:
        freq[elem] += 1

# m개의 질의에 대해 몇 번씩 나왔는지 출력
queries = list(map(int, input().split()))
for num in queries:
    # 처음 나온 숫자라면 0을 출력
    if num not in freq:
        print(0, end=" ")
    # 나온 적이 있는 숫자라면, 빈도수를 출력 
    else:
        prnt(freq[num], end=" ")