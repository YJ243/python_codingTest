n = 3
answer = []

def print_answer():
    for i in range(len(answer)):
        print(answer[i], end=' ')
    print()

def choose(cur_num):    # cur_num 위치에 들어갈 숫자 결정
    if cur_num == n+1:
        print_answer()
        return
    
    for i in range(2):
        answer.append(i)
        choose(cur_num+1)
        answer.pop()
    return

choose(1)