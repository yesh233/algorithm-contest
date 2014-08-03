n = int(raw_input())
a = map(int, raw_input().split())

l = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41]
llen = len(l)
ran = 50
mt = [0 for i in range(ran)]
for i in range(1,ran):
    t = [int(i % x == 0) for x in l]
    mt[i] = sum([x<<j for j,x in enumerate(t)])

f = [[ran*n for j in range(1<<llen)] for i in range(n+1)]
c = [[0 for j in range(1<<llen)] for i in range(n+1)]
p = [[-1 for j in range(1<<llen)] for i in range(n+1)]

f[0][0] = 0
for i in range(n):
    for j in range(1<<llen):
	for k in range(1,ran):
	    if (j & mt[k]) == 0:  
		if f[i+1][j|mt[k]] > f[i][j] + abs(a[i]-k):
		    c[i+1][j|mt[k]] = k
		    p[i+1][j|mt[k]] = j 
		    f[i+1][j|mt[k]] = f[i][j] + abs(a[i]-k)

r = f[n].index(min(f[n]))
ans = []
for i in range(n, 0, -1):
    ans.append(c[i][r])
    r = p[i][r]
print ' '.join(map(str, ans[::-1]))    
