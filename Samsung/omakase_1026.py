'''
2023.10.26

'''

# 변수 선언
L, Q = 0, 0     # L: 초밥 벨트의 길이, Q: 명령의 수

# 명령의 정보
class Query:
    def __init__(self, cmd, t, x, name, n):
        self.cmd = cmd      # 명령 구분(100, 200, 300)
        self.t = t          # 명령이 발생한 시각
        self.x = x          # 병령이 발생한 자리 위치
        self.name = name    # 명령에 관계된 이름
        self.n = n          # 새로 도착한 사람이 먹어야 하는 초밥 개수

# 사람의 정보
class Person:
    def __init__(self, name):
        self.name = name        # 사람 이름
        self.in_time = 0        # 들어온 시간
        self.out_time = 0       # 나간 시간
        self.chair_num = 0      # 의자 번호
        self.query = []         # 그 사람에게 배정된 쿼리

people = dict()         # 사람들마다 독립적으로 문제를 해결
queries = []            # 모든 쿼리들 관리

# 입력
L, Q = map(int, input().split())    # 초밥 벨트의 길이와 명령 수 입력 받기
for _ in range(Q):                  # Q개의 줄에 걸쳐서 명령 정보가 주어짐
    query = input().split()         # 명령 입력 받기
    cmd = int(query[0])             # 명령 구분자
    t, x, n = 0, 0, 0
    name = ""
    if cmd == 100:  # 주방장의 초밥 만들기
        t, x, name = query[1:]          # 시각 t에 위치 x앞에 있는 벨트 위에 name 이름 초밥 올려놓음
        t, x = map(int, [t, x])         # 시각, 위치를 int로
    elif cmd == 200: # 손님 입장
        t, x, name, n = query[1:]       # name 사람은 시각 t에 위치 x에 있는 의자로 가서 앉은 뒤, n개의 초밥을 먹고 떠남
        t, x, n = map(int, [t, x, n])   # 시각, 위치, 초밥 개수 int로
    else:            # 사진 촬영
        t = int(query[1])               # 시각 t에 남아 있는 사람 수와 초밥의 수를 출력

    # 입력 받은 모든 쿼리를 넣기
    queries.append(Query(cmd, t, x, name, n))
    # 사람 객체 만들기
    if name != "" and name not in people:   # 만약 명령이 사람에 관한 것이고, 그 이름을 가진 사람이 새로 들어온 명령이라면
        people[name] = Person(name)         # 해당 이름을 key로, 클래스를 value로 하는 객체 생성

    if cmd == 100:
        people[name].query.append(Query(cmd,t,x,name,n))
    elif cmd == 200:
        people[name].chair_num = x
        people[name].in_time = t

# 시뮬레이션 시작
# 1. 현재 명령 정보를 초밥 생성/사람 입장/출력밖에 없음-->초밥 사라짐(111)/사람 퇴장 명령(222) 추가
# 모든 초밥(각각의 초밥은 독립적)에 대해서 언제 사라지는가?
# 마지막으로 사라진 초밥 시각이 사람 퇴장 시각
'''
for name, per in people.items():
    for q in per.query:
        time_to_removed = 0

        if q.t < per.in_time:
            sushi_loc = (q.x + (per.in_time - q.t)) % L
            additional_turn = (L+per.chair_num-sushi_loc) % L
            time_to_removed = per.in_time+additional_turn
        else:
            additional_turn = (L+per.chair_num-q.x) % L
            time_to_removed = q.t + additional_turn

        per.out_time = max(per.out_time, time_to_removed)

        queries.append(Query(111,time_to_removed, -1, name, -1))
'''
for query in queries:
    if query.cmd == 100:        # 초밥이 생성된 명령이라면
        cur_name = query.name   # 해당 초밥이 배정된 사람의 이름
        time_to_removed = 0     # 초밥이 사라지는 시간
        # 1) 이 초밥이 사람이 등장하기 이전의 초밥이라면
        if query.t < people[cur_name].in_time:
            # 1-1) 돌고 있던 초밥이 사람이 등장했을 때의 위치를 계산
            # 초밥이 들어온 위치부터 시작해서 얼만큼 돌았는지
            sushi_loc = (query.x + (people[cur_name].in_time-query.t)) % L
            # 1-2) 그 위치에서 얼만큼 회전해야 사람 위치까지 가는지 계산
            additional_turn = (people[cur_name].chair_num+L - sushi_loc) % L
            time_to_removed = people[cur_name].in_time+additional_turn
        # 2) 이 초밥이 사람이 등장한 후의 초밥이라면
        else:
            # 2-1) 그 위치에서 얼만큼 회전해야 사람 위치까지 가는지 계산
            additional_turn = (L+people[cur_name].chair_num-query.x) % L
            time_to_removed = query.t + additional_turn
        # 해당 초밥이 사라지는 시점에 대해서 명령을 추가하기
        # 111번 명령=초밥 사라짐, 해당 사람이 등장하고
        queries.append(Query(111, time_to_removed, -1, cur_name, -1))
        people[cur_name].out_time = max(people[cur_name].out_time, time_to_removed)

# 사람마다 초밥을 마지막으로 먹은 t를 계산해 그 사람이 해당 t때 코드트리 오마카세를 떠났다는 query를 추가
for per in people.values():    # 모든 사람마다
    queries.append(Query(222, per.out_time, -1, per.name, -1))      # 사람이 퇴장하는 이벤트

# 전체 Query를 시간 순으로 정렬하되, t가 일치한다면 문제 조건상 사진 촬영에 해당하는 300이 가장 늦게 나오도록
# cmd를 오름차순으로 정렬, 이후 순서대로 count 하다가 300이 나오면 현재 사람, 초밥 수를 출력
queries.sort(key=lambda x:(x.t, x.cmd))
person_cnt, sushi_cnt = 0,0
for query in queries:
    if query.cmd == 100:        # 초밥 추가
        sushi_cnt += 1
    elif query.cmd == 111:      # 초밥 제거
        sushi_cnt -= 1
    elif query.cmd == 200:      # 사람 추가
        person_cnt += 1
    elif query.cmd == 222:      # 사람 제거
        person_cnt -= 1
    else:                       # 사진 촬영 시 답을 출력
        print(person_cnt, sushi_cnt)
