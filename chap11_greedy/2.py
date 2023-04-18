number = input()

# 첫 번째 문자를 숫자로 변경해서 대입
result = int(number[0])
for i in range(1,len(number)):
    # 두 수 중에서 하나라도 '0' 또는 '1'인 경우, 곱하기보다는 더하기 수행
    if result <=1 or int(number[i]) <= 1:
        result += int(number[i])

    else:
        result *= int(number[i])
        
print(result) 