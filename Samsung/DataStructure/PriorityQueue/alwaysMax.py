'''
2023.10.06
- n개의 숫자가 주어졌을 때 그 중 가장 큰 숫자를 골라 1씩 빼는 작업을 m번 반복
- 이를 반복한 이후 남아있는 숫자들 중 최댓값을 구하는 프로그램을 작성해보세요
'''

import heapq

# 변수 선언 및 입력:
n, m = tuple(map(int, input().split()))
arr = list(map(int, input().split()))
pq = []

# priority queue에 숫자들을 넣어줌
# 최댓값을 구해야 하므로 -를 붙여서 넣어주기

for elem in arr:
    heapq.heappush(pq, -elem)
    
# m번에 걸쳐서 최댓값을 찾아 1씩 빼주는 것을 반복
for _ in range(m):
    # 최댓값을 찾고 제거
    max_val = -heapq.heappop(pq)
    # 1뺀 값을 다시 넣어주기
    # -를 붙여서 넣어줘야 함에 유의
    heapq.heappush(pq, -(max_val-1))
print(-heapq.heappop(pq))