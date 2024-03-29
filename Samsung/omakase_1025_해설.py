'''
2023.10.25
'''
###################################################################################################
# 내가 놓친 것들
# 1. 일일이 L번 for문을 돌아서 시간 초과
# 2. 언제 초밥이 먹히는지를 계산해서 시뮬레이션 돌리기
# 3. 문제에서 주어지지 않은 이벤트를 query로 정의하여 내가 창조할 수도 있음
# 4. 초밥, 사람은 각각 독립적이니 그에 따라 생각해서 계산하기
####################################################################################################


# 변수 선언
L, Q = 0,0      # L: 의자 개수, Q: 쿼리 개수

class Query:
    def __init__(self, cmd, t, x, name, n):
        self.cmd = cmd      # 명령 유형
        self.t = t          # 명령이 발생한 시각
        self.x = x          # 명령이 발생한 자리 번호
        self.name = name    # 명령에 관계된 이름
        self.n = n          # 새로 도착한 사람이 먹어야 하는 초밥 개수

class Person:
    def __init__(self, name):
        self.name = name
        self.entry_time = 0     # 이 사람이 입장한 시각
        self.queries = []       # 이 사람에게 만들어진 초밥 정보들(언제, 어느 자리에)
        self.position = 0       # 이 사람이 앉은 자리
        self.exit_time = 0      # 이 사람이 퇴장한 시각


queries = []        # 명령들을 관리
people = dict()     # 각 사람들마다 독립적으로 문제를 해결

# 입력
L, Q = map(int, input().split())
for _ in range(Q):
    command = input().split()
    cmd, t, x, n = -1, -1, -1, -1
    name = ""
    cmd = int(command[0])
    if cmd == 100:      # 초밥이 만들어짐
        t, x, name = command[1:]
        t, x = map(int, [t,x])
    elif cmd == 200:    # 사람이 입장
        t, x, name, n = command[1:]
        t, x, n = map(int, [t,x,n])
    else:               # 사진 촬영
        t = int(command[1])
    queries.append(Query(cmd, t, x, name, n))

    if name != "" and name not in people:
        people[name] = Person(name)

    # 사람별 주어진 초밥 목록을 관리
    if cmd == 100:      # 이 사람을 위한 초밥이 만들어졌다면
        people[name].queries.append(Query(cmd, t, x, name, n))      # 이 사람의 쿼리 리스트에 기록
    # 손님이 입장한 시간과 위치를 관리
    elif cmd == 200:    # 이 사람 입장 시간이 주어졌다면
        people[name].entry_time = t     # 입장시간 업데이트
        people[name].position = x       # 앉은 자리 업데이트

# 각 사람마다 자신의 이름이 적힌 조합을 언제 먹게 되는지를 계산해서 해당 정보를 기존 Query에 추가하기 (111번 쿼리)
for name, p in people.items():
    for q in p.queries:
        time_to_removed = 0         # 이 사람이 이 초밥을 먹게 되는 시각

        # 1) 만약 사람이 등장하기 전에 초밥이 미리 주어진 상황이라면
        if q.t < p.entry_time:
            # 1-1) entry_time 때의 스시 위치를 구함
            t_sushi_x = (q.x + (p.entry_time - q.t)) % L    # L초마다 자기 위치로 돌아오기 때문에, L로 나눈 나머지
            # 1-2) 몇 초가 더 지나야 만나는 지를 계산하기
            additional_time = (L+p.position-t_sushi_x) % L  # (L+X-Y)%L
            time_to_removed = p.entry_time+additional_time  # 사람 도착 시간 + 사람 앞에까지 가는데 걸리는 시간

        # 2) 만약 사람이 등장한 이후에 주어졌다면
        else:
            # 2-1) 몇 초가 더 지나야 만나는 지를 계산
            additional_time = (L+p.position-q.x) % L        # 가는데 걸리는 시간
            time_to_removed = q.t +additional_time  # 그 만큼의 시간이 지나면 먹힘

        # 초밥이 사라지는 시간 중 가장 늦은 시간으로 사람이 사라지는 시간을 업데이트 하기
        p.exit_time = max(p.exit_time, time_to_removed)     # 이 사람의 퇴장 시간은 마지막으로 먹힌 초밥의 시각

        # 초밥이 사라지는 111번 쿼리를 추가하기
        queries.append(Query(111, time_to_removed, -1, name, -1))   # 초밥이 먹히는 이벤트, name한테 할당된 초밥은 time_to_removed에 모두 먹힌다

# 사람마다 초밥을 마지막으로 먹은 시간 t를 계산하여 그 사람이 해당 t때 코드트리 오마카세를 떠났다는 Query를 추가 (222번 쿼리)
for p in people.values():   # 모든 사람마다
    queries.append(Query(222, p.exit_time, -1, p.name, -1))         # 사람이 퇴장하는 이벤트

# 전체 Query를 시간 순으로 정렬하되, t가 일치한다면 문제 조건상 사진 촬영에 해당하는 300이 가장 늦게 나오도록 cmd를 오름차순으로 정렬
# 이후 순서대로 보면서 사람, 초밥 수를 count하다가 300이 나오면 현재 사람, 초밥 수를 출력
queries.sort(key=lambda q: (q.t, q.cmd))    # 같은 시간이라면 쿼리 번호를 두번째 우선순위로

people_num, sushi_num = 0,0
for i in range(len(queries)):
    if queries[i].cmd == 100:   # 초밥 추가
        sushi_num += 1
    elif queries[i].cmd == 111: # 초밥 제거
        sushi_num -= 1
    elif queries[i].cmd == 200: # 사람 추가
        people_num += 1
    elif queries[i].cmd == 222: # 사람 제거
        people_num -= 1
    else:   # 사진 촬영 시 답을 출력
        print(people_num, sushi_num)
        