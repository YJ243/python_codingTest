n = int(input())

answer = 0
# 시에서 3 몇 개 있는지 확인
for i in range(0, n+1):
    for j in range(0, 60):
        for k in range(0, 60):
            # 매 시각 안에 3이 포함되어 있으면 카운트 증가
            if '3' in str(i) + str(j) + str(k):
                answer += 1
# 분에서 3 몇 개 있는지 확인

print(answer)

# 초에서 3 몇 개 있는지 확인