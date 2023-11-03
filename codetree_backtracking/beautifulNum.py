'''
2023.10.09 아름다운 수
- 연속된 수를 판단하는 로직을 만들지 못함
'''
# 초기 답

n = int(input())

cnt = [0 for _ in range(5)] # 1 ~ 4이하의 숫자 개수를 담는 배열
num = [] # 현재까지 만든 숫자
result = 0

def check_num(): # n자리 숫자가 아름다운 숫자인지 확인하는 함수
    no_flag = 0 # 아름다운 숫자인지 나타내는 flag
    for n in num: # 현재까지 만든 숫자에 대해서 하나씩 탐색하는데,
        if n == 1:
            continue
        elif n == 2:
            cnt[2] += 1
            # 
        elif n == 3:
            cnt[3] += 1
        elif n == 4:
            cnt[4] += 1

    for i in range(1, 5): # 1,2,3,4 숫자에 대해서 확인하는데
        if cnt[i] == 0: continue
        if cnt[i] % i != 0: # 개수를 1/2/3/4로 나눈 것이 0이 아니라면, 묶음이 반복되지 않은 것
            no_flag = 1 # 
    if no_flag: return False
    else: return True


# n개의 숫자에 대해서 백트래킹 하기
def beautyNum(number): # 아름다운 수의 number 자리수 만드는 함수
    global result
    
    # 재귀함수니까 종료조건
    if number == n+1: # 만약 자리수를 넘어가면
        if check_num(): # 아름다운 수인지 확인하고, 만약 아름다운 수이면
            result += 1 # 아름다운 수 개수 증가
        return

    for i in range(1,5):
        num.append(i)
        beautyNum(number+1)
        val=num.pop()



beautyNum(1)
print(result)

# 수정한 답
n = int(input())
number = []
result = 0

def verity_beautiful(): # 현재 N자리 수가 아름다운 수인지 확인하는 함수
    idx = 0     # number 배열 확인할 인덱스
    while idx < n: 
        # 1. number의 idx 자리 숫자만큼 반복되기 전에 자릿수가 끝나는가?
        # 만약 연속하여 해당 숫자만큼 나올 수 없다면 아름다운 수가 아님
        if idx + number[idx] -1 >= n: # ex) n-1번째 수가 2인데, 그대로 끝나면
            return False
        
        # 2. 그 다음 연속하여 해당 숫자만큼 같은 숫자가 있는지 확인하기
        # 하나라도 다른 숫자가 있다면 아름다운 수가 아님
        for j in range(idx, idx + number[idx]):
            if number[idx] != number[j]:
                return False
        idx += number[idx]
    return True
        
def make_beautiful(num): # 아름다운 수의 number 자리수를 만드는 함수
    global result
    
    if num == n+1: #만약 만드려는 자리수를 초과하였다면
        if verify_beautiful(): # 현재 수가 아름다운 수라면
            result += 1     # 개수 하나 추가하기
        return      # 종료

    for i in range(1,5):    # 1이상 4이하의 숫자 추가
        number.append(i)    # num 자리에 i 숫자 추가
        make_beautiful(num+1)   # num+1 자리수 만들러 가기
        number.pop()            # number 수 빼기

make_beautiful(1)
print(result)

'''
2023.11.02
답을 맞췄으나 코드가 너무 비효율적
'''
n = int(input())
a = []
ans = 0
def verify_beauty():    # N자리 숫자가 아름다운 수인지 확인하는 함수
    global ans
    cnt2, cnt3, cnt4 = 0,0,0
    for number in a:
        if number == 1:
            if cnt2 % 2 != 0:
                return
            if cnt3 %3 != 0:
                return
            if cnt4%4 != 0:
                return
        elif number == 2:
            cnt2 += 1
            if cnt3 %3 != 0:
                return
            if cnt4%4 != 0:
                return
            
        elif number == 3:
            cnt3 += 1
            if cnt2 %2 != 0:
                return
            if cnt4%4 != 0:
                return
        else:
            cnt4 += 1
            if cnt2 %2 != 0:
                return
            if cnt3 %3 != 0:
                return

    if cnt2%2 != 0 or cnt3 %3 != 0 or cnt4%4 != 0: return

    ans += 1

def make_beauty(num):   # num번째 숫자를 만드는 함수
    if num == n:
        verify_beauty()
        return
    
    for i in range(1,5):
        a.append(i)
        make_beauty(num+1)
        a.pop()


make_beauty(0)
print(ans)


