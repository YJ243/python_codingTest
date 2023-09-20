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