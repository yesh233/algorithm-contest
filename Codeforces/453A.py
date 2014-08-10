m, n = map(int, raw_input().split())
ans = float(m)
for i in range(1,m):
    ans = ans - (float(i)/m) ** n
print '%.10f' % ans 


