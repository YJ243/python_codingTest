'''
# priority queue: 내부적으로 min heap 이용
# 만약 이 최소 힙을 최대 힙처럼 사용하려면
# 우선순위에 해당하는 값에 음수 부호를 붙여서 넣었다가, 
# 이후에 다시 음수 부호를 붙여서 원래의 값으로 되돌리기 
'''

import heapq

class PriorityQueue:
    def __init__(self):             # 빈 Priority Queue 하나를 생성
        self.items = []
    
    def push(self, item):           # 우선순위 큐에 데이터를 추가
        heapq.heappush(self.items, -item)
    
    def empty(self):                # 우선순위 큐가 비어있으면 True를 반환
        return not self.items
    
    def size(self):                 # 우선순위 큐에 있는 데이터 수를 반환
        return len(self.items)
    
    def pop(self):                  # 우선순위 큐에 있는 데이터 중 최댓값에 해당하는 데이터를 제거하고 반환
        if self.empty():
            raise Exception("PriorityQueue is empty")
        
        return -heapq.heappop(self.items)
    
    def top(self):                  # 우선순위 큐에 있는 데이터 중 최댓값에 해당하는 데이터를 제거하지 않고 반환
        if self.empty()
            raise Exception("PriorityQueue is empty")
    
        return -self.items[0]

pq = PriorityQueue()