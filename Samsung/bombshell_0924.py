import sys
from collections import deque
INF = 10000000
si = sys.stdin.readline

# N, M, K := ��, ��, �� ��
N, M, K = map(int, si().split())

# a := ������ ����
a = [list(map(int, si().split())) for _ in range(N)]

# isAttacked := �̹� �Ͽ� ���ݰ� ������ �־��°�?
isAttacked = [[False for _ in range(M)] for _ in range(N)]

# lastAttack := �������� ������ ���� �����ΰ�?
# ��� ��ž�� ���� 0�� ��� ������ ������ �ִٰ� ����
lastAttack = [[0 for _ in range(M)] for _ in range(N)]

def attack(x, y, power): # (x, y)�� �ִ� ��ž�� power��ŭ�� ������ �޴´�.
    isAttacked[x][y] = True # ���ݿ� �����ߴ�
    a[x][y] = max(0, a[x][y] - power) # ���� ����

def isFinish(): # ���� ���� ������ �����ߴٸ�, true return, O(NM)
    # �μ����� ���� ��ž�� 1���� �ȴٸ� �� ��� ����
    cnt = 0
    for i in range(N):
        for j in range(M):
            if a[i][j] != 0:
                cnt += 1
    return cnt == 1 # �μ����� ���� ��ž(��Ƴ��� ��ž)�� 1���� �Ǹ� �� ��� ����

def select_attacker() -> tuple: # �����ڸ� �����ϴ� �Լ�
    minPower, latestTime, minI, minJ = INF, -1, 0, 0 # ���� ���� ���ݷ�, ���� �ֱ� ���� �ð�, ������ ��
    for sum in range(N+M-2, -1, -1): # sum(��+��)�� �ִ���� �ּұ��� ��ȸ
        for j in range(M-1, -1, -1): # ���� sum�� ���ؼ��� ���� ������ Ž��
            i = sum - j # ���� �տ��� ���� ����
            # ���� ���� �ִ� ��ǥ: (i,j)
            if i < 0 or i >= N: continue # ���ڸ� ����� ��ġ�� ����

            if a[i][j] == 0: 

                continue # �μ��� ��ž�̸� ����
           
            if minPower > a[i][j]: # ���� �ּ� ���ݷº��� �� ������
                # ���� Ž�� ��ǥ�� ���ݷ�, ������ ���ݽð�, ��ǥ �ֱ�
                minPower, latestTime, minI, minJ = a[i][j], lastAttack[i][j], i, j

            elif minPower == a[i][j] and latestTime < lastAttack[i][j]:
                # ���� �ּ� ���ݷ°� ������ �ð��� ��
                # ���� �ֱٿ� ������ ��ž���� ����

                minPower, latestTime, minI, minJ = a[i][j], lastAttack[i][j], i, j

    return minI, minJ


def select_target() -> tuple: # ���� ����� �����ϴ� �Լ� O(NM) <<< O(NM log (NM))
    maxPower, minTime, maxI, maxJ = -1, INF, 0, 0

    for sum in range(N+M-1): # �Ųٷ�, ���� ���� ���� ���� ���� ��ž����
        for j in range(M): # ���� ���� ���� ��ž����
            i = sum - j
            if i < 0 or i >= N: continue


            if maxPower < a[i][j]:

                maxPower, minTime, maxI, maxJ = a[i][j], lastAttack[i][j], i, j

            elif maxPower == a[i][j] and minTime > lastAttack[i][j]:

                maxPower, minTime, maxI, maxJ = a[i][j], lastAttack[i][j], i, j

    return maxI, maxJ


