# N�� �Է¹ޱ�
n = int(input())
plan = input().split()

x, y = 1, 1

# L R U D
dx = [0, 0, -1, 1]
dy = [-1, 1, 0, 0]
move_types = ['L','R','U','D']

# �̵� ��ȹ�� �ϳ��� Ȯ��
for p in plan:
    # �̵� �� ��ǥ ���ϱ�   
    for i in range(len(move_types)):
        if p == move_types[i]:
            nx = x + dx[i]
            ny = y + dy[i]
            
            # ������ ����� ��� ����
            if nx < 1 or nx > n or ny < 1 or ny > n:
                break
            # �̵� ����
            x = nx
            y = ny

print(x, y)