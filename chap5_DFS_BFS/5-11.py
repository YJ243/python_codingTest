from collections import deque

# n, m을 공백으로 구분하여 입력받기
n, m = map(int, input().split())

# 2차원 리스트의 맵 정보 입력받기
array = []

for i in range(n):
    array.append(list(map(int, input())))

# 이동할 네 방향 정의(상,하,좌,우)
dx = [-1,1,0,0]
dy = [0,0,-1,1]
    
# bfs 소스코드 구현
def bfs(x,y):
    # 큐 구현을 위해 deque 라이브러리 사용
    queue = deque()
    queue.append((x,y))
    
    # 큐가 빌 때까지 반복
    while queue:
        x, y = queue.popleft()
        # 현재 위치에서 네 방향으로의 위치 확인
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            # 미로 찾기 공간을 벗어난 경우 무시
            if nx <= -1 or nx >= n or ny <= -1 or ny >= m:
                continue
            # 벽인 경우 무시
            if array[nx][ny] == 0:
                continue
            # 해당 노드를 처음 방문하는 경우에만 최단 거리 기록
            if array[nx][ny] == 1:
                array[nx][ny] = array[x][y]+1
                queue.append((nx,ny))

bfs(0,0)     
for i in range(n):
    print(array[i])  
print(array[n-1][m-1])
            
    
    