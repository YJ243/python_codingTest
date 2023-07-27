'''
date: 2023.07.26
name: Yejin
title: can't make_answer
'''

n = int(input())
data = list(map(int, input().split()))
data.sort()

target = 1
for x in data:
    # 