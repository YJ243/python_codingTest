N = 1260

answer = 0

while N == 0:
    if N > 500:
        N /= 500
        answer = answer + N
    elif N > 100:
        N /= 100
        answer = answer+N
    elif N > 50:
        N /= 50
        answer = answer+N
    else
        N /= 10
        answer = answer+N
print(N)
    