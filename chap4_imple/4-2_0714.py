n = int(input())

h, m, s = 0, 0, 0

for i in range(n+1): # 시
    if i // 10 == 3 or i % 3 == 0:
        i += 1
    for j in range(60): # 분
        if j // 10 == 3 or j % 3 == 0:
            m += 1
        for k in range(60): # 초
            if k // 10 == 3 or k % 3 == 0:
                s += 1

#answer = i * j * s
print(answer)