n, k = map(int, input().split())
result = 0

# N�� K �̻��̶�� K�� ��� ������
while n >= k:
    # N�� K�� ������ �������� �ʴ´ٸ� N���� 1�� ����
    while n % k != 0:
        n -= 1
        result +=1
    # K�� ������
    n //= k
    result += 1

# ���������� ���� ���� ���ؼ� 1�� ����
while n > 1:
    n -= 1
    result += 1
print(result)

################### �� ���� ����
n, k = map(int, input().split())
result = 0

while True:
    # (N == K�� ����������� ��)�� �� ������ 1�� ����
    target = (n // k) * k
    result += (n-target)
    n = target
    
    # N�� K���� ���� �� (�� �̻� ���� �� ���� ��) �ݺ��� Ż��
    if n < k:
        break
    # K�� ������
    result += 1
    n // k

# ���������� ���� ���� ���ؼ� 1�� ����
result += (n-1)
print(result)