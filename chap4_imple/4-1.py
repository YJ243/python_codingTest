n = int(input())
x, y = 1,1

plans = input().split()

dx = []
dy = []
move_types = ['L','R','U','D']

for i in range(n):
    for j in range(len(move_types)):
        # move types과 같은지 확인