'''
date: 2023.07.26
name: Yejin
title: 1st answer
'''

def solution(food_times, k):
    answer = 0
    turn = 0
    while k != 0: # ��Ʈ��ũ ��ְ� �߻��ϱ� ������
        if turn == len(food_times): # ���� ���� �Ѿ��
            turn = 0
        if food_times[turn] == 0: # ���� ���� �ð��� 0
            count = 0
            while food_times[turn] != 0: # �����ִ� ���� ã��
                turn %= len(food_times)��
                if count == len(food_times): # ��� ���Ŀ� �����ִ� �ð��� 0�̸�
                    return -1
                turn += 1
                count += 1
        else: # ���� �ð��� ������
            food_times[turn] -= 1 # �ð� 1 ����
            turn += 1 # �������� �Ѿ��
        k -= 1
    
    if turn == len(food_times): #�Ѿ�� �����ٸ�
        answer = 0
    else:
        answer = turn
        
    return answer