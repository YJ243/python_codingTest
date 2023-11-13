'''
2023.11.03
파도반 수열
P(N) = P(N-2)+P(N-3)
'''
n = int(input())
memo = [-1 for _ in range(n+1)]

def padovan(n):
    if memo[n] != -1:
        return memo[n]
    if n <= 3:
        memo[n] = 1
    else:
        memo[n] = padovan(n-2) + padovan(n-3)
    return memo[n]
