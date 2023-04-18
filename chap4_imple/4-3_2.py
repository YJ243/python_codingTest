# 현재 나이트의 위치 입력받기
input_data = input()
row = int(input_data[1])
column = int(ord(input_data[0])) - int(ord('a')) + 1

# 나이트가 이동할 수 있는 8가지 방향 정의
steps = [(1,2),(1,-2),(-1,2),(-1,-2),(2,1),(-2,1),(2,-1),(-2,-1)]

# 8가지 방향에 대하여 각 위치로 이동이 가능한지 확인
answer = 0
for step in steps:
    nx = row + step[0]
    ny = column + step[1]
    
    if nx >= 1 and nx <= 8 and ny >= 1 and ny <= 8:
        answer += 1

print(answer)