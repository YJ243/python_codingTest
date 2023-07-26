n = int(input())
numbers = list(map(int, input().split()))
answers=[0]
answer = 0
tmp = 0
if max(numbers) < 0:
    print(max(numbers))
else:
    for number in numbers:
        if tmp + number > 0:
            tmp += number
            if max(answers) < tmp:
                answers.append(tmp) # 클 때에만 업데이트
        else:
            tmp = 0
    print(max(answers))
    
### 다른 사람 풀이 ###
### #1
import sys

N = int(input())
arr = list(map(int, sys.stdin.readline().split()))

temp = 0
ans = float('-inf') # 음의 무한대
for idx in range(N):
    if temp < 0 :
        temp = arr[idx]
    else:
        temp += arr[idx]
    ans = max(ans, temp)

print(ans)

### #2
import sys
N = int(sys.stdin.readline())
arr = list(map(sys.stdin.readline().split()))
result = sum_val = arr[0]

for num in arr[1:]:
    if sum_val < 0:
        sum_val = 0
    sum_val += num
    result = max(sum_val, result)

print(result)

### #3
import sys
n = int(input())
arr = list(map(int, input().split()))
ans = -sys.maxsize
sum_num = 0

for i in range(n):
    if sum_num < 0:
        sum_num = arr[i]
    else:
        sum_num += arr[i]
    ans = max(ans, sum_num)
print(ans)