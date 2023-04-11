# 현재 나이트의 위치 입력받기
loc = input()
x = int(loc[1])
y = int(ord(loc[0]))-96

answer=0
# 나이트가 이동할 수 있는 8가지 방향 정의
dx = [-1,1,-1,1,-2,2,-2,2]
dy = [-2,-2,2,2,-1,-1,1,1]
#move_types = ['LU','LD','RU','RD','UL','DL','UR','DR']

for i in range(len(dx)):
    # 이동하고자 하는 위치 확인
    nx = x+ dx[i]
    ny = y + dy[i]

    # 해당 위치로 이동이 가능하지 않다면 통과
    if nx < 1 or nx > 8 or ny < 1 or ny > 8:
        continue
    # 해당 위치로 이동이 가능하면 카운트 증가
    answer += 1     

print(answer)
