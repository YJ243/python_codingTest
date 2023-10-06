'''
2023.10.07

- 2차 평면 위에 서로 다른 위치에 놓여있는 n개의 점
- 이때 원점에서 가장 가까운 점을 하나 골라, 해당 점의 x, y 값에 2씩 더해주는 작업을 m번 반복
- 이를 전부 반복한 이후 원점에 가장 가까이 있는 점을 출력하기
- 원점과 특정 점 (x, y)과의 거리는 ∣x∣+∣y∣
- 만약 원점과의 거리차 최소인 점이 여러 개 있다면 x값이 가장 작은 점, 그 다음으로 y값이 가장 작은 점
'''

# 내 풀이
import heapq

pq = []

n, m = map(int,input().split())
for _ in range(n):
    x, y = map(int, input().split())
    heapq.heappush(pq, ((abs(x)+abs(y)), x, y))

for _ in range(m):
    _, x, y = heapq.heappop(pq)
    x, y = x + 2, y + 2
    heapq.heappush(pq, ((abs(x)+abs(y)), x, y))
_, x, y = heapq.heappop(pq)
print(x, y)


# 해설
import heapq

# 변수 선언 및 입력:
n, m = tuple(map(int, input().split()))
points = [
    tuple(map(int, input().split()))
    for _ in range(n)
]

pq = []

# priority queue에 x+y, x, y 순으로 우선순위가 되도록 하기
for x, y in points:
    heapq.heappush(pq, (x+y, x, y))
    

# m번에 걸쳐서 가장 가까운 점을 잡아서 2씩 더해주기
for _ in range(m):
    _, x, y = heapq.heappop(pq)
    
    # 그 다음 위치를 추가하기
    x, y = x+2, y+2
    heapq.heappush(pq, (x+y, x, y))

_, last_x, last_y = heapq.heappop(pq)
print(last_x, last_y)