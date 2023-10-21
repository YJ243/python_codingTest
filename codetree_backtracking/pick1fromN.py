'''
2023.10.09 BackTracking
'''

K, N = map(int, input().split())    # K:= K이하의 수, N:= 자리수

ans = []

def print_ans(): # 출력 함수
    for i in range(N):
        print(ans[i], end=' ')
    print()


def choose(cur_num): # cur_num 자리수에 들어갈 숫자를 선택하는 함수
    if cur_num == N+1:
        print_ans()
        return
    else:
        for n in range(1,K+1):
            ans.append(n)
            choose(cur_num+1)
            ans.pop()

choose(1)

'''
- 백트래킹을 활용해 가능한 모든 '중복 순열'탐색
- 특정 시점에 뽑힌 숫자의 개수를 인자로 설정, n개의 숫자를 모두 뽑았을 때마다 출력
- 사전순으로 앞선 것부터 순서쌍을 만들어지게 하기 위해 가장 작은 숫자부터 순회
'''
##  해설
# 변수 선언 및 입력
k, n = tuple(map(int, input().split()))
selected_nums = []

# 선택된 원소들을 출력해줌
def print_permutation():
    for num in selected_nums:
        print(num, end=" ")
    print()
    
def find_permutations(cnt): # 지금까지 cnt개의 숫자를 뽑았을 때 그 다음 어떤 숫자를 뽑을 지 선택하는 함수
    # n개를 모두 뽑은 경우 답을 출력
    
    if cnt == n:
        print_permutation()
        return
    
    # 1부터 k까지의 각 숫자가 뽑혔을 때의 경우를 탐색
    for i in range(1, k+1):
        selected_nums.append(i)
        find_permutations(cnt+1)
        selected_nums.pop()
        
find_permutatinos(0)