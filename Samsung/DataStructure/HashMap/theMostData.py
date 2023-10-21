'''
2023.10.06 
알파벳 소문자로 이루어진 문자열들이 중복을 허용하여 입력되었을때, 
최대로 등장한 문자열의 등장 횟수를 출력하는 프로그램
'''

# 내 풀이
n = int(input())

string_cnt = {}
for i in range(n):
    a = input()

    # 만약 처음 입력된 것이라면
    if a not in string_cnt:
        string_cnt[a] = 1

    # 이미 hashmap에 있다면
    else:
        string_cnt[a] += 1

# 가장 많이 입력된 데이터가 등장한 횟수 출력
result = 0
for _, val in enumerate(string_cnt):
    if result < string_cnt[val]:
        result = string_cnt[val]
print(result)


## 풀이
# 변수 선언 및 입력:
n = int(input())
words = [input() for _ in range(n)]
freq = dict()
ans = 0

# 각 문자열이 몇 번씩 나왔는지
# hashmap에 기록
for word in words:
    # 처음 나온 문자열이라면 1을 직접 적기
    if word not in freq:
        freq[word] = 1
    # 이미 나와있던 문자열이라면 1을 더해줌
    else:
        freq[word] += 1
        
    # 가장 많이 나온 횟수를 갱신
    ans = max(ans, freq[word])