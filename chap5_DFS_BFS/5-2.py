'''
date: 2023.09.04
name: Yejin
title: queue
'''

from collections import deque

# queue 구현을 위해 deque 라이브러리 사용
queue = deque()

queue.append(5)
queue.append(2)
queue.append(3)
queue.append(7)
queue.popleft()
queue.append(1)
queue.append(4)
queue.popleft()

print(queue) # 먼저 들어온 순서대로 출력
# 다음 출력을 위해 역순으로 바꾸기
queue.reverse()
print(queue)

# deque 객체를 리스트 자료형으로 변경하려면 list() 이용
print(list(queue))