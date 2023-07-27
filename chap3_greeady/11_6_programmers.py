'''
date: 2023.07.26
name: Yejin
title: 1st answer
'''

def solution(food_times, k):
    answer = 0
    turn = 0
    while k != 0: # 네트워크 장애가 발생하기 전까지
        if turn == len(food_times): # 음식 개수 넘어가면
            turn = 0
        if food_times[turn] == 0: # 현재 남은 시간이 0
            count = 0
            while food_times[turn] != 0: # 남아있는 음식 찾기
                turn %= len(food_times)ㅁ
                if count == len(food_times): # 모든 음식에 남아있는 시간이 0이면
                    return -1
                turn += 1
                count += 1
        else: # 남은 시간이 있으면
            food_times[turn] -= 1 # 시간 1 빼기
            turn += 1 # 다음으로 넘어가기
        k -= 1
    
    if turn == len(food_times): #넘어가고 끝났다면
        answer = 0
    else:
        answer = turn
        
    return answer