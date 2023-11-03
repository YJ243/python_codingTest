'''
2023.11.03
'''
def fibo(n):
    if memo[n] != -1:       # 이미 n번재 값을 구해본 적이 있다면
        return memo[n]      # memo에 적혀있는 값을 반환
    if n <= 2:              # n이 2 이하의 경우는 종료 조건이므로 
        memo[n] = 1         # 해당하는 숫자를 memo에 넣어주기
    else:
        memo[n] = fibo(n-1)+fibo(n-2)   # 점화식을 이용해 답을 구한 뒤, 해당 값을 memo에 저장
    return memo[n]          # memo 값을 반환

# => O(n)만에 올바른 답을 구할 수 있음, 중복하여 탐색하는 경우가 아예 사라졌기 때문
# => 메모이제이션(Memoization)