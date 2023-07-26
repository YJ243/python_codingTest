'''
date: 2023.07.13
name: Yejin
title: 상하좌우

'''

n = int(input())
plans = input().split()
answer = [1,1]
# L, R, U, D
nx = [0, 0, -1, 1]
ny = [-1, 1, 0, 0]
for plan in plans:
    if plan == 'L':
        dx = answer[0]+nx[0]
        dy = answer[1]+ny[0]
    elif plan == 'R':
        dx = answer[0]+nx[1]
        dy = answer[1]+ny[1]
    
    elif plan == 'U':
        dx = answer[0]+nx[2]
        dy = answer[1]+ny[2]
    else:
        dx = answer[0]+nx[3]
        dy = answer[1]+ny[3]
        

    if dx>=1 and dx <= n and dy >=1 and dy<=n:
        answer[0]=dx
        answer[1]=dy

print(answer[0], answer[1])
        