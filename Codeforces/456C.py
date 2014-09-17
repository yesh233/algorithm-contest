n = int(raw_input())
a = map(int, raw_input().split())
a.sort()
b = [(0,-1)]
c,m = a[0],1
for i in range(1,n):
    if a[i] == c:
	m = m + 1
    else:
	b.append((m*c,c))
	c,m = a[i],1

b.append((m*c, c))
m = len(b)
f = [0, b[1][0]]
for i in range(2,m):
    if b[i][1] == b[i-1][1] + 1:
        f.append(max(f[i-1], f[i-2]+b[i][0]))
    else :
	f.append(f[i-1]+b[i][0])

print f[m-1]

