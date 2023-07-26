n, m, k = map(int,input().split()) # n, m, k를 공백으로 구분하여 입력받기 
data = list(map(int, input().split())) # n개의 수를 공백으로 구분하여 입력받기

data.sort(reverse=True)
first = data[0]
second = data[1]
'''
data.sort() # 정렬
first = data[n-1] # 가장 큰 수
second = data[n-2] # 두번째로 큰 수
'''
first_count = (m//(k+1))*k + m %(k+1) # 가장 큰 수가 더해지는 횟수 계산

answer = first * first_count + second*(m-first_count)
print(answer)