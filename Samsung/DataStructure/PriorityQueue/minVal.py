'''
2023.10.07
- 비어있는 배열에 연산
- 입력이 자연수 x라면, 배열에 자연수 x를 넣습니다.
- 입력이 0이라면 배열에서 가장 작은 값을 출력하고 그 값을 배열에서 제거합니다.

'''

# 내 풀이
import heapq
pq = []
n = int(input())

for _ in range(n):
    x = int(input())
    if x > 0:
        heapq.heappush(pq, x)
    else:
        if len(pq) == 0:
            print(0)
        else:
            print(heapq.heappop(pq))


# 해설
import heapq

# 변수 선언 및 입력:
n = int(input())
arr =[
    int(input())
    for _ in range(n)
]

pq = []

# priority queue를 이용하여 진행
for elem in arr:
    # 0이 아니라면, 해당 숫자를 priority queue에 넣어줌 
    if elem != 0:
        heapq.heappush(pq, elem)
    
    # 0이라면 가장 작은 값을 출력하고 배열에서 제거
    else:
        # 배열이 비어있다면 0을 출력
        if not pq:
            print(0)
        else:
            # 그렇지 않다면 최솟값을 제거
            print(heapq.heappop(pq))