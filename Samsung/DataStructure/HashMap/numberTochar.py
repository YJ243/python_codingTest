'''
2023.10.06 
- <대응되는 수와 문자>
- n개의 문자열이 주어지고, 각각 1부터 n까지 주어진 순서대로 숫자와 매핑
- 이후, 조사할 숫자에 대해서는 대응되는 문자열, 문자열에 대해서는 대응되는 숫자 출력
'''

# 내 풀이
n, m = map(int, input().split())
words = dict()

for i in range(n):
    a = input()
    words[a] = i+1 # key-value 값 저장
    
reverse_words = dict(map(reversed, words.items())) # 숫자에 대응되는 문자열 찾기 위해 HashMap 만들기

for i in range(m):
    k = input()
    if k.isdigit(): # 숫자면
        k = int(k)
        print(reverse_works[k])
    else:
    print(words[k])
    
## 해설
# 변수 선언 및 입력:
n, m = tuple(map(int, input().split()))

# 다음과 같이 입력받으면 첫 번째 값이 0번 index에 저장
words = [input() for _ in range(n)]

string_to_num = dict()

# 각 숫자에 대응되는 문자를 array에,
# 각 문자에 대응되는 숫자를 hashmap에 기록하기
for i in range(n):
    string_to_num[works[i]] = i + 1

for _ in range(m):
    word = input()
    
    # 입력된 값이 숫자일 때에는 array에 저장된 문자를 출력
    if ord(word[0]) >= ord('0') and ord(word[0]) <= ord('9'):
        num = int(word)
        
        # n번에 대응되는 문자열이 n-1번 index에 들어있기 때문에
        print(words[num-1])
    
    # 입력된 값이 문자일 때에는 hashmap에 기록된 대응되는 숫자를 출력
    else:
        print(string_to_num[word])