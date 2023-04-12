# N, M�� �������� �����Ͽ� �Է¹ޱ�
n, m = map(int, input().split())

# �湮�� ��ġ�� �����ϱ� ���� ���� �����Ͽ� 0���� �ʱ�ȭ
d[n][m] = [[m]*0 for _ in range(n)]
# ���� ĳ������ X ��ǥ, Y ��ǥ, ������ �Է¹ޱ�
x, y, direction = map(int, input().split())
d[x][y] = 1 # ���� ��ǥ �湮 ó��

# ��ü �� ������ �Է¹ޱ�
array = []

for i in range(n):
    array.append(list(map(int, input().split()))) 
    
# ��, ��, ��, �� ���� ����
dx = [-1, 0, 1, 0]
dy = [0, 1, 0, -1]

# �������� ȸ��
def turn_left():
    global direction
    direction -= 1
    
    if direction == -1
        direction = 3

# �ùķ��̼� ����    
count = 1
turn_time = 0

while True:
    turn_left()
    nx = x + dx[direction]
    ny = y + dy[direction]
    
    # ȸ���� ���� ���鿡 ������ ���� ĭ�� �����ϴ� ���
    if array[nx][ny] == 0 and d[nx][ny] == 0:
        x = nx
        y = ny
        count += 1
        turn_time = 0
        continue
    else:
        turn_time += 1
    
    
    if turn_time == 4:
        # �ڷ� ������
        nx = x - dx[direction]
        ny = y - dy[direction]
        # �ڷ� �� �� �ִٸ�
        if d[nx][ny] == 0:
            x = nx
            y = ny
        # �ڰ� ���� �ִٸ�
        else:
            break
        turn_time = 0
print(count)
            