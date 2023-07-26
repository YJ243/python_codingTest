data = input()
count0 = 0 # 전부 0으로 바꾸는 경우
count1 = 0 # 전부 1으로 바꾸는 경우

# 첫 번째 원소에 대해서 처리
if data[0] == '1':
    count0 += 1 # 0으로 바꿈
else: # 0이면
    count1 += 1 # 1로 바꿈
    
# 두 번째 원소부터 모든 원소를 확인하며
for i in range(len(data)-1):
    print(i)
