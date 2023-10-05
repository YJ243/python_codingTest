'''
2023.10.04
'''

## 내 풀이
n, t = map(int, input().split()) # n: 격자 크기, t: 시간
r,c,d = input().split() # (r,c)에 구슬, d 방향
r = int(r)
c = int(c)

dxs = [0,1,-1,0]
dys = [1,0,0,-1]

mapping={
    'R':0,
    'D':1,
    'U':2,
    'L':3
}

cur_d = mapping[d]
#print(dxs[cur_d],dys[cur_d])
for i in range(1,t+1):
    # d 방향대로 움직이기
    # 만약 현재 있는 곳으로 갔을 때 벽이면
    nx, ny = r + dxs[cur_d], c + dys[cur_d]
    #print(nx,ny)
    if nx <= 0 or nx > n or ny <= 0 or ny > n: # 만약 벽에 부딪히면
        cur_d = 3-cur_d
        continue
    else: # 만약 갈수 있다면
        r, c = nx, ny

print(r,c)

## 해설

# 변수 선언 및 입력
n, t = tuple(map(int, input().split()))
x, y, c_dir = tuple(input().split())

# 각 알파벳 별 방향 번호를 설정
mapper = {
    'R': 0,
    'D': 1,
    'U': 2,
    'L': 3
}

x, y, move_dir = int(x)-1, int(y)-1, mapper[c_dir]

dxs = [0,1,-1,0]
dys = [1,0,0,-1]


def in_range(x,y):
    return 0 <= x and x < n and 0 <= y and y < n

# simulation 진행
for _ in range(t):
    nx, ny = x + dxs[move_dir], y + dys[move_dir]
    # 범우 안에 들어온다면 그대로 진행
    if in_range(nx,ny):
        x, y = nx, ny
        # 벽에 부딪힌다면 방향을 바꿔줌
    else:
        move_dir = 3-move_dir
print(x+1, y+1)