n = int(raw_input())
a = []
for i in range(n):
    a.append(tuple(map(int, raw_input().split())))

a.sort()
flag = 0
for i in range(n-1):
    if a[i][1] > a[i+1][1]:
	flag = 1

if flag == 1:
    print 'Happy Alex'
else :
    print 'Poor Alex'
