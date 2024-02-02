'''
HashSet을 이용해서 그룹 별로 초대받지 못한 사람 목록을 관리
처음 주어진 사람 별 속해있는 그룹 정보를 인접리스트로 만들어서 1번 사람을 시작으로 bfs탐색을 진행
=> 원래 주어진 [그룹별로 사람 번호]만 보는 것이 아니라, [사람별로 그룹 번호]를 생각 못함
=> HashSet은 초대 받은 사람만 관리하도록 생각했지만, "그룹 별"로, "초대받지 못한 사람"
큐에 새로운 원소를 추가하게 될 조건은 현재 사람 x가 속해 있는 그룹에서 x를 제거했을 떄
떄그룹에 남아있는 사람의 수가 정확히 1명이 되는 경우!
총 시간복잠도=O(N+G), 노드 수:N, 간선 수:G
'''
# 내 풀이
from collections import deque

n, g = tuple(map(int, input().split()))

not_invited = [ set() for _ in range(g) ]   # 각 그룹마다 초대받지 못한 사람들에 대한 HashSet
person_in_group = [[] for _ in range(n+1)]  # 각 사람이 속해있는 그룹들
invited = [False for _ in range(n+1)]
for group_num in range(g):
    inp = list(map(int, input().split()))
    for i in range(1, len(inp)):
        not_invited[group_num].add(inp[i])
        person_in_group[inp[i]].append(group_num)

q = deque()
invited[1] = True
q.append(1)

while q:
    cur_num = q.popleft()

    for group_num in person_in_group[cur_num]:
        not_invited[group_num].discard(cur_num)  # 현재 숫자를 해당 그룹에서 빼기
        
        if len(not_invited[group_num]) == 1:     # 만약 남은 원소가 한개라면
            cur = not_invited[group_num].pop()
            invited[cur] = True
            q.append(cur)


ans = sum(invited)
print(ans)

''' 해설 풀이 '''
from collections import deque

# 변수 선언 및 입력:
n, g = tuple(map(int, input().split()))

invited = [False] * n
# 각 그룹마다 초대장을 받지 못한 사람들을 관리
groups = [set() for _ in range(g)]
# 각 사람이 어떤 그룹에 속하는지 관리
people_groups = [[] for _ in range(n)]

q = deque()
ans = 0

for i in range(g):
    nums = list(map(int, input().split()))[1:]
    for num in nums:
        num -= 1
        gorups[i].add(num)
        people_groups[num].append(i)

q.append(0)
invited[0] = True
while q:
    x = q.popleft()
    ans += 1
    
    # x가 들어있는 그룹에서 x를 지우기
    # hashset에는 그룹에서 초대받지 않은 인원만을 남김
    groups[g_num].remove(x)
    # 초대받지 않은 인원이 한명밖에 없다면 초대하기
    if len(groups[g_num]) == 1:
        p_num = list(groups[g_num])[0]
        if not invited[p_num]:
            invited[p_num] = True
            q.append(p_num)

# 초대장을 받은 인원을 출력학기
print(ans)
