# N, M, K�� �������� �����Ͽ� �Է¹ޱ�
n, m, k = map(int, input().split())
# N ���� ���� �������� �����Ͽ� �Է¹ޱ�
data = list(map(int, input().split()))

data.sort() # �Է¹��� ���� �����ϱ�
first = data[n-1] # ���� ū ��
second = data[n-2] # �� ��°�� ū ��

result = 0

while True:
    for i in range(k): # ���� ū ���� k�� ���ϱ�
        if m == 0: # m�� 0�̶�� �ݺ��� Ż��
            break
        result += first
        m -= 1 # ���� ������ 1�� ����
        
    if m == 0: # m�� 0�̶�� �ݺ��� Ż��
        break
    reuslt += second # �� ��°�� ū ���� �� �� ���ϱ�
    m -= 1 # ���� ������ 1�� ����

print(result) # ���� ��� ���

###############################################3
#### �ݺ��Ǵ� ������ ���ϱ� ####
# N, M, K�� �������� �����Ͽ� �Է¹ޱ�
n, m, k = map(int, input().split())
# n ���� ���� �������� �����Ͽ� �Է¹ޱ�
data = list(map(int, input().split()))

data.sort() # �Է¹��� �� ����
first = data[n-1] # ���� ū ��
second = data[n-2] # �� ��°�� ū ��

# ���� ū ���� �������� Ƚ�� ���
count = int(m/(k+1)) * k
count += m % (k+1)

result = 0
result += (count) * first # ù ��°�� ū �� ���ϱ�
result += (m-count) * second # �� ��°�� ū �� ���ϱ�

print(result)
