'''
date: 2023.08.18
name: Yejin
title: stack
'''

stack = []
stack.append(5)
stack.append(2)
stack.append(3)
stack.append(7)
stack.pop()
stack.append(1)
stack.append(4)
stack.pop()

print(stack) # 최 하단 원소부터 출력
print(stack[::-1])
