def recursive_function():
    if i == 100:
        return
    print(i, '��° ��� �Լ�����', i+1, '��° ��� �Լ��� ȣ��')
    recursive_function(i+1)
    print(i, '��° ��� �Լ��� �����մϴ�.')

recursive_function(1)