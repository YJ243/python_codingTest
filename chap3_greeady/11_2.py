'''
date: 2023.07.25
name: Yejin
title: multiplex or plus
'''
number = input()

a = []
for i in str(number):
    a.append(i)

a_int = list(map(int, a))
answer = 0
for i in a_int:
    if i == 0 or answer == 0 or i == 1 or answer == 1:
        answer += i
    
    else:
        answer *= i
print(answer)
    
        