'''
2023.10.06
- 정수를 저장하는 최대 우선순위 큐, 입력으로 주어지는 명령 처리
'''
## 내 풀이
import heapq
class integer_priorityQueue:
    def __init__(self):
        self.items = []
    
    def push(self, item):
        heapq.heappush(self.items, -item)
    
    def pop(self):
        if self.empty():
            raise Exception("PriorityQueue is empty")
        return -heapq.heappop(self.items)
    
    def size(self):
        return len(self.items)
    
    def empty(self):
        return not self.items


    def top(self):
        if self.empty():
            raise Exception("PriorityQueue is empty")
        return -self.items[0]


n = int(input())
pq = integer_priorityQueue()
for _ in range(n):
    query = input().split()
    #print(query)
    if query[0] == "push":
        #print("hey")
        pq.push(int(query[1]))
    elif query[0] == "pop":
        print(pq.pop())
    elif query[0] == "size":
        print(pq.size())
    elif query[0] == "empty":
        ret = pq.empty()
        if ret == False:
            print(0)
        else:
            print(1)
    elif query[0] == "top":
        print(pq.top())
        
        
# 해설
import heapq

class PriorityQueue:
    def __init__(self):     # 빈 Priority Queue 하나를 생성
        self.items = []
        
    def push(self, item):           # 우선순위 큐에 데이터를 추가
        heapq.heappush(items, -item)
        
    def pop(self):                  # 우선순위 큐에 있는 데이터 중 최댓값에 해당하는 데이터를 반환하고 제거
        if self.empty():
            raise Exception("PriorityQueue is empty")
        return -heapq.heappop(items)
    
    def empty(self):                # 우선순위 큐가 비어있으면 True 반환
        return not self.items
    
    def size(self):                 # 우선순위 큐에 있는 데이터 수를 반환
        return len(self.items)
    
    def top(self):                  # 우선순위 큐에 있는 데이터 중 최댓값에 해당하는 데이터를 제거하지 않고 반환
        if self.empty():
            raise Exception("PriorityQueue is empty")
        return -self.items[0]
    
# 변수 선언 및 입력
n = int(input())
pq = PriorityQueue()

for _ in range(n):
    command = input()
    if command.startswitch("push"):
        x = int(command.split()[1])
        pq.push(x)
        
    elif command == "pop":
        print(pq.pop())
    
    elif command == "size":
        print(pq.size())
    
    elif command == "empty":
        print(1 if pq.empty() else 0)
    else:
        print(pq.top())