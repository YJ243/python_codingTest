n, m = map(int, input().split())
x, y, direction = map(int, input().split())

array = []
for i in range(n):
    array.append(list(map(int, input().split())))

d = [[0]*m for _ in range(n)]
d[x][y]=1
# 북:0 --> 서:3 --> 남:2 --> 동:1
def turn_left():
    global direction
    direction -= 1
    
    if direction == -1:
        direction = 3

answer = 0

# 0:육지, 1: 바다

# 0,1,2,3 --> 북,동,남,서
dx=[-1,0,1,0]
dy=[0,1,0,-1]

move_count = 0
while True:
    turn_left()
    # 가보지 않았고, 육지이면 전진
    nx = x + dx[direction]
    ny = y + dy[direction]
    if d[nx][ny] == 0 and array[nx][ny] == 0:
        d[nx][ny] = 1
        x = nx
        y = ny
        move_count = 0
        answer += 1
        continue
    else :
        move_count += 1
        
    if move_count == 4:
        nx = x - dx[direction]
        ny = y - dx[direction]
        if array[nx][ny] == 1: # 뒤가 바다이면 멈춤
            break
        elif d[nx][ny] == 0: # 뒤가 육지이고 가보지 않았더라면 
            x = nx
            y = ny
            move_count = 0
            answer += 1
                
print(answer)