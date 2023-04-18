n = int(input())
p = list(map(int, input().split()))

p.sort(reverse=True) # 내림차순 정렬

cnt = 0 # 총 그룹 수
idx = 0 # 현재 그룹에 들어가 있는 맨 마지막 모험가의 인덱스
for i in range(n): # 공포도가 제일 큰 모험가부터 확인하는데
    if i <= idx: # 만약 현재 비교하는 인덱스가 idx보다 작거나 같으면
        continue # 아래는 무시
    idx = p[i]-1+i # 인덱스는 최대 들어갈 수 있는 개수만큼 넣기
    if idx < n: # 그 인덱스가 범위를 안넘으면
        cnt += 1 # 그룹 수 증가
        
print(cnt)