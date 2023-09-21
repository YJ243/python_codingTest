'''
date: 2023.09.21
'''
## 내 처음 답

tile = ['0' for _ in range(100000)]
black_cnt = [0 for _ in range(100000)]
white_cnt = [0 for _ in range(100000)]

cur = 50000
n = int(input())
for i in range(n):
    x, d = input().split()
    x = int(x)
    
    if d == 'L':
        for i in range(x):
            tile[cur] = 'W'
            black_cnt[cur] += 1
            cur -= 1
        cur += 1
    else:
        for i in range(x):
            tile[cur] = 'B'
            white_cnt[cur] += 1
            cur += 1
        cur -= 1

result_gray = 0
result_black = 0
result_white = 0

for i in range(len(tile)):
    if tile[i] != '0':
        if black_cnt[i] >= 2 and white_cnt[i] >= 2:
            result_gray += 1
        else:
            if tile[i] == 'B':
                result_black += 1
            else:
                result_white += 1

print(result_white, result_black, result_gray)

'''해설'''

MAX_K = 100000
# 변수 선언 및 입력:
n = int(input())
a = [0] * (2*MAX_K + 1)
cnt_b = [0]*(2*MAX_K+1)
cnt_w = [0]*(2*MAX_K + 1)

b, w, g = 0, 0, 0

cur = MAX_K
for _ in range(n):
    x, c = tuple(input().split())
    x = int(X)
    
    if c == 'L':
        # x칸 왼쪽으로 칠함
        while x > 0:
            a[cur] = 1
            cur_w[cur]+=1
            x -= 1
            
            if x:
                cur -= 1
    else:
        # x칸 오른쪽으로 칠함
        while x > 0:
            a[cur] = 2
            cnt_b[cur] += 1
            x -= 1
            
            if x:
                cur += 1

for i in range(2*MAX_K + 1):
    # 검은색과 흰색으로 두 번 이상 칠해진 타일은 회색
    if cnt_b[i] >= 2 and cnt_w[i] >= 2:
        g += 1
    # 그렇지 않으면 현재 칠해진 색깔이 곧 타일의 색깔
    elif a[i] == 1:
        w += 1
    elif a[i] == 2:
        b += 1

# 정답 출력
print(w, b, g)