# bfs �Լ�
def tryRaser(atk, tgt) -> bool: # ������ ���� �õ�, �����ϸ� False return, O(NM)
    # visit[x][y] := (x, y)�� ���� �湮 ����
    visit = [[False for _ in range(M)] for _ in range(N)]

    # come[x][y] := (x,y)�� ���κ��� �Դ°�?
    come = [[None for _ in range(M)] for _ in range(N)]

    q = deque()
    visit[atk[0]][atk[1]] = True
    q.append(atk)

    # ��/��/��/�� �켱����
    dirs = ((0,1),(1,0),(0,-1),(-1,0))
    while q:
        x, y = q.popleft()
        for dx, dy in dirs:
            nx, ny = (x + dx + N) % N, (y + dy + M) % M # ��ⷯ �������� ���������� ��� ó��

            if a[nx][ny] == 0: continue
            if visit[nx][ny]: continue

            come[nx][ny] = (x,y) # ���κ��� �Դ��� ����ϱ� (�� �� �ٸ� �߰��ϸ� ������ ����)
            visit[nx][ny] = True
            q.append((nx,ny))
    
    if not visit[tgt[0]][tgt[1]]: # ���� �������� �������� ���ߴٸ�, False return
        return False

    # ������ �ϸ鼭 ����
    x, y = tgt[0], tgt[1] # x, y = tgt
    while x != atk[0] or y != atk[1]:
        # power ���ݷ� ���ϱ�
        power = a[atk[0]][atk[1]] // 2
        if x == tgt[0] and y == tgt[1]:
            power = a[atk[0]][atk[1]]
        # �����ϱ�
        attack(x,y,power)
        # �������ϱ�
        x, y = come[x][y]
    return True
        




# ��ź ���� �Լ�
def bomb(atk, tgt):
    '''
    # Ÿ�ٿ� ���� ���� �Ŀ�
    power = a[atk[0]][atk[1]]
    attack(tgt[0], tgt[1], power)

    dx = [-1,1,0,0,-1,-1,1,1]
    dy = [0,0,-1,1,-1,1,-1,1]
    power = a[atk[0]][atk[1]] // 2
    for i in range(8):
        nx = (tgt[0]+dx[i]+N) % N
        ny = (tgt[1]+dy[i]+N) % N
        if a[nx][ny] == 0: continue
        if nx == atk[0] and ny == atk[1]: continue
        attack(nx,ny,power)
    '''
    for dx in (-1,0,1):
        for dy in (-1,0,1):
            nx, ny = (tgt[0]+dx + N)%N, (tgt[1]+dy+M)%M
            if nx == atk[0] and ny == atk[1]: continue # �����ڸ� �н�
            power = a[atk[0]][atk[1]] // 2 # ���ݷ� ���ϱ�
            if nx == tgt[0] and ny == tgt[1]: power = a[atk[0]][atk[1]]
            # �����ϱ�
            attack(nx,ny,power)


# �ùķ��̼� -> ��Ű�� �� �ϱ�! (�Ｚ�� ������ �˷���� ������ �״�� �ϸ� �ȴ�)

for time in range(1, K+1):
    if isFinish(): # ���� ���� ������ �����ߴٸ�, ���� �������� �ʰ� ����
        break
    
    # 1. ������ ����
    atk = select_attacker()

    # 2. ���� ��� ����
    tgt = select_target()

    # 3. �����ڿ��� �ڵ�ĸ ����
    a[atk[0]][atk[1]] += N+M

    # 4. �����ڿ� ���� "������ ���� ��" ���� ����
    lastAttack[atk[0]][atk[1]] = time

    # 5. ���� ����
    # �� �ϸ��� ������ �޾Ҵ����� ���� �迭 �ʱ�ȭ
    isAttacked = [[False for _ in range(M)] for _ in range(N)]
    isAttacked[atk[0]][atk[1]] = True # ������ ���ݿ� �����ߴ� ǥ��

    if not tryRaser(atk, tgt): # ������ ������ �õ��ϱ�
        bomb(atk, tgt) # ���ݿ� �����ߴٸ� ��ź ����
    # 6. ���� ����
    for i in range(N):
        for j in range(M):
            if not isAttacked[i][j] and a[i][j] != 0: # ���ݿ� �������� ���� ��ž�̶��
                a[i][j] += 1



'''
max_power = 0
for i in range(N):
    for j in range(M):
        if a[i][j] > max_power:
            max_power = a[i][j]
print(max_power)
'''

# �̹� ���� ���� ��ž�� �̴� �Լ��� ����������, ���� �ּ�ó�� �ٽ� �ȱ��ص� ��
res = select_target()
print(a[res[0]][res[1]])
print(a)