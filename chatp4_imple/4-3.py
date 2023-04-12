loc = input()

x = int(loc[1])

y = int(ord(loc[0]))-96

answer=0
dx = [-1,1,-1,1,-2,2,-2,2]
dy = [-2,-2,2,2,-1,-1,1,1]
move_types = ['LU','LD','RU','RD','UL','DL','UR','DR']

for i in range(len(move_types)):
    nx = x+ dx[i]
    ny = y + dy[i]

    if nx < 1 or nx > 8 or ny < 1 or ny > 8:
        continue
    
    answer += 1     

print(answer)
