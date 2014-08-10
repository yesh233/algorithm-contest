n, m = map(int, raw_input().split())
e = [[] for i in range(n)]
for i in range(m):
    j,k = map(int, raw_input().split())
    e[j-1].append(k-1)
    e[k-1].append(j-1)
o = map(int, raw_input().split())

r = [idx for (idx,x) in enumerate(o) if x == 1]
if len(r) == 0:
    print 0
else :
    v = [0 for i in range(n)]
    ans = []
    def add(u):
	o[u] ^= 1
        ans.append(u + 1)

    def gao(u, p=-1):
	v[u] = 1
	add(u)
	for i in e[u]:
	    if not v[i]:
		gao(i, u)
		add(u)
	if o[u] == 1:
	    if p != -1:
		add(p)
		add(u)
	    else :
		ans.pop()
		o[u] = 0
    gao(r[0])
    r = [x for x in o if x == 1]
    if len(r) > 0:
	print -1
    else :
	print len(ans)
	print ' '.join(map(str,ans)) 
