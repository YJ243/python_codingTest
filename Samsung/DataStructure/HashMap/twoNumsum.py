'''
2023.10.06 HashMap / 두 수의 합
'''

n, k = map(int, input().split())
arr = list(map(int, input().split()))

freq = dict()
ans = 0
# 배열을 앞에서부터 순회하면서 쌍을 만들어 줌
for num in arr:
    if k - num in freq: # 가능한 모든 쌍의 수를 세어줌
       ans += freq[k-num]
    
    # 현재 숫자 개수 하나 증가
    if num in freq:
        freq[num] += 1
    else:
        freq[num] = 1
print(ans) 