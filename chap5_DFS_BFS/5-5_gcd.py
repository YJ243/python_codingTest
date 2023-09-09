'''
date: 2023.09.09
name: Yejin
title: recursive function_gcd
'''

def gcd(a, b):
    if a % b == 0:
        return b
    else:
        return gcd(b, a % b)
    
print(gcd(192,162))