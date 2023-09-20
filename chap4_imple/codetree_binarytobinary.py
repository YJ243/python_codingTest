'''
2023.09.20
'''
#### 내답안
a, b = map(int, input().split())
n = list(map(int, input()))

# a진수 n을 10진수로 바꾸기
num = 0
for i in range(len(n)):
    num = num*a + n[i]

# 10진수 num을 b진수로 변환 
result = []
while True:
    if num < b:
        result.append(num)
        break
    result.append(num%b)
    num = num // b

for digit in result[::-1]:
    print(digit, end="")


#### 해설

# 변수 선언 및 입력:
a, b = tuple(map(int, input().split()))
n = input()

digits = []

# 십진수로 변환 
num = 0
for ch in n:
    num = num*a + (ord(ch) - ord('0'))
    
# b진수로 변환
while True:
    if num < b:
        digits.append(num)
        break
    digits.append(num%b)
    num //= b
    
# 진수 배열을 뒤집어 b진수 출력
for digit in digits[::-1]:
    print(digit, end="")