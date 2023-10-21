'''
2023.10.06
'''

# 내 풀이
n, k = map(int, input().split())
a = list(map(int, input().split()))

freq = dict()
for num in a:
    if num in freq:
        freq[num] += 1
    else:
        freq[num = 1]

# value -> key 순으로 내림차순 정렬
freq = dict(sorted(frq.items(), key=lambda x:(-x[1], -x[0])))
keys = list(freq.keys()) # key들만 들어있는 리스트

for i in range(k):
    print(keys[i], end=' ')
    
    
    
## 풀이
# 변수 선언 및 입력:
n, k = tuple(map(int, input().split()))
arr = list(map(int, input().split()))

count = dict()

# 각 숫자가 몇 번씩 나왔는지 hashmap에 기록
for elem in arr:
    if elem in count:
        count[elem] += 1
    else:
        count[elem] = 1

# hashmap을 순회하면서 중복되지 않게 새 배열 만들어 줌
new_arr = [
    [value, key]
    for key, value in count.items()
]

# 문제에서 요구한 정렬 기주에 맞추어 정렬
new_arr = sorted(new_arr)

# 출력
leng = len(new_arr)
for i in range(leng-1, leng-k-1, -1):
    print(new_arr[i][1], end=" ")