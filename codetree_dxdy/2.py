'''
2023.09.26
'''
# ���� ���� �� �Է�
dirs = input()
x, y = 0,0
curr_dir = 3

# ��, ��, ��, �� ������ dx, dy ����
dxs = [1,0,-1,0]
dys = [0,-1,0,1]

# �����̴� ���� ����
for c_dir in dirs:
    # �ݽð���� 90�� ȸ��
    if c_dir == 'L':
        curr_dir = (curr_dir-1+4)%4
    # �ð���� 90�� ȸ��
    elif c_dir == 'R':
        curr_dir = (curr_dir+1)%4
    else:
        x += dxs[curr_dir]
        y += dys[curr_dir]
print(x,y)
