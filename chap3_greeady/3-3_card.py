n, m = map(int, input().split())
min_num = []
for i in range(n):
    data = list(map(int, input().split()))
    data.sort()
    min_num.append(data[0])

#print(min_num)

min_num.sort(reverse=True)
print(min_num[0])

###### min() 함수를 이용하는 답안
n, m = map(int, input().split())
# 한 줄씩 입력받아 확인
for i in range(n):
    data = list(map(int, input().split()))
    # 현재 줄에서 '가장 작은 수' 찾기
    min_value = min(data)
    # '가장 작은 수'들 중에서 가장 큰 수 찾기
    result = max(result, min_value)
print(result) # 최종 답안 출력