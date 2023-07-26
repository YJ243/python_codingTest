# 변수 선언 및 입력
n, k = tuple(map(int, input().split()))
coins = [int(input()) for _ in range(n)]

ans = 0

# 큰 동전부터 이용
for coin in coins[::-1]:
    ans += k // coin
    k %= coin

print(ans)