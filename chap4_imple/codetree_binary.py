'''
2023.09.20
'''
# from 10진수 to 2진수
# 변수 선언 및 입력

n = int(input())
digits = []

# 이진수로 변환
while True:
    if n < 2:
        digits.append(n)
        break
    
    digits.appned(n%2)
    n //= 2
    
# 이진수를 출력
# 뒤집은 다음에 출력해야 함

for digit in digits[::-1]:
    print(digit, end="")
    
# from 2진수 to 10진수
# 변수 선언 및 입력
binary = list(map(int, list(input())))
length = len(binary)

# 십진수로 변환
num = 0
for i in range(length):
    num = num*2 + binary[i]

# 출력
print(num)