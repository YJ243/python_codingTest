'''
2023.10.06
- 서로 다른 세 개의 위치를 골라 각 위치에 있는 세 수를 더했을 때 
- k가 되는 서로 다른 조합의 개수를 출력하는 코드
'''

## 내 풀이
# 나는 [tmp_sum(두 원소의 합) = target_sum - 한 원소]를 보고,
# 그다음 또 tmp_sum에서 해시에 있는 key를 뺀 [tmp_sum-num]을 봄
# --> 그런데 틀림
n, k = map(int, input().split())
arr = list(map(int, input().split()))

cnt = dict()
ans = 0
def factorial(number): # 조합을 위한 factorial 함수
    if number == 0: number = 1
    if number <= 1: return 1
    return number * factorial(number-1)


for i in range(n):
    tmp_sum = k-arr[i] # 현재 값 위치에서 나머지 두 수의 합

    # cnt에 2개 이상이 있다면 확인하기
    if sum(cnt.values()) >= 2:    
        # cnt hashMap에서 2개의 key 뽑아서 확인
        # key 2개의 합이 tmp_sum이 되는지 확인
        for _, num in enumerate(cnt): # cnt에 있는 key 차례대로 확인해나가면서
            if tmp_sum-num == num: # 만약 나머지 두 수가 똑같다면 조합 구하기
                a = factorial(cnt[num])
                b = 2 * factorial(cnt[num]-2)
                ans += int(a / b)
                break
            else:
                if tmp_sum-num in cnt: # 만약 k-arr[i]-num이 cnt에 있다면
                    #print(ans)
                    ans += cnt[num] * cnt[tmp_sum-num]
                    break


    if arr[i] not in cnt:
        cnt[arr[i]] = 1
    else:
        cnt[arr[i]] += 1

print(ans)

## 풀이
# 배열에서 두 원소를 골라 target_sum을 만들 수 있는지 여부는?
# => target_sum - 두 원소의 합에 해당하는 원소가 있는지 확인
# 매번 모든 배열을 순회하면서 해당 원소가 있는지 확인 = O(N)
# 그렇지만, HashMap에 모든 배열의 원소에 대한 정보를 담아두면 그 후로는 O(1)


# 변수 선언 및 입력:
n, k = tuple(map(int, input().split()))
arr = list(map(int, input().split()))

count = dict()

# 각 숫자가 몇 번씩 나왔는지를
# hashmap에 기록
for elem in arr:
    if elem in count:
        count[elem] += 1
    else:
        count[elem] = 1

ans = 0
# 배열을 앞에서부터 순회하면서 쌍을 만들어 줌
for i in range(n):
    # 이미 순회한 적이 있는 숫자는 빼 버림으로서
    # 같은 조합이 여러번 세어지는 걸 방지
    count[arr[i]] -= 1
    
    for j in range(i):
        # 전처리를 해주었기 때문에 이미 순회한 적이 있는 값은 hashmap에 없음
        # 이와 같은 방식으로 같은 조합이 중복으로 세어지는 것을 방지
        diff = k-arr[i]-arr[j]
        
        if diff in count:
            ans += count[diff]

print(ans)
